#include <bot.h>

void sig_segv() {
	ssend(":%s WALLOPS :Got sigsegv :(\n", bot.server);
	ssend(":%s SQUIT %s %ld :got sigsegv :(\n", bot.server, bot.server, time(NULL));
	exit(0);
}

void sig_term() {
	ssend(":%s WALLOPS :got sigterm (oops!)\n", bot.server);
	ssend(":%s SQUIT %s %ld :got sigterm\n", bot.server, bot.server, time(NULL));
	exit(0);
}

void sig_int() {
	ssend(":%s WALLOPS :got sigint (doh)\n", bot.server);
	ssend(":%s SQUIT %s %ld :got sigint\n", bot.server, bot.server, time(NULL));
	exit(0);
}

void sig_hup() {
	ssend(":%s WALLOPS :got sighup, restarting\n", bot.server);
	ssend(":%s SQUIT %s %ld :Restarting (SIGHUP)\n", bot.server, bot.server, time(NULL));
	close(socketfd);
	bot.active = false;
	loadconf();
	socketfd = get_connection(bot.uplinkHost, bot.uplinkPort);
	if(socketfd == -1) exit(0);
	bot_init();
}

void sig_bus() {
	ssend(":%s WALLOPS :Got SIGBUS :(\n", bot.server);
	ssend(":%s SQUIT %s %ld :Got SIGBUS\n", bot.server, bot.server, time(NULL));
	close(socketfd);
	bot.active = false;
	exit(0);
}
