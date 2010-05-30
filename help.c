#include <bot.h>

void send_help(char *numeric, char *command) {
	FILE *fp;
	char filename[128], buffer[128];
	struct User *nickptr = getUser(numeric);
	
	sprintf(filename, "help/%s", command);
	
	if(!nickptr)
		return;
	if(!(fp = fopen(filename, "r"))) {
		notice(nickptr->numeric, "Help for command %s unavailable.", toUpper(command));
		return;
	}
		
	while(fgets(buffer, 100, fp)) {
		notice (nickptr->numeric, "%s", buffer);
	}
	
	fclose(fp);
}


void send_syntax(char *numeric, char *command) {
	FILE *fp;
	char filename[128], buffer[128];
	struct User *nickptr = getUser(numeric);
	
	sprintf(filename, "help/%s", toLower(command));
	
	if(!nickptr)
		return;
	if(!(fp = fopen(filename, "r"))) {
		notice(nickptr->numeric, "Invalid syntax.");
		notice(nickptr->numeric, "Help for command %s unavailable.", toUpper(command));
		return;
	}
		
	fgets(buffer, 100, fp);
	notice(nickptr->numeric, "%s", buffer);
	fclose(fp);
}
