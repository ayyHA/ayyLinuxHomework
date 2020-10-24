/*
 设某个文件含n个记录，文件的第一个字（4字节）给出记录的总个数n，随后的n个字给出各个记录的长度（字节数），剩余部分则由各个记录组成。编写一个根据文件指针和记录编号（从1开始编号）读取第k个记录的函数。
 */
// 怎么让文件指针指向第k个记录的行起始位置，再通过getline()、puts()输出之
// 文件第一次getline需要读到第n+1个，并且把[1,n+1]的长度保留下来并加一，定位的时候读到第n+1个的文件位置为基址，之后添加偏移量即可
#include "ch3.h"

//全局变量定义
int recordNo=0;
int* recordSize=NULL;

//函数声明
void operateFile(FILE* fp);	//对文件的操作
int getNumber(char* buf);
int getOffset(int index);
/*
	第一个单独的getline(),读入目前文件位置，及记录的项的次数
	第二次循环记录项次的getline,是为了记录每一个记录项的长度，作日后偏移值用 ，且最后一次的作基址
	
	getline返回值为成功读入的字符的个数，含\n
*/

int main(){
	FILE* fp=fopen("./testFor2.10-10.txt","r");
	operateFile(fp);
	fclose(fp);
	return 0;
}

void operateFile(FILE* fp){
	char *buf=NULL;
	char length=0;
	int index;

	getline(&buf,&length,fp);
	recordNo=getNumber(buf);//获得总记录数
	recordSize=(int*)malloc(sizeof(int)*(recordNo+1));
	for(int i=0;i<recordNo;i++){
		getline(&buf,&length,fp);
		recordSize[i+1]=getNumber(buf);
	}
	recordSize[0]=ftell(fp);//获得基址

	while(scanf("%d",&index)){
	if(index>recordNo){
		err_exit("The index you input ISN'T EXIST");
		break;}
	fseek(fp,getOffset(index)+recordSize[0],SEEK_SET);
	getline(&buf,&length,fp);
	puts(buf);
	}

	free(recordSize);
}

int getNumber(char* buf){
	int res=0;
	for(int i=0;i<strlen(buf);i++){
		if(buf[i]>='0'&&buf[i]<='9'){
			res = res*10 + buf[i] -'0';
		}
	}
	return res;
}

int getOffset(int index){
	int offset=0;
	for(int i=1;i<index;i++)
		offset+=(recordSize[i]+1);//每个记录项的大小加上\n这一字节
	return offset;
}
