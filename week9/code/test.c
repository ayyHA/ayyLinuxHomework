#include "./ch9.h"
int main(int argc,char* argv[]){
	extern char** environ;
	char **env=environ;
	printf("strlen env=%d environ=%d\n",strlen(env),strlen(environ));
	int i=0;
	//printf("I am test!\n");
	for(int i=1;i<argc;i++){
		printf("%s ",argv[i]);
	}
	while(*env){
		printf("%s\n",*env);
		env++;
	}
	exit(EXIT_SUCCESS);
	//return 0;
}
