/*
 * 注：此程序为gets溢出的例子，因为ubuntu存在栈溢出保护机制，无法体现；但可在VC6.0中体现
 * */
#include "ch4.h"
int main(){
	char password[8]="secret",input[8];
	while(1){
		printf("Enter your password:");
		gets(input);
		if(strcmp(input,password)==0){
			printf("Welcome!\n");
			break;
		}
		else{
			printf("Sorry,your password is wrong.\n");
		}
	}
	return 0;
}
