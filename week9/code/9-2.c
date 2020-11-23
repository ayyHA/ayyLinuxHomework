#include "./ch9.h"
int g_int =1;

int main(){
	pid_t pid;
	int l_int=99;
	int *pt = malloc(sizeof(int));
	char* string= "test stirng!";
	*pt = 9999;
	printf("%d:----Before fork-----",getpid());

	pid = fork();
	if(pid<0){
		fprintf(stderr,"failed to fork.Reason(%s)",strerror(errno));
		exit(-1);
	}
	else if(pid==0) {
		printf("child : pid =%d, ppid = %d return from fork()=%d\n",getpid(),getppid(),pid);
		printf("child : init g =%d,l=%d,*pt=%d\n",g_int,l_int,*pt);
		g_int++;
		l_int++;
		(*pt)++;
		printf("child : g=%d %x,l=%d %x,*pt=%d %x\n",g_int,&g_int,l_int,&l_int,*pt,pt);
		printf("child : string =%s\n",string);
		exit(0);
	}
	else{
		sleep(2);
		printf("parent : pid =%d,ppid =%d return from fork()=%d\n",getpid(),getppid(),pid);
		printf("parent : init g =%d,l=%d,*pt=%d\n",g_int,l_int,*pt);
                g_int++;
                l_int++;
                (*pt)++;
                printf("parent : g=%d %x,l=%d %x,*pt=%d %x\n",g_int,&g_int,l_int,&l_int,*pt,pt);
		printf("parent : string =%s\n",string);
		return 0;
	}
}
