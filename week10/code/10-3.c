#include "./ch10.h"
int main(){
	int r1,r2,r3,r11,state;
	r1 = fork();
	//r2 = fork();
	if(r1<0||r2<0){
		perror("fork failed!\n");
		exit(1);
	}
	else if(r1==0){
		r11=fork();
		if(r11<0){
			printf("fork failed!\n");
			exit(-1);
		}
		else if(r11==0){
			printf("child11 : pid = %d, ppid = %d\n",getpid(),getppid());
			exit(78);
		}
		else{
			wait(&state);
			printf("child1 : pid = %d, ppid = %d\n",getpid(),getppid());
			exit(0);
		}
	}
	else{
		r2 = fork();
		if(r2<0){
			perror("fork failed!\n");
			exit(-1);
		}
		else if(r2==0){
			printf("child 2 : pid = %d , ppid = %d\n",getpid(),getppid());
			exit(0);
		}
		else{
			r3=fork();
			if(r3<0){
				printf("fork failed!\n");
				exit(-1);
			}
			else if(r3==0){
				printf("child 3 : pid =%d , ppid = %d\n",getpid(),getppid());
			}
			else{
			wait(NULL);// 等待第一个子进程
			wait(NULL);// 等待第二个子进程
			wait(NULL);// 等待第三个子进程
			printf("parent : pid = %d, r1 = %d, r2 = %d, r3 = %d\n",getpid(),r1,r2,r3);
			return 0;
			}
		}
	}
}
