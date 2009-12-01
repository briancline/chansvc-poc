#include <bot.h>

void parse(char *line) {
	int i = 0;
	char *cmd = NULL, *who = NULL, *rest = NULL, parc = 0;
	char *parv[100];
	char ltmp[strlen(line)];
	
	strip_newline(line);
	strcpy(ltmp, line);
	ssend(":%s PRIVMSG %s :%s\n", bot.nick, bot.protoChan, line);
	parc = parse_line(line, parv);
	
	if(!parv[1]) return;
	
	if(!strcmp(parv[0], "SERVER")) {
		add_server(parv[1], parv[6][0], bot.server->numeric);
		bot.uplink = get_serv(parv[6][0]);
		
		add_server(bot.server->name, bot.scnum, bot.uplink->numeric);
		add_nick(bot.nick, bot.ident, bot.host, bot.modes, bot.fullnum);
		
		bot.uplink->uplink = bot.server;
		bot.server->uplink = bot.uplink;
		
		notify("SRV (*) %s\n", parv[1]);
		return;
	}
	
	cmd = parv[1];
	if(parv[0][0] == ':')
		*parv[0]++;
	if(parc >= 4 && parv[3][0] == ':')
		*parv[3]++;
	if(!strcmp(parv[0], "PASS"))
		cmd = parv[0];
	
	
	for(i = 0; parsetable[i].cmd; i++) {
		if(!strcmp(parsetable[i].cmd, cmd)) {
			parsetable[i].run(parv, parc);
			return;
		}
	}
}


void parse_server(char **parv, int parc) {
	add_server(parv[2], parv[7][0], parv[0][0]);
}	


void parse_burst(char **parv, int parc) {
//	notify("BST (%c) %s", parv[0][0], parv[2]);
}


void parse_eob(char **parv, int parc) {
	if(get_serv(parv[0][0]) == bot.uplink) {
		ssend("%c EA\n", bot.scnum);
		notify("EOB (%c) from uplink", parv[0][0]);
	}
}


void parse_eob_ack(char **parv, int parc) {
	notify("EA from %s", get_serv(parv[0][0]));
}


void parse_ping(char **parv, int parc) {
	ssend(":%s PONG %s %s\n", bot.server->name, bot.server->name, parv[1]);
}


void parse_squit(char **parv, int parc) {
	rem_servs_byserv(parv[2]);
}


void parse_pass(char **parv, int parc) {
	bot_burst();
}


void parse_nick(char **parv, int parc) {
	struct nickinfo *nick = nicks;
	
	if(parc >= 10) {
		if(parv[7][0] == '+') {
			*parv[7]++;
			add_nick(parv[2], parv[5], parv[6], parv[7], parv[9]);
		}
		else {
			add_nick(parv[2], parv[5], parv[6], "+", parv[8]);
		}
	}
	else {
		while(nick) {
			if(!strcmp(nick->numeric, parv[0])) {
				notify("NCK %s -> %s", nick, parv[2]);
				strcpy(nick->nick, parv[2]);
				return;
			}
			nick = nick->next;
		}
	}
}


void parse_mode(char **parv, int parc) {
}


void parse_quit(char **parv, int parc) {
	notify("QT %s", parv[0]);
	rem_nick(parv[0]);
}


void parse_kill(char **parv, int parc) {
	rem_nick(parv[2]);
	notify("QT %s (kill)", parv[2]);
}


void parse_join(char **parv, int parc) {
	notify("JN %s %s", parv[0], parv[2]);
}


void parse_part(char **parv, int parc) {
	notify("PT %s %s", parv[0], parv[2]);
}


void parse_create(char **parv, int parc) {
	struct nickinfo *user;
	
	user = get_user(parv[0]);
	notify("CRT %s %s", user->nick, parv[2]);
}


void parse_privmsg(char **parv, int parc) {
	int i = 0;
	
	notify("CMD: %s (%d) %s", parv[0], parc, parv[3]);
	
	for(i = 0; commands[i].cmd; i++) {
		if(!strcasecmp(commands[i].cmd, parv[3])) {
			if((parc-3) >= commands[i].args) {
				commands[i].run(parv, parc);
				return;
			}
			else {
				send_syntax(parv[0], commands[i].cmd);
				return;
			}
		}
	}
}


void parse_admin(char **parv, int parc) {
	ssend(":%s 256 %s :Administrative info about %s\n", bot.server->name, parv[0]);
}


void parse_version(char **parv, int parc) {
	ssend(":%s 351 %s %s %s :http://mercury.darktech.org/cs/\n", bot.server->name, parv[0], bot.version, bot.server->name);
}
