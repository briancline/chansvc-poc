#include <bot.h>

void parse(char *line) {
	int i = 0, parc = 0;
	char *cmd = NULL;
	char *parv[100];
	char ltmp[strlen(line)];
		
	strip_newline(line);
	strcpy(ltmp, line);
	printf("[RECV] %s\n", line);
	parc = parse_line(line, parv, 1);
	
	for(i = 0; i < parc; i++) {
		printf("		parv[%d] = '%s'\n", i, parv[i]);
	}
	
	if(!parv[1])
		return;
	
	cmd = parv[1];
	
	if(!strcmp(parv[0], CMD_SERVER)
			|| !strcmp(parv[0], CMD_ERROR) 
			|| !strcmp(parv[0], CMD_PASS)) {
		cmd = parv[0];
	}
	
	for(i = 0; parsetable[i].cmd; i++) {
		if(!strcmp(parsetable[i].cmd, cmd)) {
			parsetable[i].run(parv, parc);
			return;
		}
	}
}


void parse_error(char **parv, int parc) {
	printf("Error from uplink: %s\n", parv[1]);
	exit(0);
}


void parse_server_uplink(char **parv, int parc) {
	char numeric[3];
	irc_strncpy(numeric, parv[6], 2);
	
	print_servers();
	
	printf("Numeric is %s/%d.\n", numeric, (int)strlen(numeric));
	bot.uplink = add_server(parv[1], numeric, bot.server->numeric, parv[parc-1]);
	
	print_servers();
	
	//bot.uplink->uplink = bot.server;
	//bot.server->uplink = bot.uplink;
	
	notify("SRV (*) %s\n", getServer(numeric)->name);
	
	burst_servers();
	burst_glines();
	burst_jupes();
	burst_users();
	burst_channels();
	irc_sendToken(bot.serverNumeric, TOK_END_OF_BURST);
	
	return;
}


void parse_server(char **parv, int parc) {
	add_server(parv[2], parv[7], parv[0], parv[parc-1]);
	print_servers();
}	


void parse_burst(char **parv, int parc) {
	char *modes = NULL;
	
	if(*parv[4] == '+')
		modes = parv[4];
	
	struct Channel *chan = add_channel(parv[2], modes, atol(parv[3]));
	
	notify("BST (%s) %s", parv[0], chan->name, chan->modes, chan->create_ts);
}


void parse_eob(char **parv, int parc) {
	if(getServer(parv[0]) == bot.uplink) {
		irc_sendToken(bot.serverNumeric, TOK_END_OF_BURST_ACK);
		notify("EOB (%s) from uplink", parv[0]);
	}
	else {
		notify("EOB (%s)", parv[0]);
	}
}


void parse_eob_ack(char **parv, int parc) {
	notify("EA from %s", getServer(parv[0]));
}


void parse_ping(char **parv, int parc) {
	irc_send(bot.server->numeric, TOK_PONG, "%s %s", 
		bot.server->numeric, parv[2]);
}


void parse_squit(char **parv, int parc) {
	rem_servs_byserv(parv[2]);
}


void parse_pass(char **parv, int parc) {
	// do nothing with uplink password...
}


void parse_nick(char **parv, int parc) {
	struct User *nick = users;
	
	if(parc >= 10) {
		char serverNum[3];
		irc_strncpy(serverNum, parv[0], 2);
		
		if(parv[7][0] == '+') {
			//*parv[7]++;
			// add_user(char *nick, char *ident, char *host, char *modes, char *numeric, char *realName)
			nick = add_user(parv[2], parv[5], parv[6], parv[7], parv[parc-2], parv[parc-1]);
		}
		else {
			nick = add_user(parv[2], parv[5], parv[6], "+", parv[parc-2], parv[parc-1]);
		}
		
		nick->server = getServer(serverNum);
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
	struct User *user;
	
	user = getUser(parv[0]);
	notify("CRT %s %s", user->nick, parv[2]);
}


void parse_privmsg(char **parv, int parc) {
	int i = 0;
	struct User* source = getUser(parv[0]);
	
	int carc = 0;
	char *carv[256];
	carc = parse_line(parv[3], carv, 0);
	printf("	carc: %d\n", carc);
	for(i = 0; i < carc; i++) {
		printf("	carv[%d] = '%s'\n", i, carv[i]);
	}
	
	notify("CMD: %s - %s (%d:%s)", source->nick, carv[0], parc, parv[3]);
	
	for(i = 0; commands[i].cmd; i++) {
		if(!strcasecmp(commands[i].cmd, carv[0])) {
			if((carc - 1) >= commands[i].args) {
				commands[i].run(source, carv, carc);
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
	ssend("%s 256 %s :Administrative info about %s\n", 
		bot.server->numeric, parv[0], bot.server->name);
}


void parse_version(char **parv, int parc) {
	ssend("%s 351 %s %s %s :http://mercury.darktech.org/cs/\n", 
		bot.server->numeric, parv[0], bot.version, bot.server->name);
}
