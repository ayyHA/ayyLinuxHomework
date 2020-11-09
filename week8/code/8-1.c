#include "./ch8.h"

void fun(int cnt){
	int* x = (int*)malloc(sizeof(int));
	int* y = (int*)malloc(sizeof(int));
	if(!x){
		printf("END~");
		printf("cnt=%d\n",cnt);
		return;
	}
	if(!y){
		printf("END~");
		printf("cnt=%d\n",cnt);
		return;
	}
	printf("x=%x,y=%x,cnt=%x,cnt=%d\n",x,y,&cnt,++cnt);
	fun(cnt);
}
int main(){
	fun(0);
	return 0;
}
