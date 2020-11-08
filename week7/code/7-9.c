#include "ch7.h"
static void set_env_string(void){
	char testEnvKey[]="test_env";
	char testEnvValue[]="test";
	if(setenv(testEnvKey,testEnvValue,0)!=0){
		printf("Setenv is failed!\n");
	}
	printf("1. The test_env = %s\n",getenv("test_env"));
}
	
static void show_env_string(){
	printf("2. The test_env = %s\n",getenv("test_env"));
}

int main(){
	set_env_string();
	show_env_string();//成功二次打印test_env对应的值
	return 0;
}
