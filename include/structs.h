#ifndef __STRUCTS_H
#define __STRUCTS_H

struct User {
	char nick[NICKLEN];
	char ident[20];
	char host[100];
	char modes[10];
	char realName[100];
	char numeric[4];
	int isoper;
	struct Server *server;
	struct User *next;
};

struct Server {
	char name[100];
	char numeric[2];
	int numericInt;
	char description[100];
	struct Server *uplink;
	struct Server *next;
};

struct Channel {
	char name[100];
	char modes[50];
	time_t create_ts;
	struct Channel *next;
};

struct Bot {
	char nick[NICKLEN];
	char ident[20];
	char host[100];
	char serverDescription[50];
	char realName[50];
	char modes[10];
	char debugChan[50];
	char protoChan[50];
	char version[70];
	
	struct Server *uplink;
	struct Server *server;
	
	char serverNumeric[3];
	int  serverNumericInt;
	char numeric[6];
	int  numericInt;
	
	char uplinkHost[100];
	int uplinkPort;
	char uplinkPassword[50];
	
	long start;
	int active;
};

struct ProtocolHandler {
	char *cmd;
	void (*run)(char **, int);
};

struct CommandHandler {
	char *cmd;
	void (*run)(struct User*, char **, int);
	int level;
	int args;
};


/** Structure to store an IP address. */
struct irc_in_addr
{
  unsigned short in6_16[8]; /**< IPv6 encoded parts, little-endian. */
};


#endif //__STRUCTS_H
