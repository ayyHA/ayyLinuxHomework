#include "./ch12.h"
/*
 * 目前存在如下问题：
 * 1、某一进程结束后，另一进程敲击任意键并ENTER后也会结束  原因：关闭后仍发送信息，得信号SIGPIPE
 * 2、最后的88没有被记录到
 * 3、没有模块化
 * */
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
		close(fd1[1]);
		close(fd2[0]);
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
				printf("pid2:");
				gets(buf3);
				f3=write(fd3[1],buf3,sizeof(buf3));
				if(f3<=0)
					printf("pid2 output failed!\n");

				if(!strcmp("88",buf3))
					break;
			}
			close(fd3[1]);
			close(fd4[0]);
			printf("pid2 finished!\n");
		}
		else{
			// 注：子进程fd为奇数表示输出内容，偶数为输入内容；fd1,fd2是pid1专用,fd3,fd4是pid2专用
			close(fd1[1]);
			close(fd3[1]);
			close(fd2[0]);
			close(fd4[0]);

			int d1,d2,d3,d4;
			int toFile;
			int flag1=0,flag2=0;// 表示pid1、pid2进程仍在运行
			int status;
			
			time_t t;
			//time(&t);
			struct tm* tm_t;
			//tm_t=localtime(&t);
			char bufTime[100];
			memset(bufTime,0,sizeof(bufTime));
			
			char bufSelf[20];
			memset(bufSelf,0,sizeof(bufSelf));

			int fd=open("./ChatContent.txt",O_CREAT|O_TRUNC|O_WRONLY,0644);
			do{
				if(!(flag1=waitpid(pid1,NULL,WNOHANG))){
					// 转发pid1给pid2的内容
					while((d1=read(fd1[0],buf1,sizeof(buf1)))==-1);//当pid1无输入，则一直等待；有输入后，则跳出循环
					//printf("%s from pid1\n sizeof(buf1)=%d\n strlen(buf1)=%d\n",buf1,sizeof(buf1),strlen(buf1));
					strcpy(buf4,buf1);

					flag2 = waitpid(pid2, NULL, WNOHANG); // 更新flag2
					if(!flag2){
						d4=write(fd4[1],buf4,sizeof(buf4));		// 当pid2存在才转发
						if(d4<=0)
							printf("send to pid2 failed!\n");
					}

					memset(bufTime,0,sizeof(bufTime));
					memset(bufSelf,0,sizeof(bufSelf));
					time(&t);
					tm_t=localtime(&t);
					sprintf(bufTime,"  %4d-%02d-%02d %02d:%02d:%02d  |",1900+tm_t->tm_year,tm_t->tm_mon+1,tm_t->tm_mday,tm_t->tm_hour,tm_t->tm_min,tm_t->tm_sec);        			        // 存储聊天时间
										
					sprintf(bufSelf,"  %d  |",pid1);	// 存储pid
					//sprintf(buf4,"  %s  |\n",buf4);	// 存储内容(内容丢失)
					strcat(buf1,"  \n");
					strcat(bufTime,bufSelf);
					strcat(bufTime,buf1);
					toFile=write(fd,bufTime,sizeof(bufTime));
					if(toFile<=0)
						printf("write to file failed!\n");
				}
				else if (!(flag2=waitpid(pid2,NULL,WNOHANG))) // pid1挂了，pid2活着。父进程与pid2通信
				{
					if(strcmp("88",buf3)){		// 若pid2挂了，则不write
					//if (strcmp("88",buf2)) {
						if(!(flag2=waitpid(pid2,NULL,WNOHANG))){//bbbbbbbbbbbb
							sprintf(buf4, "I am your parent, I am listen!");
							write(fd4[1], buf4, sizeof(buf4));
					
						}
					}
				}
				
				if(!(flag2=waitpid(pid2,NULL,WNOHANG))){
					// 转发pid2给pid1的内容
					while((d3=read(fd3[0],buf3,sizeof(buf3)))==-1);
					strcpy(buf2,buf3);

					flag1 = waitpid(pid1, NULL, WNOHANG); // 更新flag1
					if(!flag1){					// 当pid1依旧存在时才转发否则不转发
						d2=write(fd2[1],buf2,sizeof(buf2));
						if(d2<=0)
							printf("send to pid2 failed!\n");
					}
					
					memset(bufTime,0,sizeof(bufTime));
					memset(bufSelf,0,sizeof(bufSelf));
					time(&t);
					tm_t=localtime(&t);
					sprintf(bufTime,"  %4d-%02d-%02d %02d:%02d:%02d  |",1900+tm_t->tm_year,tm_t->tm_mon+1,tm_t->tm_mday,tm_t->tm_hour,tm_t->tm_min,tm_t->tm_sec);       		 	        // 存储聊天时间
                                               
                                        sprintf(bufSelf,"  %d  |",pid2);	// 存储pid
                                        //sprintf(buf3,"  %s  |\n",buf3);	// 存储内容
                                        strcat(buf3,"  \n");
					strcat(bufTime,bufSelf);
                                        strcat(bufTime,buf3);
                                        toFile=write(fd,bufTime,sizeof(bufTime));
                                        if(toFile<=0)
                                                printf("write to file failed!\n");

				}
				else if (!(flag1=waitpid(pid1,NULL,WNOHANG))) // pid2挂了，pid1活着。父进程跟pid1聊天
				{
					if(strcmp("88",buf1)){		      // 获取pid1的输入信息，若是88退出了，则buf1不会被修改
					//if (strcmp("88", buf4)) {
						if(!(flag1=waitpid(pid1,NULL,WNOHANG))){
							sprintf(buf2, "I am your parent, I am listen!");
							write(fd2[1], buf2, sizeof(buf2)); 
						}
					}
				}

				status=!(flag1&&flag2);
			}while(status);

			close(fd);
			printf("Parent : %d finished!\n",getpid());
		}
	}
}
