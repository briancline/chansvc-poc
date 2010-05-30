#define TOK_ERROR "ERROR"
#define CMD_ERROR "ERROR"
#define TOK_PASS "PASS"
#define CMD_PASS "PASS"
#define TOK_SERVER "S"
#define CMD_SERVER "SERVER"
#define TOK_BURST "B"
#define TOK_END_OF_BURST "EB"
#define TOK_END_OF_BURST_ACK "EA"
#define TOK_PING "G"
#define TOK_PONG "Z"
#define TOK_SQUIT "SQ"
#define TOK_NICK "N"
#define TOK_MODE "M"
#define TOK_QUIT "Q"
#define TOK_KILL "D"
#define TOK_JOIN "J"
#define TOK_PART "L"
#define TOK_CREATE "C"
#define TOK_PRIVMSG "P"
#define TOK_NOTICE "O"
#define TOK_ADMIN "AD"
#define TOK_VERSION "V"

#ifdef DEF_GLOBALS

int socketfd;
int logfd;
char line[MAXLEN];
char linebuff[100];
char strbuff[70];
struct Bot bot;
struct Server *servers = NULL;
struct User *users = NULL;
struct Channel *channels = NULL;

struct ProtocolHandler parsetable[] = {
	{ CMD_ERROR,              parse_error   },
	{ TOK_PASS,               parse_pass    },
	{ CMD_SERVER,             parse_server_uplink  },
	{ TOK_SERVER,	           parse_server  },
	{ TOK_BURST,              parse_burst   },
	{ TOK_END_OF_BURST,       parse_eob     },
	{ TOK_END_OF_BURST_ACK,   parse_eob_ack },
	{ TOK_PING,               parse_ping    },
	{ TOK_PONG,               parse_ping    },
	{ TOK_SQUIT,              parse_squit   },
	{ TOK_NICK,               parse_nick    },
	{ TOK_MODE,               parse_mode    },
	{ TOK_QUIT,               parse_quit    },
	{ TOK_KILL,               parse_kill    },
	{ TOK_JOIN,               parse_join    },
	{ TOK_PART,               parse_part    },
	{ TOK_CREATE,             parse_create  },
	{ TOK_PRIVMSG,            parse_privmsg },
	{ TOK_ADMIN,              parse_admin   },
	{ TOK_VERSION,            parse_version },
	{ NULL,                   NULL          }
};


struct CommandHandler commands[] = {
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
extern int logfd;
extern char line[];
extern char linebuff[];
extern char strbuff[];
extern struct Bot bot;
extern struct Server *servers;
extern struct User *users;
extern struct Channel *channels;
extern struct ProtocolHandler parsetable[];
extern struct CommandHandler commands[];

#endif //DEF_GLOBALS


/** Evaluate to non-zero if \a ADDR (of type struct irc_in_addr) is an IPv4 address. */
#define irc_in_addr_is_ipv4(ADDR) (!(ADDR)->in6_16[0] && !(ADDR)->in6_16[1] && !(ADDR)->in6_16[2] \
                                   && !(ADDR)->in6_16[3] && !(ADDR)->in6_16[4] \
                                   && ((!(ADDR)->in6_16[5] && (ADDR)->in6_16[6]) \
                                       || (ADDR)->in6_16[5] == 65535))


/** Maximum length of a full user numnick. */
#define NUMNICKLEN 5            /* strlen("YYXXX") */
/** Number of bits encoded in one numnick character. */
#define NUMNICKLOG 6
/** Bitmask to select value of next numnick character. */
#define NUMNICKMASK 63          /* (NUMNICKBASE-1) */
/** Number of servers representable in a numnick. */
#define NN_MAX_SERVER 4096      /* (NUMNICKBASE * NUMNICKBASE) */
/** Number of clients representable in a numnick. */
#define NN_MAX_CLIENT 262144    /* NUMNICKBASE ^ 3 */

