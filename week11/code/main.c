#include "./my.h"

// 1 tree home
// 2 prtInfo()
// 3 Gather
int main(){
	int fd=open("log.dat",O_RDWR|O_CREAT|O_TRUNC,0644);
	pid_t pid1;
	pid1=fork();
	if(pid1<0){
		perror("pid1 failed fork!\n");
		exit(-1);
	}
	else if(pid1==0){
		pid_t pid11;
		pid11=fork();
		if(pid11<0){
			perror("pid11 failed fork!\n");
			exit(-1);
		}
		else if(pid11==0){
			prtInfo(fd,getpid(),3);
			//printf("Ch11 : pid = %d, ppid =%d\n",getpid(),getppid());
			exit(0);
		}
		else{
			int r11,s11;
			r11=wait(&s11);
			prtInfo(fd,getpid(),1);
			//printf("Ch1 : pid = %d, ppid =%d\n",getpid(),getppid());
			exit(0);
		}
	}
	else{
		pid_t pid2;
		pid2=fork();
		if(pid2<0){
			perror("pid2 failed fork!\n");
			exit(-1);
		}
		else if(pid2==0){
			pid_t pid21;
			pid21=fork();
			if(pid21<0){
				perror("pid21 failed fork!\n");
				exit(-1);
			}
			else if(pid21==0){
				prtInfo(fd,getpid(),4);
				//printf("Ch21 : pid = %d, ppid =%d\n",getpid(),getppid());
				exit(0);
			}
			else{
				int r21,s21;
				r21=wait(&s21);
				prtInfo(fd,getpid(),2);
				//printf("Ch2 : pid = %d, ppid =%d\n",getpid(),getppid());
				exit(0);
			}
		}
		else{
			int r1,r2,s1,s2;
			r1=wait(&s1);	//等待ch1、ch2
			r2=wait(&s2);
			prtInfo(fd,getpid(),0);
			//printf("Parent : pid = %d!\n Parent finished!\n",getpid());
		
			close(fd);
			fd=open("./log.dat",O_RDWR);	
			char buf[1024];
			memset(buf,0,1024);
			while(read(fd,buf,1024)){
				printf("%s",buf);
			}
			
			close(fd);
			return 0;
		}
	}
}
