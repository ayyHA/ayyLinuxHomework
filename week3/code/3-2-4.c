#include "ch2.h"
int main(){
	FILE* fp;
	char buf[80];
	int ret,test;
	memset(buf,0,sizeof(buf));
	if((fp = fopen("./text2.txt","w"))==NULL)
		perror("open failed!\n");
	
	fgets(buf,sizeof(buf),stdin);
	printf("Content is %s\n",buf);
	

	//此方法为只写1次，1次写入80个字节
	test = fwrite(buf,sizeof(buf),1,fp);
	printf("Test Success\n");

	printf("The return value is: %d\n",test);
	fclose(fp);
	return 0;
}
