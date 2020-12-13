#include "./ch12.h"
#include "my.h"
int main(){
	int a[10]={12,5,-0,44,1,-987,43,80439,765,-99999},i;
	printf("add = %d \n",add(a[5],a[9]));
	for(i=0;i<10;i++)
		printf("a[%d]: %d \n",i,a[i]);
	mysort();
}
