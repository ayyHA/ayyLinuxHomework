#include "ch2.h"
int main(int argc,char* argv[])
{	
	FILE* fp;
        if((fp=fopen("./text5.txt","w"))==NULL)
                perror("open failed!\n");

        for(int i=1;i<argc;i++){
                fwrite(argv[i],1,strlen(argv[i]),fp);
                printf("[%d]: \t %s \t %ld byte\n",i,argv[i],strlen(argv[i]));
        }
        return 0;
}
