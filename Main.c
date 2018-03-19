#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHARQ 30
#define DEFAULTPORT 80

int xorString(char * string){
	int result = 0, cont=0;
	while(string[cont++] != '\n'){
		result = result ^ string[cont];
	}
	return result;
}
void validateRequestLine(char * method, char * uri, char * version){
	if(strcmp(method,"GET") != 0 && strcmp(method,"get") != 0 && strcmp(method,"post") != 0 && strcmp(method,"POST") != 0)	
		exit(0);
}

//HTTP Parser
int main(int argc, char const *argv[])
{
	char * method = malloc(MAXCHARQ), * uri = malloc(MAXCHARQ), * version = malloc(MAXCHARQ), * line = malloc(MAXCHARQ), *prefix = malloc(MAXCHARQ), * sufix = malloc(MAXCHARQ);
	char * host = malloc(MAXCHARQ), * messagebody = malloc(MAXCHARQ), * sport = malloc(MAXCHARQ);
	int port;
	size_t max;
	host = "";

	if(method == NULL || uri == NULL || version == NULL || line == NULL || prefix == NULL || sufix == NULL || host == NULL){
		printf("No memory!\n");
		return 1;
	}
	printf("[Enter Request]\n");
	
	getline(&line, &max, stdin);
    sscanf(line, "%s %s %s", method, uri, version);	//Request Line
	validateRequestLine(method, uri, version);

	getline(&line, &max, stdin);    				//Headers
	sscanf(line, "%s %s", prefix, sufix);	
	while(line[0] != 0xA){								
		if(strcmp(prefix, "Host:")==0){
			host = strtok(sufix, ":");
			if((sport = strtok(NULL, ":")) != NULL)
				port = atoi(sport);
			else
				port = DEFAULTPORT;
		}

		getline(&line, &max, stdin);
	}
	if(strcmp(host, "") == 0){
		printf("No host.\n");
		exit(0);
	}

	getline(&messagebody, &max, stdin);				//Message body
	
	printf("%s %s %d R %ld %x \r\n", method, host, port, strlen(messagebody), xorString(messagebody));
	return 0;
}
