#include <bot.h>

void strip_newline(char *string) {
   char *ptr = NULL;
   if(ptr = strchr(string, '\r')) *ptr = '\0';
   if(ptr = strchr(string, '\n')) *ptr = '\0';
}

int parse_line(char *str, char **parv) {
	int i = 0;
	
//	fprintf(stdout, "PARSING: %s\n", str);
	parv[0] = strtok(str, " ");
	for(i = 1; i < 100; i++) {
		if(parv[i] = strtok(NULL, " ")) {
			if(parv[i][0] == ':') *parv[i]++;
		}
		else
			break;
	}
//  fprintf(stdout, "   parc = %d\n\n", i);
	return i;
}

char *join_array(char **parv, int start, int end) {
	int i = 0;
	char str[MAXBUF];
	
	if(parv[start]) strcpy(str, parv[start]);
	for(i = start+1; parv[i] && i <= end; i++) {
		sprintf(str, "%s %s", str, parv[i]);
	}
	return str;
}

char *strlwr(char *str) {
	int i = 0;

	for(i = 0; i < strlen(str); i++)
		str[i] = tolower(str[i]);
	return str;
}

char *strupr(char *str) {
	int i = 0;

	for(i = 0; i < strlen(str); i++)
		str[i] = toupper(str[i]);
	return str;
}