#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHARQ 30

//HTTP Parser
int main(int argc, char const *argv[])
{
	char * method = malloc(MAXCHARQ), * uri = malloc(MAXCHARQ), * version = malloc(MAXCHARQ), * line = malloc(MAXCHARQ), *prefix = malloc(MAXCHARQ), * sufix = malloc(MAXCHARQ);
	char * host = malloc(MAXCHARQ);
	int port;
	size_t max;

	if(method == NULL || uri == NULL || version == NULL || line == NULL || prefix == NULL || sufix == NULL || host == NULL){
		printf("No memory!\n");
		return 1;
	}
	printf("[Enter Request]\n");
	
	getline(&line, &max, stdin);
    sscanf(line, "%s %s %s", method, uri, version);	//Request Line
	//Request Line validations

	getline(&line, &max, stdin);    
	sscanf(line, "%s %s", prefix, sufix);	
	while(line[0] != 0xA){							//Headers	
		if(strcmp(prefix, "Host:")==0){
			host = strtok(sufix, ":");
			port = atoi(strtok(NULL, ":"));
			//sscanf(sufix, "%s:%d", host, &port);
			printf("HOST:%s\nPORT:%d", host, port);
		}

		getline(&line, &max, stdin);
	}

	printf("%s %s %d", method, host, port );
	return 0;
}
