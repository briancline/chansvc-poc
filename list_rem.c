#include <bot.h>

void rem_server(char *name) {
	struct servinfo *servptr = servers, *prevsrv, *nextsrv;
	
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
	return; // This should never happen
}


void rem_nick(char *nick) {
	struct nickinfo *nicklist = nicks, *prevnick, *nextnick;
	
	strcpy(nick, strlwr(nick));
	
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
	return; // This should never happen
}


void rem_servs_byserv(char *server) {
	struct servinfo *servptr = servers, *prevsrv = servers;
	
	rem_nicks_byserv(server);
	
	while(servptr) {
		if(servptr->uplink && !strcasecmp(servptr->uplink->name, server)) {
			if(prevsrv != servptr) prevsrv->next = servptr->next;
			notify("removed server %s from %s", servptr->name, servptr->uplink);
			rem_nicks_byserv(servptr->name);
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


void rem_nicks_byserv(char *server) {
	struct nickinfo *nickptr = nicks, *prevnick, *nextnick;
	
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
