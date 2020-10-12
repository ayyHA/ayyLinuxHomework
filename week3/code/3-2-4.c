#include "ch2.h"
int main(){
	/*
	FILE* fp;
	fp = fopen("./text1.txt","w");
	printf("file fp = %d\n",fp->_fileno);
	int ch;
	ch=getchar();
	fputc(ch,fp);
	fclose(fp);
	*/
	FILE* fp;
	char buf[80];
	int ret,test;
	memset(buf,0,sizeof(buf));
	if((fp = fopen("./text2.txt","w"))==NULL)
		perror("open failed!\n");
	fgets(buf,sizeof(buf),stdin);
	printf("Content is %s\n",buf);
	
	test = fwrite(buf,sizeof(buf),1,fp);
	printf("Test Success\n");

	printf("The return value is: %d\n",test);
	fclose(fp);
	return 0;
}
