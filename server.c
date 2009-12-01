#include <bot.h>

int get_connection(char *hostname, int port)
{
   struct sockaddr_in sa;
   struct hostent *hp;
   int sckfd;
   
   if((hp = gethostbyname(hostname)) == NULL) 
   {
      errno = ECONNREFUSED;
      return(-1);
   }
   bzero(&sa, sizeof(sa));
   bcopy(hp->h_addr, (char *) &sa.sin_addr, hp->h_length);
   sa.sin_family = hp->h_addrtype;
   sa.sin_port = htons((u_short) port);
   if((sckfd = socket(hp->h_addrtype, SOCK_STREAM, 0)) < 0) return(-1);
   setsockopt(sckfd, SOL_SOCKET, SO_LINGER, 0, 0);
   setsockopt(sckfd, SOL_SOCKET, SO_REUSEADDR, 0, 0);
   setsockopt(sckfd, SOL_SOCKET, SO_KEEPALIVE, 0, 0);
   if(connect(sckfd, (struct sockaddr *) &sa, sizeof(sa)) < 0) 
   {
      close(sckfd);
      return(-1);
   }
   return(sckfd);
}

int readln()
{
   char ch;
   int i = 0;
   do {
      if(read(socketfd, &ch, 1) < 1) return(0);
      if(ch >= 32 || ch <= 126)
         if(i < MAXLEN - 1) line[i++] = ch;
   } while(ch != '\n');

   line[i] = '\0';
   
   return 1;
}

int read_from_socket(int sock, char *buffer) {
   char ch;
   int i = 0;

   do {
      if(read(sock, &ch, 1) < 1) return(0);
      if(ch >= 32 || ch <= 126)
         if(i < MAXLEN - 1) buffer[i++] = ch;
   } while(ch != '\n');
   buffer[i] = '\0';

   return 1;
}

int writeln(char *buffer) {
   if(write(socketfd, buffer, strlen(buffer)) < 0) return(0);
}

int writeln2(int sock, char *buffer) {
   if(write(sock, buffer, strlen(buffer)) < 0) return(0);
   return 1;
}

int send_to_socket(int sck, char *format, ...) {
   va_list arglist;
   char buffer[MAXBUF];
	
   va_start(arglist, format);
   vsprintf(buffer, format, arglist);
   va_end(arglist);
   return(writeln2(sck, buffer));
}

int ssend(char *format, ...) {
   va_list arglist;
   char buffer[MAXBUF];

   buffer[0]='\0';
   va_start(arglist, format);
   vsprintf(buffer, format, arglist);
   va_end(arglist);
   return(writeln(buffer));
}

int notify(char *format, ...) {
	va_list arglist;
	char buffer[MAXBUF];
	
	va_start(arglist, format);
	vsprintf(buffer, format, arglist);
	va_end(arglist);
	
	return ssend(":%s PRIVMSG %s :%s\n", bot.nick, bot.debugChan, buffer);
}


int notice(char *nick, char *format, ...) {
	va_list arglist;
	char buffer[MAXBUF];
	struct nickinfo *nickptr = get_usernum(nick);
	
	va_start(arglist, format);
	vsprintf(buffer, format, arglist);
	va_end(arglist);
	
	return ssend(":%s NOTICE %s :%s\n", bot.nick, nickptr->numeric, buffer);
}


void parse_serv(fd_set *fds) {
	if(FD_ISSET(socketfd, fds)) {
		if(readln() > 0) {
			parse(line);
		}
		else
			close(socketfd);
	}
}
