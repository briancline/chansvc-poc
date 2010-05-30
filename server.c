#include <bot.h>

int get_connection(char *hostname, int port)
{
   struct sockaddr_in sa;
   struct hostent *hp;
   int sckfd;
   
   if((hp = gethostbyname(hostname)) == NULL) 
   {
      errno = ECONNREFUSED;
      return -1;
   }
   bzero(&sa, sizeof(sa));
   bcopy(hp->h_addr, (char *) &sa.sin_addr, hp->h_length);
   sa.sin_family = hp->h_addrtype;
   sa.sin_port = htons((u_short) port);
   if((sckfd = socket(hp->h_addrtype, SOCK_STREAM, 0)) < 0)
 		return -1;
   setsockopt(sckfd, SOL_SOCKET, SO_LINGER, 0, 0);
   setsockopt(sckfd, SOL_SOCKET, SO_REUSEADDR, 0, 0);
   setsockopt(sckfd, SOL_SOCKET, SO_KEEPALIVE, 0, 0);
   if(connect(sckfd, (struct sockaddr *) &sa, sizeof(sa)) < 0) 
   {
      close(sckfd);
      return -1;
   }
   return sckfd;
}

int readln()
{
   char ch;
   int i = 0;
   do {
      if(read(socketfd, &ch, 1) < 1)
			return 0;
      if(ch >= 32 || ch <= 126)
         if(i < MAXLEN - 1) 
				line[i++] = ch;
   } while(ch != '\n');

   line[i] = '\0';
   
   return 1;
}

int read_from_socket(int sock, char *buffer) {
   char ch;
   int i = 0;

   do {
      if(read(sock, &ch, 1) < 1) 
			return 0;
      if(ch >= 32 || ch <= 126)
         if(i < MAXLEN - 1)
				buffer[i++] = ch;
   } while(ch != '\n');
   buffer[i] = '\0';

   return 1;
}

int writeln(char *buffer) {
	printf("[SEND] %s", buffer);
   return write(socketfd, buffer, strlen(buffer));
}

int writeln2(int sock, char *buffer) {
	printf("[S!!!] %s", buffer);
   return write(sock, buffer, strlen(buffer));
}

int send_to_socket(int sck, char *format, ...) {
   va_list arglist;
   char buffer[MAXBUF];
	
   va_start(arglist, format);
   vsprintf(buffer, format, arglist);
   va_end(arglist);
   return writeln(buffer);
}

int ssend(char *format, ...) {
   va_list arglist;
   char buffer[MAXBUF];

   buffer[0] = '\0';
   va_start(arglist, format);
   vsprintf(buffer, format, arglist);
   va_end(arglist);
   return writeln(buffer);
}

int irc_send(char *source, char *token, char *argFormat, ...)
{
	char fullBuffer[MAXBUF];
	char tokenArgs[MAXBUF];
	
	fullBuffer[0] = '\0';
	tokenArgs[0] = '\0';
	
	va_list argList;
	va_start(argList, argFormat);
	vsprintf(tokenArgs, argFormat, argList);
	va_end(argList);
	
	sprintf(fullBuffer, "%s %s %s\n", source, token, tokenArgs);
	return writeln(fullBuffer);
}

int irc_sendToken(char *source, char *token)
{
	char fullBuffer[MAXBUF];
	sprintf(fullBuffer, "%s %s\n", source, token);
	return writeln(fullBuffer);
}

int notify(char *format, ...) {
	if(!bot.uplink)
		return 0;
	
	va_list arglist;
	char buffer[MAXBUF];
	
	va_start(arglist, format);
	vsprintf(buffer, format, arglist);
	va_end(arglist);
	
	char fullBuffer[MAXBUF];
	sprintf(fullBuffer, "%s %s %s :%s\n", bot.numeric, TOK_PRIVMSG, bot.debugChan, buffer);
	return write(socketfd, fullBuffer, strlen(fullBuffer));
}


int notice(char *numeric, char *format, ...) {
	va_list arglist;
	char buffer[MAXBUF];
	
	va_start(arglist, format);
	vsprintf(buffer, format, arglist);
	va_end(arglist);
	
	return irc_send(bot.numeric, TOK_NOTICE, "%s :%s", numeric, buffer);
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
