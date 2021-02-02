#include "./ch1-22.h"
int main(){
	union{
		short inum;
		char c[sizeof(short)];
	}un;
	struct utsname uts;
	un.inum = 0x0102;
	/* 打印出操作系统及其版本号 */
	if(uname(&uts) < 0)
		perror("Could not get host information!\n");
	printf(" %s-%s-%s: ",uts.machine,uts.sysname,uts.release);
	/* 检测字节顺序 */
	if(sizeof(short) != 2)
		printf("sizeof short : %d\n",sizeof(short));
	else if(un.c[0]==1 && un.c[1]==2)
		printf("big endian\n");
	else if(un.c[0]==2 && un.c[1]==1)
		printf("little endian\n");
	else
		printf("unknown!\n");
	exit(EXIT_SUCCESS);
}
