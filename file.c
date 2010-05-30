#include <bot.h>

void loadconf() {
	FILE *fp;
	char buffer[100], *field = NULL;
	buffer[0] = '\0';
	
	if((fp = fopen(FILE_CONF, "r")) == NULL) exit(0);
	
	while(fgets(buffer, 100, fp)) {
		if(buffer[0] == '*' || buffer[0] == '\n' || buffer[0] == '\r')
			continue;
		if((field = strchr(buffer, ' ')))
		 	*field++ = '\0';

		strip_newline(field);
		
		if(!strcmp(buffer, "RSERVER"))
			strcpy(bot.uplinkHost, field);
		if(!strcmp(buffer, "RPORT"))
			bot.uplinkPort = atoi(field);
		if(!strcmp(buffer, "RPASS"))
			strcpy(bot.uplinkPassword, field);
		if(!strcmp(buffer, "NICK"))
			strcpy(bot.nick, field);
		if(!strcmp(buffer, "IDENT"))
			strcpy(bot.ident, field);
		if(!strcmp(buffer, "HOST"))
			strcpy(bot.host, field);
		if(!strcmp(buffer, "COMMENT"))
			strcpy(bot.realName, field);
		if(!strcmp(buffer, "MODES"))
			strcpy(bot.modes, field);
		if(!strcmp(buffer, "SERVER"))
			strcpy(bot.server->name, field);
		if(!strcmp(buffer, "SCOMMENT"))
			strcpy(bot.serverDescription, field);
		if(!strcmp(buffer, "DEBUGCHAN"))
			strcpy(bot.debugChan, field);
		if(!strcmp(buffer, "PROTOCHAN"))
			strcpy(bot.protoChan, field);
		if(!strcmp(buffer, "NUM")) {
			bot.serverNumericInt = atoi(field);
			inttobase64(bot.serverNumeric, bot.serverNumericInt, 2);
			strcpy(bot.server->numeric, bot.serverNumeric);
		}
		if(!strcmp(buffer, "NICKNUM")) {
			bot.numericInt = atoi(field);
		}
	}
	
	char tmpNum[4];
	inttobase64(tmpNum, bot.numericInt, 3);
	sprintf(bot.numeric, "%s%s", bot.serverNumeric, tmpNum);
	
	fclose(fp);
}
