#include <bot.h>

void strip_newline(char *string) {
   char *ptr = NULL;
   if((ptr = strchr(string, '\r')))
 		*ptr = '\0';
   if((ptr = strchr(string, '\n')))
 		*ptr = '\0';
}

int parse_line(char *str, char **parv, int stopAtColon) {
	int i = 0;
	
	parv[0] = strtok(str, " ");
	for(i = 1; i < 100; i++) {
		if((parv[i] = strtok(NULL, " "))) {
			if(parv[i][0] == ':') {
				*parv[i]++;
				
				if(stopAtColon) {
					char *token = NULL;
					while((token = strtok(NULL, " "))) {
						sprintf(parv[i], "%s %s", parv[i], token);
					}
					
					i++;
					break;
				}
			}
		}
		else
			break;
	}
	
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

char *toLower(char *str) {
	int i = 0;
	char buf[strlen(str) + 1];
	char *p = str;
	
	while(*p)
		buf[i++] = tolower(*p++);

	buf[i] = '\0';
	
	return buf;
}

char *toUpper(char *str) {
	int i = 0;
	char buf[strlen(str) + 1];
	char *p = str;
	
	while(*p)
		buf[i++] = toupper(*p++);
	
	buf[i] = '\0';
	
	return buf;
}


char* irc_strncpy(char* s1, const char* s2, size_t n)
{
  char* endp = s1 + n;
  char* s = s1;

  assert(0 != s1);
  assert(0 != s2);

  while (s < endp && (*s++ = *s2++))
    ;
  if (s == endp)
    *s = '\0';
  return s1;
}
