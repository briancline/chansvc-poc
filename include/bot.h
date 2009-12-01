#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <ctype.h>
#include <errno.h>
#include <sys/time.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <proto.h>

#define BadPtr(x) (!(x) || (*(x) == '\0'))
#define FILE_CONF "w.conf"
#define FILE_LOG "w.log"
#define CTCP_CHAR '\001'
#define MAXLEN 512     /* Max line length */
#define MAXBUF 1024    /* Max buffer length */
#define MAXUSERS 100   /* Max # of nicks */
#define MAXSERVERS 20  /* Max # of servers */
#define NICKLEN 31     /* Should be NICKLEN+1 to allow for \0 */
#define NUMNICKBASE 64
#define WAITSEC 20
#define UWAITSEC 0
#define true 1;
#define false 0;

#include <structs.h>
#include <globals.h>
