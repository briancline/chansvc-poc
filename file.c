#include <bot.h>

void loadconf() {
	FILE *fp;
	char buffer[100], *field = NULL, *ptr = NULL;
	buffer[0] = '\0';
	
	if((fp = fopen(FILE_CONF, "r")) == NULL) exit(0);
	
	while(fgets(buffer, 100, fp)) {
		if(buffer[0] == '*' || buffer[0] == '\n') continue;
		if(field = strchr(buffer, ' ')) *field++ = '\0';

		strip_newline(field);
		
		if(!strcmp(buffer, "RSERVER"))
			strcpy(bot.remotehost, field);
		if(!strcmp(buffer, "RPORT"))
			bot.remoteport = atoi(field);
		if(!strcmp(buffer, "RPASS"))
			strcpy(bot.password, field);
		if(!strcmp(buffer, "NICK"))
			strcpy(bot.nick, field);
		if(!strcmp(buffer, "IDENT"))
			strcpy(bot.ident, field);
		if(!strcmp(buffer, "HOST"))
			strcpy(bot.host, field);
		if(!strcmp(buffer, "COMMENT"))
			strcpy(bot.nickinfo, field);
		if(!strcmp(buffer, "MODES"))
			strcpy(bot.modes, field);
		if(!strcmp(buffer, "SERVER"))
			strcpy(bot.server->name, field);
		if(!strcmp(buffer, "SCOMMENT"))
			strcpy(bot.servinfo, field);
		if(!strcmp(buffer, "DEBUGCHAN"))
			strcpy(bot.debugChan, field);
		if(!strcmp(buffer, "PROTOCHAN"))
			strcpy(bot.protoChan, field);
		if(!strcmp(buffer, "NUM")) {
			bot.snum = atoi(field);
			bot.scnum = convert2y[bot.snum];
			bot.server->numeric = bot.scnum;
		}
		if(!strcmp(buffer, "NICKNUM")) {
			bot.nnum = atoi(field);
			strcpy(bot.ncnum, field);
		}
	}
	bot.fullnum[0] = bot.scnum;
	bot.fullnum[1] = '\0';
	strcat(bot.fullnum, bot.ncnum);
	
	fclose(fp);
}
