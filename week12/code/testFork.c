#include "./ch12.h"

int main(){
	/*
	pid_t pid;
	pid=fork();
	if(pid<0){
		printf("fork failed!\n");
		exit(-1);
	} 
	else if(pid==0){
		sleep(2);
	}
	else{
		int t;
		while(!(t=waitpid(pid,NULL,WNOHANG))){
			printf("t=%d\n",t);
		}
		t=waitpid(pid,NULL,WNOHANG);
		printf("The t=%d\n",t);
	}*/
	int a=-1;
	printf("%d\n",!a);
	return 0;
}
