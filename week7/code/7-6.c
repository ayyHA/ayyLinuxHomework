#include "ch7.h"

static void callback1(void){
	printf("----------I am callback1~----------\n");
}

static void callback2(void){
	printf("---------I am callback2~-----------\n");
}

static void __attribute__((destructor)) after_main(){
	printf("--------------I am destructor -------------\n");
}

int main(){
	atexit(callback1);
	atexit(callback2);
	while(1){
		sleep(1);
	}
	printf("----- Main test ------\n");
	exit(0);//只有正常退出(return 0; OR exit(0);)才会调用callback
}
