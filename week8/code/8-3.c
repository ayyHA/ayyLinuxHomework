#include "./ch8.h"
int main(){
	int *pt=NULL;
	int max=1024*1024;
	for(int i=0;i<max;i++){
		pt =(int*)malloc(i*max);
		if(!pt){
			perror("malloc failed !\n ");
			exit(-1);
		}	
		printf("malloc %d MB \n",i);
	}
	return 0;
}
