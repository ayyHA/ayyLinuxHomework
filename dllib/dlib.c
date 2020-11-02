#include "../week7/code/ch7.h"
void dynamic_lib_call(void){
	printf("Dynamic lib is called!\n");
}

void dsum(int max){
	int i,sum=0;
	for(i=1;i<=max;i++){
		sum+=i;
	}
	printf("The sum = %d\n",sum);
}
