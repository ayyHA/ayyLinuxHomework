#include "./ch10.h"
int main(){
	int r,i;
	r=fork();
	if(r<0){
		perror("fork failed!\n");
		exit(-1);
	}
	else if(r==0){
		printf("Child : pid = %d, ppid = %d\n",getpid(),getppid());
		i = execl("./test","I","am","the","child",NULL);
		if(i==-1){
			perror("execl failed!\n");
			exit(-1);
		}
		printf("Child end!\n");
		exit(78);// 此退出码不会被传出，因为此代码被替换掉
	}
	else{
		int child,state;
		child=wait(&state);
		printf("Father : pid =%d, ppid = %d\n",getpid(),getppid());
		printf("My son pid = %d , status = %d\n",child,WEXITSTATUS(state));
		return 0;
	}
}
