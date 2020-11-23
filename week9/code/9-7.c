#include "./ch9.h"
int main(){
	int pid;
	int status;
	pid=fork();
	if(pid<0){
		perror("Fork failed!\n");
		exit(-1);
	}
	else if(pid==0){
		printf("child : pid =%d, ppid =%d\n",getpid(),getppid());
		exit(23);
	}
	else{
		int y;
		y=wait(&status);
		if(WIFEXITED(status))
			printf("child %d is normal back. The exit code = %d\n",y,WEXITSTATUS(status));
		return 0;
	}
}

