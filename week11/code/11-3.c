#include "./ch11.h"
//父进程派生两个子进程1、2，子进程退出码为0
int main(){
	pid_t pid1;
	pid1=fork();
	if(pid1<0){
		perror("fork pid error!\n");
		exit(-1);
	}
	else if(pid1==0){
		printf("Child1 : pid = %d, ppid = %d\n",getpid(),getppid());
		exit(0);
	}
	else{
		pid_t pid2;
		pid2=fork();
		if(pid2<0){
			perror("fork pid2 error!\n");
			exit(-1);
		}
		else if(pid2==0){
			printf("Child2 : pid = %d, ppid = %d\n",getpid(),getppid());
			exit(0);
		}
		else{
			pid_t pid3;
			pid3=fork();
			if(pid3<0){
				printf("fork pid3 error!\n");
				exit(-1);
			}
			else if(pid3==0){	
				printf("Child3 : pid = %d, ppid = %d\n",getpid(),getppid());
				sleep(5);
				//exit(0);
				abort();
			}
			else{
				int s1,s2,s3,r1,r2;
				int flag=1;
				r1=wait(&s1);
				r2=wait(&s2);
				//int i=0;
				while(!waitpid(pid3,&s3,WNOHANG)){
					//printf("i=%d\n",++i);
					if(flag==1){
						printf("%d is in while and in sleep!\n",pid3);
						flag=0;
					}
					/*if(WIFSTOPPED(s3)){
						printf("%d is STOP! signal number %d\n",pid3,WSTOPSIG(s3));
					}*/
				}
				printf("%d is UNNORMAL EXIT! signal number %d\n",pid3,WTERMSIG(s3));
				return 0;
			}
			/*int s1,s2,r1,r2;
			r1=wait(&s1);
			r2=wait(&s2);
			printf("Parent pid = %d , pid1=%d,pid2=%d\n",getpid(),pid1,pid2);
			/*if(r1==pid1){
				printf("the first one is pid1 = %d\n",pid1);
				printf("the second one is pid2 =%d\n",pid2);
			}
			else{
				printf("the first one is pid2=%d\n",pid2);
				printf("the second one is pid1= %d\n",pid1);
			}*/
			/*
			if(WIFSIGNALED(s1)){
				printf("pid1 = %d, signal=%d\n",r1,WTERMSIG(s1));	
			}
			else{
                                printf("pid1 = %d, Normal exit!\n",pid1);
                        }

			
			

			if(WIFSIGNALED(s2)){
				printf("pid2 = %d, signal=%d\n",r2,WTERMSIG(s2));
			}
			else{
				printf("pid2 = %d, Normal exit!\n",pid2);
			}
			return 0;*/
		}
	
	}
}
