#include "ch2.h"
int main(int argc,char* argv[]){
/*	
 //此代码用于测试通过位置参数输入值以替代fread
  	FILE* fp;
	int test;
	
	if((fp = fopen(argv[1],"w"))==NULL)
		perror("open failed!\n");

	test=fwrite(argv[2],strlen(argv[2]),1,fp);
	printf("Test Success\n");
	printf("[%ld]: %s\n",strlen(argv[2]),argv[2]);
	printf("The return value is: %d\n",test);
	fclose(fp);
 //	printf("strlen: %ld\n",strlen("\0a344564564848safsdgss"));
*/

/*
	FILE* fp;
	int test,i;
	char buf[200];
	memset(buf,0,sizeof(buf));
	if((fp=fopen(argv[1],"w"))==NULL)
		perror("open failed!\n");
	for(i=2;i<argc;i++){
		strcat(buf,argv[i]);
	}
	fwrite(buf,sizeof(buf),1,fp);
	printf("Test Success~\n");
	return 0;
*/

	FILE* fp;
	if((fp=fopen("text4.txt","w"))==NULL)
		perror("open failed!\n");


	for(int i=1;i<argc;i++){
		fprintf(fp,"%s",argv[i]);
	} 
	return 0;
}
