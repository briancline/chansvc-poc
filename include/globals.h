#ifdef DEF_GLOBALS
int socketfd;
int log;
char line[MAXLEN];
char linebuff[100];
char strbuff[70];
struct botinfo bot;
struct servinfo *servers = NULL;
struct nickinfo *nicks = NULL;
char convert2y[NUMNICKBASE] = {
  'A','B','C','D','E','F','G','H',
  'I','J','K','L','M','N','O','P',
  'Q','R','S','T','U','V','W','X',
  'Y','Z','a','b','c','d','e','f',
  'g','h','i','j','k','l','m','n',
  'o','p','q','r','s','t','u','v',
  'w','x','y','z','0','1','2','3',
  '4','5','6','7','8','9','[',']'
};
unsigned int convert2n[] = {
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  52,53,54,55,56,57,58,59,60,61, 0, 0, 0, 0, 0, 0, 
   0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,
  15,16,17,18,19,20,21,22,23,24,25,62, 0,63, 0, 0,
   0,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
  41,42,43,44,45,46,47,48,49,50,51, 0, 0, 0, 0, 0,

   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
struct PARSECOM parsetable[] = {
	{ "SERVER",	      parse_server  },
	{ "BURST",        parse_burst   },
	{ "END_OF_BURST", parse_eob     },
	{ "EOB_ACK",      parse_eob_ack },
	{ "PING",         parse_ping    },
	{ "SQUIT",        parse_squit   },
	{ "PASS",         parse_pass    },
	{ "NICK",         parse_nick    },
	{ "MODE",         parse_mode    },
	{ "QUIT",         parse_quit    },
	{ "KILL",         parse_kill    },
	{ "JOIN",         parse_join    },
	{ "PART",         parse_part    },
	{ "CREATE",       parse_create  },
	{ "PRIVMSG",      parse_privmsg },
	{ "ADMIN",        parse_admin   },
	{ "VERSION",      parse_version },
	{ NULL,           NULL          }
};

struct USERCOM commands[] = {
	{ "WHOIS",           u_whois       , 0,    1 },
	{ "RAW",             u_raw         , 0,    1 },
	{ "TL",              u_traverse    , 0,    0 },
	{ "DIE",             u_die         , 1000, 0 },
	{ "RESTART",         u_restart     , 1000, 0 },
	{ "REHASH",          u_rehash      , 1000, 0 },
	{ "\001PING",        u_ping        , 0,    0 },
	{ "\001VERSION\001", u_version     , 0,    0 },
	{ "\001TIME\001",    u_time        , 0,    0 },
	{ NULL,              NULL          , 0,    0 }
};

////////////////////////////////////////////////////
#else
////////////////////////////////////////////////////

extern int socketfd;
extern int log;
extern char line[];
extern char linebuff[];
extern char strbuff[];
extern struct botinfo bot;
extern struct servinfo *servers;
extern struct nickinfo *nicks;
extern char convert2y[];
extern unsigned int convert2n[];
extern struct PARSECOM parsetable[];
extern struct USERCOM commands[];
#endif