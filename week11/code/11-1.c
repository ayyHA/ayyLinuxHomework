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
		//int s,r
		else{
			int s1,s2,r1,r2;
			r1=wait(&s1);
			r2=wait(&s2);
			printf("Parent pid = %d , pid1=%d,pid2=%d\n",getpid(),pid1,pid2);
			if(r1==pid1){
				printf("the first one is pid1 = %d\n",pid1);
				printf("the second one is pid2 =%d\n",pid2);
			}
			else{
				printf("the first one is pid2=%d\n",pid2);
				printf("the second one is pid1= %d\n",pid1);
			}
			return 0;
		}
		/*r=wait(&s);
		printf("Parent : exit code = %d\n",WEXITSTATUS(s));
		return 0;*/
	}
}
