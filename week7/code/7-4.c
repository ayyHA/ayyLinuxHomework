#include "ch7.h"
//用注册函数使用回调
static void callback1(void){
	printf("------CallBack1----------\n");
}

static void callback2(void){
	printf("------CallBack2----------\n");
}

static void callback3(void){
	printf("------CallBack3----------\n");
}

int main(void){
	atexit(callback1);//用于注册main函数的回调函数,以栈的形式
	atexit(callback2);
	atexit(callback3);
	printf("----Main exit----");
	exit(0);//会清空缓存区再退出
	//_exit(0);//强制清空,不会输出
}
