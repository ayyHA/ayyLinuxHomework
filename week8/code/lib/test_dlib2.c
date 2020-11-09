#include "../ch8.h"
extern void callMeHelloKitty(void);
extern int giveMeSomeArguments(int,int);
int main(int argc,char* argv[]){
	callMeHelloKitty();
	if(argc<3){
		perror("INPUT ARGUMENTS FAILED");
		exit(0);
	}
	int a=giveMeSomeArguments(atoi(argv[1]),atoi(argv[2]));
	printf("%s+%s=%d\n",argv[1],argv[2],a);
	return 0;
}
