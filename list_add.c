#include <bot.h>

void add_server(char *name, char num, char upnum) {
	struct servinfo *newserv, *uplink;
	newserv = (struct servinfo *) calloc(1, sizeof(struct servinfo));
	
	strcpy(newserv->name, name);
	newserv->numeric = num;
	newserv->uplink = get_serv(upnum);
	newserv->next = servers;
	servers = newserv;
	
	if(newserv->uplink)
		notify("SRV %c:%s -> %s", newserv->uplink->numeric, newserv->uplink->name, newserv->name);
}

void add_nick(char *nick, char *ident, char *host, char *modes, char *numeric) {
	struct nickinfo *newuser;
	
	newuser = (struct nickinfo *) calloc(1, sizeof(struct nickinfo));
	
	strcpy(newuser->nick, nick);
	strcpy(newuser->ident, ident);
	strcpy(newuser->host, host);
	strcpy(newuser->numeric, numeric);
	newuser->server = get_serv(numeric[0]);
	newuser->isoper = 0;
	if(strcmp(modes, "+")) {
		strcpy(newuser->modes, modes);
		newuser->isoper = strchr(modes, 'o') ? 1 : 0;
	}
	
	ssend(":%s PRIVMSG %s :USR: %s (%s %s@%s) %s/%d %s\n", bot.nick, bot.debugChan, newuser->nick, newuser->numeric, newuser->ident, newuser->host, newuser->modes, newuser->isoper, newuser->server->name);

	newuser->next = nicks;
	nicks = newuser;
}
