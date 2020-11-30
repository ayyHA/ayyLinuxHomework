#include "./my.h"
void prtInfo(int fd,int pid,int name){
	time_t t;
	time(&t);
	struct tm *tm_t;
	tm_t =localtime(&t);
	char buftime[100];
	memset(buftime,0,100);
	sprintf(buftime,"%4d %02d %02d %02d:%02d\n",1900+tm_t->tm_year,tm_t->tm_mon+1,tm_t->tm_mday,tm_t->tm_hour,tm_t->tm_min);

	char buf[100];
	memset(buf,0,100);
	char* myName[5]={"parent","ch1","ch2","ch11","ch21"};
	sprintf(buf,"%s pid=%d exit time:",myName[name],pid);
	strcat(buf,buftime);
	write(fd,buf,strlen(buf));	
}
