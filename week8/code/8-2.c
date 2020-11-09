#include "./ch8.h"
//编程测试malloc最多分配多少字节
int main(){
	int cnt=0;
	while(1){
		char* a = (char*)malloc(sizeof(char));
		if(!a){
			printf("End cnt = %d\n",cnt);
			break;	
		}
		printf("Now cnt = %d\n",++cnt);
	}

	return 0;
}
