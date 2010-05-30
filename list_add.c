#include <bot.h>

struct Server* add_server(char *name, char *num, char *upnum, char *desc) {
	struct Server *newserv;
	newserv = (struct Server *) calloc(1, sizeof(struct Server));
	
	irc_strncpy(newserv->numeric, num, 2);
	strcpy(newserv->name, name);
	strcpy(newserv->description, desc);
	newserv->numericInt = base64toint(num);
	newserv->next = servers;
	servers = newserv;
	
	if(upnum)
		newserv->uplink = getServer(upnum);
	
	if(newserv->uplink)
		notify("SRV %s:%s -> %s:%s", newserv->uplink->numeric, newserv->uplink->name, newserv->numeric, newserv->name);
	else
		printf("SRV %s:%s\n", newserv->numeric, newserv->name);
	
	return newserv;
}

struct User* add_user(char *nick, char *ident, char *host, char *modes, char *numeric, char *realName) {
	struct User *newuser;
	
	newuser = (struct User *) calloc(1, sizeof(struct User));
	
	strcpy(newuser->nick, nick);
	strcpy(newuser->ident, ident);
	strcpy(newuser->host, host);
	strcpy(newuser->numeric, numeric);
	strcpy(newuser->realName, realName);
	
	char serverNumeric[3];
	irc_strncpy(serverNumeric, numeric, 2);
	newuser->server = getServer(serverNumeric);
	newuser->isoper = 0;
	if(strcmp(modes, "+")) {
		strcpy(newuser->modes, modes);
		newuser->isoper = strchr(modes, 'o') ? 1 : 0;
	}
	
	notify("USR: %s (%s %s@%s) %s/%d %s", 
		newuser->nick, newuser->numeric, newuser->ident, newuser->host, 
		newuser->modes, newuser->isoper, newuser->server->name);

	newuser->next = users;
	users = newuser;
	
	return newuser;
}

struct Channel* add_channel(char *name, char* modes, time_t create_ts)
{
	struct Channel *chan;
	
	chan = (struct Channel *) calloc(1, sizeof(struct Channel));
	
	strcpy(chan->name, name);
	chan->create_ts = create_ts;
	
	if(modes) {
		if(*modes == '+')
			*modes++;
		
		strcpy(chan->modes, modes);
	}
	
	notify("CHAN: %s (%s), epoch %lu", chan->name, chan->modes, chan->create_ts);
	
	chan->next = channels;
	channels = chan;
	
	return chan;
}


void print_user(struct User* u) {
	printf("USER 0x%x\n", u);
	printf("\t numeric[%2d]: %s\n"
	       "\t    nick[%2d]: %s\n"
			 "\t   ident[%2d]: %s\n"
			 "\t    host[%2d]: %s\n"
			 "\t   modes[%2d]: %s\n"
			 "\trealName[%2d]: %s\n"
			 "\t       isoper: %0d\n"
			 "\t       server: 0x%x\n"
			 "\t         next: 0x%x\n",
			(int)strlen(u->numeric), u->numeric,
			(int)strlen(u->nick), u->nick,
			(int)strlen(u->ident), u->ident,
			(int)strlen(u->host), u->host,
			(int)strlen(u->modes), u->modes,
			(int)strlen(u->realName), u->realName,
			u->isoper,
			u->server,
			u->next);
}

void print_server(struct Server* s) {
	printf("SERVER 0x%x\n", s);
	printf("\t    numeric[%2d]: %s\n"
	       "\t       name[%2d]: %s\n"
			 "\tdescription[%2d]: %s\n"
			 "\t      numericInt: %0d\n"
			 "\t          uplink: 0x%x\n"
			 "\t            next: 0x%x\n",
			(int)strlen(s->numeric), s->numeric,
			(int)strlen(s->name), s->name,
			(int)strlen(s->description), s->description,
			s->numericInt,
			s->uplink,
			s->next);
}

void print_channel(struct Channel* c) {
	printf("CHANNEL 0x%x\n", c);
	printf("\t       name[%2d]: %s\n"
	       "\t      modes[%2d]: %s\n"
			 "\t       create_ts: %lu\n"
			 "\t            next: 0x%x\n",
			(int)strlen(c->name), c->name,
			(int)strlen(c->modes), c->modes,
			c->create_ts,
			c->next);
}

void print_users() {
	printf("==========================================\n");
	struct User* u = users;
	while(u) {
		print_user(u);
		u = u->next;
	}
	printf("==========================================\n");
}
void print_servers() {
	printf("==========================================\n");
	struct Server* s = servers;
	while(s) {
		print_server(s);
		s = s->next;
	}
	printf("==========================================\n");
}
void print_channels() {
	printf("==========================================\n");
	struct Channel* c = channels;
	while(c) {
		print_channels(c);
		c = c->next;
	}
	printf("==========================================\n");
}
