#include "../ch9.h"
/*
 * 问：-会输出几次？
 * */
int main(){
	int i;
	for(i=0;i<2;i++){
		fork();
		printf("-");
	}
	return 0;
	// 会输出8次，因并非打印，留于缓冲区
}
