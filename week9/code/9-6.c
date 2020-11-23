#include "./ch9.h"
char* env_init[]={"USER=stu","PATH=/tmp",NULL};
int main(){
	if(execle("./test","./test","Hello","World\n",NULL,env_init)==-1){
		perror("execle!\n");
		exit(EXIT_FAILURE);
	}
	puts("Never get here !\n");
	exit(EXIT_SUCCESS);
}
