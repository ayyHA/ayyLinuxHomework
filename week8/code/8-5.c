#include "./ch8.h"
static g=10;
int k=1;
int main(){
	static a=10;
	int i=1,j=2;
	int* pt = (int*)malloc(sizeof(int));
	printf("stack:i=%x,j=%x\n",&i,&j);
	printf("heap:pt=%x\n",pt);
	printf("data:g=%x,k=%x,a=%x\n",&g,&k,&a);
}
