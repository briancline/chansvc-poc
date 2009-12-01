#include <bot.h>

void bot_init() {
	FILE *out;
	
	ssend("PASS %s\n", bot.password);
	ssend("SERVER %s 2 0 %ld P10 %c]] :%s\n", bot.server->name, time(NULL), bot.scnum, bot.servinfo);
	
	bot.active = true;
	if(out = fopen("w.pid", "wt")) {
		fprintf(out, "%i\n", getpid());
		fclose(out);
	}
}

void bot_burst() {
	ssend("%c N %s 1 %lu %s %s %s DAqAAF %s :%s\n", bot.scnum, bot.nick, time(NULL), bot.ident, bot.host, bot.modes, bot.fullnum, bot.nickinfo);
	ssend("%c B %s 127008000 +tn %s:o\n", bot.scnum, bot.debugChan, bot.fullnum);
	ssend("%c B %s 127008000 +tn %s:o\n", bot.scnum, bot.protoChan, bot.fullnum);
	ssend("%c EB\n", bot.scnum);
}
