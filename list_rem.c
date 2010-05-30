#include <bot.h>

void rem_server(char *name) {
	struct Server *servptr = servers, *prevsrv, *nextsrv;
	
	while(servptr) {
		if(!strcasecmp(servptr->name, name)) {
			nextsrv = servptr->next;
			prevsrv->next = nextsrv;
			notify("removed server %s from %s", servptr->name, servptr->uplink->name);
			free(servptr);
			return;
		}
		prevsrv = servptr;
		servptr = servptr->next;
	}
	
	return;
}


void rem_nick(char *nick) {
	struct User *nicklist = users, *prevnick, *nextnick;
	
	strcpy(nick, toLower(nick));
	
	while(nicklist) {
		if(!strcasecmp(nicklist->nick, nick)) {
			nextnick = nicklist->next;
			prevnick->next = nextnick;
			notify("removed %s from %s", nicklist->nick, nicklist->server->name);
			free(nicklist);
			return;
		}
		prevnick = nicklist;
		nicklist = nicklist->next;
	}
	
	return;
}


void rem_channel(char *name) {
	struct Channel *chanlist = channels, *prevchan, *nextchan;
	
	while(chanlist) {
		if(!strcasecmp(chanlist->name, name)) {
			nextchan = chanlist->next;
			prevchan->next = nextchan;
			notify("removed %s", chanlist->name);
			free(chanlist);
			return;
		}
		prevchan = chanlist;
		chanlist = chanlist->next;
	}
	
	return;
}


void rem_servs_byserv(char *server) {
	struct Server *servptr = servers, *prevsrv = servers;
	
	rem_users_byserv(server);
	
	while(servptr) {
		if(servptr->uplink && !strcasecmp(servptr->uplink->name, server)) {
			if(prevsrv != servptr) prevsrv->next = servptr->next;
			notify("removed server %s from %s", servptr->name, servptr->uplink);
			rem_users_byserv(servptr->name);
			rem_servs_byserv(servptr->name);
			free(servptr);
			servptr = servptr->next;
		}
		else {
			prevsrv = servptr;
			servptr = servptr->next;
		}
	}
	rem_server(server);
}


void rem_users_byserv(char *server) {
	struct User *nickptr = users, *prevnick, *nextnick;
	
	while(nickptr) {
		if(!strcasecmp(nickptr->server->name, server)) {
			nextnick = nickptr->next;
			prevnick->next = nextnick;
			notify("removed nick %s from %s", nickptr->nick, nickptr->server->name);
			free(nickptr);
			nickptr = nextnick;
		}
		else {
			prevnick = nickptr;
			nickptr = nickptr->next;
		}
	}
	return;
}
