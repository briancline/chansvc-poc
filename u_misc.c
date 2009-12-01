#include <bot.h>

void u_whois(char **parv, int parc) {
	char *nick = parv[0], *who = parv[4];
	struct nickinfo *nickptr = nicks;
	
	while(nickptr) {
		if(!strcasecmp(nickptr->nick, who)) {
			notice(nick, "Full host      : %s!%s@%s", nickptr->nick, nickptr->ident, nickptr->host);
			notice(nick, "On server      : %s", nickptr->server->name);
			if(nickptr->isoper) {
				notice(nick, "Access         : Is an IRC Operator");
			}
			notice(nick, "Numeric        : %s", nickptr->numeric);
			notice(nick, "Server Numeric : %c (%d)", nickptr->server->numeric, convert2n[nickptr->server->numeric]);
			return;
		}
		nickptr = nickptr->next;
	}
	notice(nick, "User %s is not online.\n", who);
	return;
}


void u_raw(char **parv, int parc) {
	char *rest = join_array(parv, 4, parc-1);
	
	ssend("%s\n", rest);
}


void u_ping(char **parv, int parc) {
	struct nickinfo *nickptr = get_usernum(parv[0]);
	
	ssend(":%s NOTICE %s :%cPING %s\n", bot.nick, nickptr->numeric, CTCP_CHAR, parv[4]);
}


void u_version(char **parv, int parc) {
	struct nickinfo *nickptr = get_usernum(parv[0]);
	
	ssend(":%s NOTICE %s :%cVERSION %s%c\n", bot.nick, nickptr->numeric, CTCP_CHAR, bot.version, CTCP_CHAR);
}


void u_traverse(char **parv, int parc) {
	struct nickinfo *nsrc = nicks;
	struct servinfo *ssrc = servers;
	
	notify("Traversing nicks linked-list");
	while(nsrc) {
		notify("(%d) nicks->nick = %s", nsrc, nsrc->nick);
		nsrc = nsrc->next;
	}
	notify("(done)");
	
	notify("Traversing servers linked-list");
	while(ssrc) {
		notify("servers->name = %s", ssrc, ssrc->name);
		notify("         uplink: %s", ssrc->uplink->name);
		notify("         next: %s", ssrc->next->name);
		ssrc = ssrc->next;
	}
	notify("(done)");
}


void u_die(char **parv, int parc) {
	ssend(":%s QUIT :Die by %s", bot.nick, parv[0]);
}


void u_restart(char **parv, int parc) {
	ssend(":%s QUIT :Restart by %s", bot.nick, parv[0]);
	ssend(":%s SQUIT %s 0 :Restarting (%s)", bot.server->name, bot.server->name, parv[0]);
	loadconf();
	
}


void u_rehash(char **parv, int parc) {
	notice(parv[0], "Rehashing from %s", FILE_CONF);
	loadconf();
}


void u_time(char **parv, int parc) {
	struct nickinfo *nickptr = get_usernum(parv[0]);
	
	ssend(":%s NOTICE %s :%cTIME %s (%ld)%c\n", bot.nick, nickptr->numeric, CTCP_CHAR, ctime(time(NULL)), time(NULL), CTCP_CHAR);
}
