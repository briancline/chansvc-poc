#ifndef __PROTO_H
#define __PROTO_H

int get_connection(char *hostname, int port);
int readln();
int read_from_socket(int sock, char *buffer);
int writeln(char *buffer);
int writeln2(int sock, char *buffer);
int send_to_socket(int sck, char *format, ...);
int ssend(char *format, ...);
int irc_send(char *source, char *token, char *argFormat, ...);
int irc_sendToken(char *source, char *token);
int notify(char *format, ...);
int notice(char *nick, char *format, ...);


extern unsigned int base64toint(const char *str);
extern const char *inttobase64(char *buf, unsigned int v, unsigned int count);
extern const char *iptobase64(char *buf, const struct irc_in_addr* addr, unsigned int count, int v6_ok);
extern void base64toip(const char *s, struct irc_in_addr* addr);

void sig_segv();
void sig_int();
void sig_term();
void sig_hup();
void sig_bus();

void loadconf();
void bot_init();
void burst_servers();
void burst_glines();
void burst_jupes();
void burst_users();
void burst_channels();
void parse(char *line);
void parse_serv(fd_set *fds);

void parse_error(char ** parv, int parc);
void parse_server(char **parv, int parc);
void parse_server_uplink(char **parv, int parc);
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

int parse_line(char *str, char **parv, int stopAtColon);
char *join_array(char **parv, int start, int end);
void strip_newline(char *string);
char *toUpper(char *str);
char *toLower(char *str);
char *irc_strncpy(char *s1, const char *s2, size_t n);

struct User *getUser(char *numeric);
struct Server *getServer(char *numeric);
struct Channel *getChannel(char *name);
struct User *getUserByNick(char *nick);
struct Server *getServerByNum(char *server);

struct User* add_user(char *nick, char *ident, char *host, char *modes, char *numeric, char *realName);
struct Server* add_server(char *name, char *num, char *upnum, char *desc);
struct Channel* add_channel(char *name, char* modes, time_t create_ts);
void rem_nick(char *nick);
void rem_server(char *name);
void rem_channel(char *name);
void rem_users_byserv(char *server);
void rem_servs_byserv(char *server);

void print_server(struct Server* s);
void print_user(struct User* u);
void print_channel(struct Channel* c);
void print_servers();
void print_users();
void print_channels();

void u_traverse(struct User* source, char **parv, int parc);
void u_whois(struct User* source, char **parv, int parc);
void u_raw(struct User* source, char **parv, int parc);
void u_ping(struct User* source, char **parv, int parc);
void u_version(struct User* source, char **parv, int parc);
void u_die(struct User* source, char **parv, int parc);
void u_restart(struct User* source, char **parv, int parc);
void u_rehash(struct User* source, char **parv, int parc);
void u_time(struct User* source, char **parv, int parc);

void send_help(char *nick, char *command);
void send_syntax(char *nick, char *command);

#endif //__PROTO_H
