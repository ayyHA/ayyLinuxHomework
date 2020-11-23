#include "./ch10.h"
int main(){
// exit code：108 99
	pid_t pid;
	int status;
       	pid=fork();
	if(pid<0){
		perror("fork failed!\n");
		exit(-1);
	}	
	else if(pid==0){
		printf("Child 1 : pid = %d, ppid = %d\n",getpid(),getppid());
		exit(108);
	}
	else{
		int son;
		son=waitpid(pid,&status,0);
		printf("The Child 1 : %d exit, its exit code %d\n",son,WEXITSTATUS(status));
		pid=fork();
		if(pid<0){
			perror("fork failed!\n");
			exit(-1);
		}
		else if(pid==0){
			printf("Child 2 : pid = %d, ppid = %d\n",getpid(),getppid());
			exit(99);
		}
		else{
			int i=0;
			while(!(son=waitpid(pid,&status,WNOHANG))){
				printf("%d:the son %d still running, wait this guy!\n",++i,pid);
			}
			printf("The Child 2 : %d exit, its exit code %d\n",son,WEXITSTATUS(status));
			exit(0);
		}
	}
}
