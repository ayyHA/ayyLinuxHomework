#include "ch2.h"
int main(){
	FILE* fp;
	char buf[80];
	int ret,test;
	memset(buf,0,sizeof(buf));
	if((fp = fopen("./text1.txt","w"))==NULL)
		perror("open failed!\n");
	fgets(buf,sizeof(buf),stdin);
	printf("Content is %s\n",buf);
	
	//此种方式为一次写一字节，写80次
	test = fwrite(buf,1,sizeof(buf),fp);
	printf("Test Succes\n");
	
	printf("The return value is: %d\n",test);
	fclose(fp);
	return 0;
}
