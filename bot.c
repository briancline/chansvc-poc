#include <bot.h>

void bot_init()
{
	FILE *out;
	
	add_server(bot.server->name, bot.server->numeric, NULL, bot.serverDescription);
	add_user(bot.nick, bot.ident, bot.host, bot.modes, bot.numeric, bot.realName);
	add_channel(bot.debugChan, "+nt", time(NULL));
	add_channel(bot.protoChan, "+nt", time(NULL));
	
	ssend("PASS %s\n", bot.uplinkPassword);
	ssend("SERVER %s 2 %ld %ld P10 %s]]] :%s\n", bot.server->name, time(NULL), time(NULL), bot.serverNumeric, bot.serverDescription);
	
	bot.active = true;
	if((out = fopen("w.pid", "wt"))) {
		fprintf(out, "%i\n", getpid());
		fclose(out);
	}
}

void burst_servers()
{
	struct Server* server = servers;
	
	while(server) {
		//irc_send(bot.serverNumeric, TOK_SERVER, "%s ")
		server = server->next;
	}
}

void burst_glines()
{
}

void burst_jupes()
{
}

void burst_channels()
{
	struct Channel* chan = channels;
	
	while(chan) {
		irc_send(bot.serverNumeric, TOK_BURST, "%s 127008000 +tn %s:o", 
			chan->name, bot.numeric);
		
		chan = chan->next;
	}
}

void burst_users()
{
	struct User* user = users;
	
	while(user) {
		irc_send(bot.serverNumeric, TOK_NICK, "%s 1 %lu %s %s %s AAAAAA %s :%s", 
			user->nick, time(NULL), user->ident, user->host, 
			user->modes, user->numeric, user->realName);
			
		user = user->next;
	}
}