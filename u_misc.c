#include <bot.h>

void u_whois(struct User* source, char **parv, int parc) {
	struct User *user = getUserByNick(parv[1]);
	
	if(!user) {
		notice(source->numeric, "User %s is not online.\n", parv[1]);
		return;
	}
	
	notice(source->numeric, "Full host      : %s!%s@%s", user->nick, user->ident, user->host);
	notice(source->numeric, "On server      : %s", user->server->name);
	if(user->isoper) {
		notice(source->numeric, "Access         : Is an IRC Operator");
	}
	notice(source->numeric, "Numeric        : %s", user->numeric);
	notice(source->numeric, "Server Numeric : %s (%d)", user->server->numeric, user->server->numericInt);
}


void u_raw(struct User* source, char **parv, int parc) {
	char *rest = join_array(parv, 1, parc-1);
	ssend("%s\n", rest);
}


void u_ping(struct User* source, char **parv, int parc) {
	notice(source->numeric, "%cPING %s", CTCP_CHAR, parv[4]);
}


void u_version(struct User* source, char **parv, int parc) {
	notice(source->numeric, "%cVERSION %s%c", CTCP_CHAR, bot.version, CTCP_CHAR);
}


void u_traverse(struct User* source, char **parv, int parc) {
	struct User *nsrc = users;
	struct Server *ssrc = servers;
	
	notify("Traversing users linked-list");
	while(nsrc) {
		notify("(%d) users->nick = [%s] %s", nsrc, nsrc->numeric, nsrc->nick);
		nsrc = nsrc->next;
	}
	notify("(done)");
	
	notify("Traversing servers linked-list");
	while(ssrc) {
		notify("servers->name = %s", ssrc, ssrc->name);
		notify("         uplink: %s", ssrc->uplink->name);
		notify("         next: %s", ssrc->next ? ssrc->next->name : "(null)");
		ssrc = ssrc->next;
	}
	notify("(done)");
}


void u_die(struct User* source, char **parv, int parc) {
	irc_send(bot.numeric, TOK_QUIT, ":Die by %s", source->nick);
	irc_send(bot.serverNumeric, TOK_SQUIT, "%s 0 :Die by %s", bot.server->name, source->nick);
}


void u_restart(struct User* source, char **parv, int parc) {
	irc_send(bot.numeric, TOK_QUIT, ":Restart by %s", 
		source->nick);
	irc_send(bot.serverNumeric, TOK_SQUIT, "%s 0 :Restart by %s", 
		bot.server->name, source->nick);
	
	loadconf();
}


void u_rehash(struct User* source, char **parv, int parc) {
	notice(source->numeric, "Rehashing from %s", FILE_CONF);
	loadconf();
}


void u_time(struct User* source, char **parv, int parc) {
	time_t currentTime = time(NULL);
	notice(source->numeric, "%cTIME %s (%ld)%c", CTCP_CHAR, ctime(&currentTime), time(&currentTime), CTCP_CHAR);
}
