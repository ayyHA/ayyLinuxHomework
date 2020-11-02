#include "ch7.h"
int main(void){
	printf("----data in buffer----");
	//exit(0);//会清空缓存区再退出
	_exit(0);//强制清空,不会输出缓冲区内容
}
