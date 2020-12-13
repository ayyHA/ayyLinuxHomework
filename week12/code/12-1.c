#include "./ch12.h"
int main(){
	int fd[2],i;
	pid_t k;
	char buf[100];
	memset(buf,0,sizeof(buf));
	if(pipe(fd)<0){
		perror("pipe failed!\n");
		exit(-1);
	}
	// 父子进程共享
	k=fork();
	if(k<0){
		perror("fork failed!\n");
		exit(-1);
	}
	else if(k==0){
		close(fd[1]);// 关闭写口
		i=read(fd[0],buf,sizeof(buf));
		if(i<=0){
			printf("child receive failed!\n");
		}
		else{
			fprintf(stdout,"child %d receive %s from parent! total = %d\n",getpid(),buf,strlen(buf));
		}
		exit(0);
	}
	else{
		close(fd[0]);
		sprintf(buf,"parent %d send to childl %d\n",getpid(),k);
		i=write(fd[1],buf,sizeof(buf));
		if(i>0){
			printf("parent %d send success!\n",getpid());
		}
		wait(NULL);
		return 0;
	}
}
