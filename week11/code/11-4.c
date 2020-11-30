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
		//while(1);
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
			while(1)
				printf("RUNNING!\n");
			exit(0);
		}
		
		else{
			int s1,s2,r1,r2;
			//r1=waitpid(pid1,&s1,0);
			r2=waitpid(pid2,&s2,WNOHANG);
			r1=waitpid(pid1,&s1,0);
			/*if(pid1==r1){
				printf("I AM FEI ZU SAI！、N");
			}*/
			printf("Parent pid = %d , pid1=%d,pid2=%d\n",getpid(),pid1,pid2);
			
			if(WIFEXITED(s1)){
				printf("pid1 = %d, exit code = %d\n",r1,WEXITSTATUS(s1));
			}
			else{
				if(WIFSIGNALED(s1)){
					printf("pid1 = %d, signal code = %d\n",r1,WTERMSIG(s1));
				}
			}
			
			/*while(!(r2=waitpid(pid2,&s2,WNOHANG))){
				printf("I AM IN WHILE RUNNING!\n");
				sleep(1);
			}*/
			if(WIFEXITED(s2)){
				printf("pid2 = %d, exit code = %d\n",r2,WEXITSTATUS(s2));
			}
			else{
				if(WIFSIGNALED(s2))
				printf("pid2 = %d, signal code = %d\n",r2,WTERMSIG(s2));
			}
			return 0;
		}
		/*r=wait(&s);
		printf("Parent : exit code = %d\n",WEXITSTATUS(s));
		return 0;*/
	}
}
