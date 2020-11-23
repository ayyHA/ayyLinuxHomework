#include "./ch10.h"
int main(){
// exit code：108 99
	pid_t pid1,pid2;
	int status1,status2;
       	pid1=fork();
	if(pid1<0){
		perror("fork failed!\n");
		exit(-1);
	}	
	else if(pid1==0){
		printf("Child 1 : pid = %d, ppid = %d\n",getpid(),getppid());
		exit(108);
	}
	else{
		//int son;
		//son=waitpid(pid,&status,0);
		//printf("The Child 1 : %d exit, its exit code %d\n",son,WEXITSTATUS(status));
		pid2=fork();
		if(pid2<0){
			perror("fork failed!\n");
			exit(-1);
		}
		else if(pid2==0){
			printf("Child 2 : pid = %d, ppid = %d\n",getpid(),getppid());
			exit(99);
		}
		else{
			//int i=0;
			int r1,r2;
			r1=waitpid(pid1,&status1,WNOHANG);
			r2=waitpid(pid2,&status2,0);
			printf("The Child 1 : %d exit, its exit code %d\n",r1,WEXITSTATUS(status1));
			printf("The Child 2 : %d exit, its exit code %d\n",r2,WEXITSTATUS(status2));
			exit(0);
		}
	}
}
