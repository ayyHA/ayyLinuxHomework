#include "./ch14.h"
int main(){
	char c,*shm,*s;
	int shmid;
	if((shmid=shmget((key_t)758,SHMSIZ,IPC_CREAT|0666))<0)
		perror("shmget failed!\n");
	if((shm=shmat(shmid,NULL,0))==(char*)-1)
		perror("shmat failed!\n");
	s = shm;
	for(c='a';c<='z';c++)
		*s++=c;
	*s='\0';
	exit(0);
}
