#include "ch7.h"
int main(int argc,char* argv[]){
	for(int i=0;i<argc;i++){
		printf("argv[%d]:%s\n",i,argv[i]);
	}
	if(argc<3){
		perror("arguments error!\n");
		exit(0);
	}
	int a = atoi(argv[1]);		//char* -> int
	int b = atoi(argv[2]);
	printf("%d + %d=%d\n",a,b,a+b);	
	return 0;
}
