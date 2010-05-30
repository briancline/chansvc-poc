#define DEF_GLOBALS
#include "bot.h"
#undef DEF_GLOBALS

int main(int argc, char **argv) {
	fd_set fdvar;
	struct timeval timeout;
	bot.start = time(NULL);
	signal(SIGSEGV, sig_segv);
	signal(SIGTERM, sig_term);
	signal(SIGINT, sig_int);
	signal(SIGHUP, sig_hup);
	signal(SIGBUS, sig_bus);
	//if(fork()) exit(0);
	
	bot.server = (struct Server *) calloc(1, sizeof(struct Server));
	loadconf();
	socketfd = get_connection(bot.uplinkHost, bot.uplinkPort);
	if(socketfd == -1) {
		printf("Could not connect to %s:%d.\n", bot.uplinkHost, bot.uplinkPort);
		exit(0);
	}
	
	strcpy(bot.version, "Channel Service 0.1.1a");
	bot_init();
	
	while(1) {
		timeout.tv_sec = WAITSEC;
		timeout.tv_usec = UWAITSEC;
		FD_ZERO(&fdvar);
		FD_SET(socketfd, &fdvar);
		switch(select(NFDBITS, &fdvar, (fd_set *) 0, (fd_set *) 0, &timeout)) {
			case 0: break;
			case -1: break;
			default:
    				parse_serv(&fdvar);
				break;
		}
	}
	
	return 0;
}
