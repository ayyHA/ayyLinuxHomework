#include "ch3.h"
int main(){
	int d1,d2;
	char buf[5];
	memset(buf,0,5);
	d1=open("file.hole",O_RDONLY);
	d2=dup(d1);//两者共用同一个FILE*
	printf("d1=%d,d2=%d\n",d1,d2);
	lseek(d1,5,SEEK_SET);
	read(d2,buf,4);
	printf("buf:%s\n",buf);
	return 0;
}
