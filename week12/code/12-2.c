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

	int fd2[2],j;
	char buf2[100];
	memset(buf2,0,sizeof(buf));
	if(pipe(fd2)<0){
		perror("pipe2 failed!\n");
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
		else{// ++号框住的是输入的内容
			fprintf(stdout,"child %d receive ++%s++ from parent! total = %d\n",getpid(),buf,strlen(buf));
		}

		close(fd2[0]);	// 关闭输入口
		sprintf(buf2,"I am %d have already received you message!",getpid());
		j=write(fd2[1],buf2,sizeof(buf2));
		if(j>0){
			printf("child %d send success!\n",getpid());
		}
		exit(0);
	}
	else{
		close(fd[0]);
		sprintf(buf,"parent %d send to child %d",getpid(),k);
		i=write(fd[1],buf,sizeof(buf));
		if(i>0){
			printf("parent %d send success!\n",getpid());
		}

		close(fd2[1]);	// 关闭输出口
		j=read(fd2[0],buf2,sizeof(buf2));
		if(j<=0){
			printf("parent receive failed!\n");
		}
		else{
			fprintf(stdout,"parent %d receive:++%s++ from my child!\n",getpid(),buf2);
		}
		
		wait(NULL);
		return 0;
	}
}
