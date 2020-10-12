#include "ch2.h"
int main(){
	FILE* fp;
	char buf[80];
	memset(buf,0,sizeof(buf));
	fp = fopen("./test1.txt","a+");
	fputs("\tappend new information!",fp);
	fp = freopen("./test1.txt","r",fp);	//先关掉fp再以只读方式打开
	fgets(buf,sizeof(buf),fp);
	printf("Content of file : %s\n",buf);
	fclose(fp);
	return 0;
}
