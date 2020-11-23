#include "./ch10.h"
int main(){
	int r;
	printf("10-5 : pid = %d, ppid = %d\n",getpid(),getppid());
	system("./test hello world 2020 11 23\n");
	//r = execl("./test","./test","hello","world",NULL);
	//if(r==-1){
	//	perror("execl failed!\n");
	//	exit(-1);
	//}

	printf("After Calling!\n");
	return 0;
}
