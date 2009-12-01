struct nickinfo {
	char nick[NICKLEN];
	char ident[20];
	char host[100];
	char modes[10];
	char numeric[4];
	int isoper;
	struct servinfo *server;
	struct nickinfo *next;
};

struct servinfo {
	char name[100];
	char numeric;
	struct servinfo *uplink;
	struct servinfo *next;
};

struct botinfo {
	char nick[NICKLEN];
	char ident[20];
	char host[100];
	char servinfo[50];
	char nickinfo[50];
	char modes[10];
	char debugChan[50];
	char protoChan[50];
	char version[70];
	
	struct servinfo *uplink;
	struct servinfo *server;
	
	char fullnum[4];
	char scnum;
	char ncnum[3];
	int snum;
	int nnum;
	
	char remotehost[100];
	int remoteport;
	char password[50];
	long start;
	int active;
};

struct PARSECOM {
	char *cmd;
	void (*run)(char **, int);
};

struct USERCOM {
	char *cmd;
	void (*run)(char **, int);
	int level;
	int args;
};
