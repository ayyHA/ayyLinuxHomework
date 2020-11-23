#include "./ch10.h"
int main(){
	pid_t pid;
	pid = fork();
	if(pid<0){
		perror("fork failed!\n");
		exit(-1);
	}
	else if(pid==0){
		exit(0);
	}
	else{
		sleep(300);
		wait(NULL);// 父进程暂时无法处理子进程的事情，子进程变为僵尸进程
	}
	return 0;
}
