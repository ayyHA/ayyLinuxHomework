#include "ch7.h"
int main(int argc,char* argv[],char* env[]){

	extern char** environ;		     //引用外部的环境指针，环境指针找寻环境表
	int i;
	for(i=0;environ[i];i++){
		printf("environ[%d] = %s\n",i,environ[i]);
	}
	for(i=0;env[i]!=NULL;i++){
		printf("env[%d] = %s\n",i,env[i]);	//用main函数的env
	}
	//此二者等效
	printf("PATH = %s\n",getenv("PATH"));//获得单个环境变量
	return 0;
}
