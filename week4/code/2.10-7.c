#include "ch3.h"
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
