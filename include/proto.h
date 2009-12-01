int get_connection(char *hostname, int port);
int readln();
int read_from_socket(int sock, char *buffer);
int writeln(char *buffer);
int writeln2(int sock, char *buffer);
int send_to_socket(int sck, char *format, ...);
int ssend(char *format, ...);
int notify(char *format, ...);
int notice(char *nick, char *format, ...);

void sig_segv();
void sig_int();
void sig_term();
void sig_hup();
void sig_bus();

void loadconf();
void bot_init();
void parse(char *line);
void parse_serv(fd_set *fds);

void parse_server(char **parv, int parc);
void parse_burst(char **parv, int parc);
void parse_eob(char **parv, int parc);
void parse_eob_ack(char **parv, int parc);
void parse_ping(char **parv, int parc);
void parse_squit(char **parv, int parc);
void parse_pass(char **parv, int parc);
void parse_nick(char **parv, int parc);
void parse_mode(char **parv, int parc);
void parse_quit(char **parv, int parc);
void parse_kill(char **parv, int parc);
void parse_join(char **parv, int parc);
void parse_part(char **parv, int parc);
void parse_create(char **parv, int parc);
void parse_privmsg(char **parv, int parc);
void parse_admin(char **parv, int parc);
void parse_version(char **parv, int parc);

int parse_line(char *str, char **parv);
char *join_array(char **parv, int start, int end);
void strip_newline(char *string);
char *strupr(char *str);
char *strlwr(char *str);

struct nickinfo *get_user(char* numeric);
struct servinfo *get_serv(char numeric);
struct nickinfo *get_usernum(char *nick);
struct servinfo *get_servnum(char *server);

void add_nick(char *nick, char *ident, char *host, char *modes, char *numeric);
void add_server(char *name, char num, char upnum);
void rem_nick(char *nick);
void rem_server(char *name);
void rem_nicks_byserv(char *server);
void rem_servs_byserv(char *server);

void u_traverse(char **parv, int parc);
void u_whois(char **parv, int parc);
void u_raw(char **parv, int parc);
void u_ping(char **parv, int parc);
void u_version(char **parv, int parc);
void u_die(char **parv, int parc);
void u_restart(char **parv, int parc);
void u_rehash(char **parv, int parc);
void u_time(char **parv, int parc);

void send_help(char *nick, char *command);
void send_syntax(char *nick, char *command);
