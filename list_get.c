#include <bot.h>

struct nickinfo *get_user(char* numeric) {
	struct nickinfo *userptr = nicks;
	
	while(userptr) {
		if(!strcmp(userptr->numeric, numeric))
			return userptr;
		userptr = userptr->next;
	}
	return 0; // This should never happen
}


struct servinfo *get_serv(char numeric) {
	struct servinfo *servptr = servers;
	
	while(servptr) {
		if(servptr->numeric == numeric)
			return servptr;
		servptr = servptr->next;
	}
	return 0;
}


struct nickinfo *get_usernum(char *nick) {
	struct nickinfo *userptr = nicks;
	
	while(userptr) {
		if(!strcasecmp(userptr->nick, nick))
			return userptr;
		userptr = userptr->next;
	}
	return 0;
}


struct servinfo *get_servnum(char *server) {
	struct servinfo *servptr = servers;
	
	while(servptr) {
		if(!strcasecmp(servptr->name, server))
			return servptr;
		servptr = servptr->next;
	}
	return 0;
}