#include "../week7/code/ch7.h"
int main(){
//	char* s;如这样写，不初始化，则会报段错误
	char s[120];
	memset(s,0,sizeof(s));
	strcpy(s,"hello world!\n");
	printf("s = %s \n",s);
	return 0;
}
