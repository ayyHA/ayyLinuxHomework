#include "./ch12.h"
int main(){
	int fd[2],i;
	int fd2[2],j;
	pid_t pid1,pid2;
	char buf[100],buf2[100];
	memset(buf,0,sizeof(buf));
	if(pipe(fd)<0){
		perror("pipe failed!\n");
		exit(-1);
	}
	memset(buf2,0,sizeof(buf2));
	if(pipe(fd2)<0){
		perror("pipe2 failed!\n");
		exit(-1);
	}

	pid1=fork();
	if(pid1<0){
		perror("pid1 fork failed!\n");
		exit(-1);
	}
	else if(pid1==0){
		close(fd[1]);
		i=read(fd[0],buf,sizeof(buf));
		if(i<=0){
			printf("pid1 read failed!\n");
		}
		else{
			fprintf(stdout,"pid1 %d receive:++%s++ from pid2\n",getpid(),buf);
		}

		//--
		close(fd2[0]);
		sprintf(buf2,"pid1 %d say HAHAHA to you!",getpid());
		j=write(fd2[1],buf2,sizeof(buf2));
		if(j<=0)
			printf("pid1 write failed!\n");
		else
			printf("pid1 wrtie success!\n");

		close(fd[0]);
		close(fd2[1]);
	}
	else{
		pid2=fork();
		if(pid2<0){
			perror("pid2 fork failed!\n");
			exit(-1);
		}
		else if(pid2==0){
			close(fd[0]);
			sprintf(buf,"pid2 %d say hello to you!",getpid());
			i=write(fd[1],buf,sizeof(buf));
			if(i<=0){
				printf("pid2 write failed");
			}
			else{
				printf("pid2 write success!\n");
			}
			
			//--
			close(fd2[1]);
			j=read(fd2[0],buf2,sizeof(buf2));
			if(j<=0)
				printf("pid2 read failed!\n");
			else
				fprintf(stdout,"pid2 %d receive ++%s++ from pid1\n",getpid(),buf2);
			
			close(fd[1]);
			close(fd2[0]);
		}
		else{
			wait(NULL);
			wait(NULL);
			printf("ch1:%d ch2:%d \nparent : %d finished!\n",pid1,pid2,getpid());
			return 0;
		}
	}

}
