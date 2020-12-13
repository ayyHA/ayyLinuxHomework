#include "./ch12.h"
int main(){
	int fd1[2],fd2[2],fd3[2],fd4[2];
	pid_t pid1,pid2;
	char buf1[100],buf2[100],buf3[100],buf4[100];
	int f1,f2,f3,f4;
	if(!(pipe(fd1)||pipe(fd2)||pipe(fd3)||pipe(fd4))){
		memset(buf1,0,sizeof(buf1));
		memset(buf2,0,sizeof(buf2));
		memset(buf3,0,sizeof(buf3));
		memset(buf4,0,sizeof(buf4));
	}
	else{
		perror("pipe failed!\n");
		exit(-1);
	}

	pid1=fork();
	if(pid1<0){
		perror("pid1 fork failed!\n");
		exit(-1);
	}
	else if(pid1==0){
		// 关闭pid2与父进程的通话管道
		close(fd3[0]);
		close(fd3[1]);
		close(fd4[0]);
		close(fd4[1]);
		
		close(fd1[0]);
		close(fd2[1]);
		while(1){
			// 此段为pid1输出信息给pid2,使用fd1,buf1	(pid1->主->pid2)
			//sprintf(buf1,"我是PID1，我现在发消息给PID2!\n");
			printf("pid1:");
			gets(buf1);
			f1=write(fd1[1],buf1,sizeof(buf1));
			if(f1<=0)
				printf("pid1 output failed!\n");
			
			if(!strcmp("88",buf1))
				break;

			// 此段为pid1获得pid2输入信息,使用fd2,buf2	（pid1<-主<-pid2）
			//waitpid(pid2,NULL,0);// 会死锁🔓
			while((f2=read(fd2[0],buf2,sizeof(buf2)))==-1);
			printf("pid1: ++%s++ from pid2\n",buf2);
		}
		printf("pid1 finished!\n");
	}
	else{
		pid2=fork();
		if(pid2<0){
			perror("pid2 fork failed!\n");
			exit(-1);
		}
		else if(pid2==0){
			// 关闭pid1与父进程的通话管道
			close(fd1[0]);
			close(fd1[1]);
			close(fd2[0]);
			close(fd2[1]);
		
			close(fd4[1]);
			close(fd3[0]);	
			
			while(1){
				// 此段为pid2获得pid1输入信息,使用fd4,buf4	(pid2<-主<-pid1)
				//waitpid(pid1,NULL,0);// 不可互相如此使用，会导致死锁🔓
				while((f4=read(fd4[0],buf4,sizeof(buf4)))==-1);
				printf("pid2: ++%s++ from pid1\n",buf4);
	
				// 此段为pid2输出信息给pid1,使用fd3,buf3	(pid2->主->pid1)
				//sprintf(buf3,"pid2写给pid1的一些微不足道的话!\n");
				printf("pid2:");
				gets(buf3);
				f3=write(fd3[1],buf3,sizeof(buf3));
				if(f3<=0)
					printf("pid2 output failed!\n");

				if(!strcmp("88",buf3))
					break;
			}
			printf("pid2 finished!\n");
		}
		else{
			// 注：子进程fd为奇数表示输出内容，偶数为输入内容；fd1,fd2是pid1专用,fd3,fd4是pid2专用
			close(fd1[1]);
			close(fd3[1]);
			close(fd2[0]);
			close(fd4[0]);

			int d1,d2,d3,d4;
			int flag1=0,flag2=0;// 表示pid1、pid2进程仍在运行
			int status;
			//flag1=waitpid(pid1,NULL,WNOHANG);
			//flag2=waitpid(pid2,NULL,WNOHANG);
			//status=!(flag1&&flag2);
			do{
				if(!(flag1=waitpid(pid1,NULL,WNOHANG))){
					// 转发pid1给pid2的内容
					while((d1=read(fd1[0],buf1,sizeof(buf1)))==-1);//当pid1无输入，则一直等待；有输入后，则跳出循环
					//printf("%s from pid1\n sizeof(buf1)=%d\n strlen(buf1)=%d\n",buf1,sizeof(buf1),strlen(buf1));
					strcpy(buf4,buf1);
					d4=write(fd4[1],buf4,sizeof(buf4));
					if(d4<=0)
						printf("send to pid2 failed!\n");
				}
				
				if(!(flag2=waitpid(pid2,NULL,WNOHANG))){
					// 转发pid2给pid1的内容
					while((d3=read(fd3[0],buf3,sizeof(buf3)))==-1);
					strcpy(buf2,buf3);
					d2=write(fd2[1],buf2,sizeof(buf2));
					if(d2<=0)
						printf("send to pid1 failed!\n");
				}
				//flag1=waitpid(pid1,NULL,WNOHANG);
				//flag2=waitpid(pid2,NULL,WNOHANG);
				status=!(flag1&&flag2);
			}while(status);
			//waitpid(pid1,NULL,0);
			//waitpid(pid2,NULL,0);
		}
	}
}
