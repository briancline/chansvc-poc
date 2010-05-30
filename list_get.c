#include <bot.h>

struct User *getUser(char *numeric) {
	struct User *userptr = users;
	
	while(userptr) {
		if(!strcmp(userptr->numeric, numeric))
			return userptr;
		userptr = userptr->next;
	}
	return 0; // This should never happen
}


struct Server *getServer(char *numeric) {
	//printf("getServer('%s'/%d)\n", numeric, (int)strlen(numeric));
	struct Server *servptr = servers;
	
	while(servptr) {
		//printf("		'%s'/%d\n", servptr->numeric, (int)strlen(servptr->numeric));
		if(!strcmp(servptr->numeric, numeric))
			return servptr;
		servptr = servptr->next;
	}
	return 0;
}


struct Channel *getChannel(char *name) {
	struct Channel *chanptr = channels;
	
	while(chanptr) {
		if(!strcasecmp(chanptr->name, name))
			return chanptr;
		chanptr = chanptr->next;
	}
	return 0;
}


struct User *getUserByNick(char *nick) {
	struct User *userptr = users;
	
	while(userptr) {
		if(!strcasecmp(userptr->nick, nick))
			return userptr;
		userptr = userptr->next;
	}
	return 0;
}


struct Server *getServerByNum(char *server) {
	struct Server *servptr = servers;
	
	while(servptr) {
		if(!strcasecmp(servptr->name, server))
			return servptr;
		servptr = servptr->next;
	}
	return 0;
}