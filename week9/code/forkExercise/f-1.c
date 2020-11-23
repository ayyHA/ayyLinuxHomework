#include "../ch9.h"
/*
 * 问：输出几次printf()的内容
 * */
int main(){
	fork()||fork();
	printf("ayy\n"); 
	/*
	 *1、父生子，fork()>0,后面的fork()不执行，执行自己的printf()
	 *2、子生子，fork()=0||fork()>0，执行自己printf()
	 *3、末子直接输出 
	 * */
	return 0;
}
