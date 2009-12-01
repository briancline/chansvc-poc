#include <bot.h>

void send_help(char *nick, char *command) {
	FILE *fp;
	char *filename, *buffer;
	struct nickinfo nickptr = get_nicknum(nick);
	
	sprintf(filename, "help/%s", command);
	
	if(!nickptr)
		return;
	if(fp = fopen(filename, "r") == NULL)
		notice(nickptr->nick, "Help for command %s unavailable.", command);
		
	while(fgets(buffer, 100, fp)) {
		notice (nickptr->nick, "%s", buffer);
	}
	
	fclose(fp);
}


void send_syntax(char *nick, char *command) {
	FILE *fp;
	char *filename, *buffer;
	struct nickinfo nickptr = get_nicknum(nick);
	
	sprintf(filename, "help/%s", command);
	
	if(!nickptr)
		return;
	if(fp = fopen(filename, "r") == NULL) {
		notice(nickptr->nick, "Invalid syntax.");
		notice(nickptr->nick, "Help for command %s unavailable.", strupr(command));
	}
		
	fgets(buffer, 100, fp);
	notice(nickptr->nick, "%s", buffer);
	fclose(fp);
}
