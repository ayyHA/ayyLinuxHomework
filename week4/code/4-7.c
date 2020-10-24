#include "ch3.h"
int main(){
	int fda;
	fda=open("ayyHa.txt",O_WRONLY,0644);
	while(1){
		write(fda,"a",1);
		sleep(3);
		lseek(fda,10,SEEK_SET);
	}
	return 0;

}
