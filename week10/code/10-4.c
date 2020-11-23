#include "./ch10.h"
int main(){
	int r;
	printf("10-4 : pid = %d, ppid = %d\n",getpid(),getppid());
	r = execl("./test","./test","hello","world",NULL);
	if(r==-1){
		perror("execl failed!\n");
		exit(-1);
	}

	printf("After Calling!\n");
	return 0;
}
