#include "./ch10.h"
// 通过argv[]之值，使用命令
int main(int argc,char* argv[]){
	//char* args=(char*)malloc(sizeof(char)*argc);
	char args[200];
	memset(args,0,200);
	int j=0;
	for(int i=1;i<argc;i++)
		j+=sprintf(args+j,"%s ",argv[i]);// 每次返回成功写入的字节数，通过j这个偏移量来定位未写入内容的区域
	
	//char buf[200];
	//memset(buf,0,200);
	//j=0;
	//for(int i=0;i<3;i++){
	//	j += sprintf(buf+j,"Iami%d ",i);
	//	printf("i=%d, j=%d\n",i,j);
	//}
	//printf("buf = %s\n",buf);
	//printf("args=%s\n",args);
	//printf("args=%s\n",args);
	
	system((const char*)args);//1、fork();2、sh-c;3、wait();
	return 0;
}
