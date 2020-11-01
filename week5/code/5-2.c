#include "ch4.h"
int main(){
	printf("%d\n",BUFSIZ);
	
	char buf1[2048];
	char buf2[32];

	FILE* fp1 = fopen("test1.dat","w+");
	FILE* fp2 = fopen("test2.dat","w+"); 
	//以下为通过setbuf打开关闭流stream的缓冲区，可自定义缓冲区大小；
	setbuf(fp1,buf1);	
	setvbuf(fp2,buf2,_IOLBF,sizeof(buf2));
	//以下为通过setvbuf自定义stream的缓冲区类型及缓冲区大小；
	fwrite("Hello World!",12,1,fp1);
	while(1);
	return 0;
}
