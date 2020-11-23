#include "./ch10.h"
int main(){
	pid_t pid;
	pid=fork();
	if(pid<0){
		perror("failed fork!\n");
		exit(-1);
	}
	else if(pid==0){
		printf("child %d is running!\n",getpid());
		while(1);
	}
	else{
	//	getchar();
		printf("parent %d will exit now!\n",getpid());
		exit(0);// 父进程消失，子进程变为孤儿进程，被1号进程收养
	}
}
