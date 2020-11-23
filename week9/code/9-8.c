#include "./ch9.h"
int g=0;
int main(){
	int fd = open("./testForMidtest.txt",O_CREAT|O_WRONLY|O_TRUNC,0644);
	char buf[20];
	memset(buf,0,20);
	pid_t pid[2];
	pid_t pid2[2];
	//printf("I am the father! my pid=%d\n",getpid());
	//printf("Grandfather:%d:%d\n",getpid(),++g);//!
	sprintf(buf,"%d:%d\n",getpid(),++g);
	write(fd,buf,strlen(buf));
	memset(buf,0,20);
	printf("I am the father! my pid=%d\n%d:%d\n",getpid(),getpid(),g);
	for(int i=0;i<2;i++){
		//printf("GrandFather:%d:%d\n",getpid(),++g);//!
		if(i==1)//!
			g++;//!
		pid[i]=fork();
		if(pid[i]<0){
			perror("FORK FAILED!\n");
			exit(EXIT_FAILURE);
		}
		else if(pid[i]==0&&i==0){		
			//waitpid(pid[0]+1,NULL,0);//!
			sprintf(buf,"%d:%d\n",getpid(),++g);
		        write(fd,buf,strlen(buf));
			memset(buf,0,20);
			//printf("Father1:%d:%d\n",getpid(),++g);//!
			printf("My pid=%d,my parent pid=%d\n%d:%d\n",getpid(),getppid(),getpid(),g);
			++g;//!
			for(int j=0;j<2;j++){
				pid2[j]=fork();
				if(j==1)g++;
				if(pid2[j]<0){
					perror("CHILD FORK FAILED!\n");
					exit(EXIT_FAILURE);
				}
				else if(pid2[j]==0){
					sprintf(buf,"%d:%d\n",getpid(),++g);
	 			        write(fd,buf,strlen(buf));
					memset(buf,0,20);
					printf("My pid=%d,my parent pid=%d\n%d:%d\n",getpid(),getppid(),getpid(),g);
					//printf("Child%d:%d:%d",j,getpid(),++g);//!
					exit(0);
				}
			//	else{
			//		if(j==0)
			//			printf("My pid=%d,my parent pid=%d\n",getpid(),getppid());
			//	}	
				
			}

			for(int j=0;j<2;++j ){
               			 waitpid(pid2[j],NULL,0);
            			}
			exit(0);
			
		}
		else if(pid[i]==0&&i==1){
			//fprintf(fd,"%d:%d\n",getpid(),++g);
			sprintf(buf,"%d:%d\n",getpid(),++g);
		        write(fd,buf,strlen(buf));
			memset(buf,0,20);
			printf("My pid=%d,my parent pid=%d\n%d:%d\n",getpid(),getppid(),getpid(),g);
			//printf("Father2:%d:%d\n",getpid(),++g);//!
			exit(0);
		}
	//	else{
	//		if(i==0)
	//			printf("I am the father! my pid=%d\n g=%d",getpid(),++g);	
	//	}
	}

	for(int i=0;i<2;++i ){
                waitpid(pid[i],NULL,0);
         }
}
