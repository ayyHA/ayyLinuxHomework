#include "ch4.h"
#define BUF_SIZE 8

int y_or_n_ques(const char* question);
int main(){
	FILE* fp;
	int fgets_yes;
	struct iobuf{
		char buf[BUF_SIZE];
		char others[BUF_SIZE];
	}buffer;
	memset(&buffer,'\0',sizeof(struct iobuf));
	do{
		/* 请用户选择使用fgets()还是gets() */
		fgets_yes =y_or_n_ques("Should we read by fgets()?");
		fprintf(stdout,"please enter a line\n");
		if(fgets_yes){	/* 使用fgets读输入数据 */
			fgets(buffer.buf,BUF_SIZE,stdin);
			fprintf(stdout,"fgets() get string \" %s \" \n",buffer.buf);
			while(buffer.buf[strlen(buffer.buf)-1]!='\n'){	/* 一行未读完，继续读 */
				fgets(buffer.buf,BUF_SIZE,stdin);
				fprintf(stdout,"fgets() get string \"%s\" \n",buffer.buf);
			}
		}else{							/* 使用gets读输入数据 */
			gets(buffer.buf);
			fprintf(stdout,"gets() get string \" %s \" \n",buffer.buf);
		}	
		/* 查看溢出情况 */
		fprintf(stdout,"buffer.others is \" %s \" \n",buffer.others);
	}while(y_or_n_ques("continue?"));
	exit(0);
}


int y_or_n_ques(const char* question){
	fputs(question,stdout);		/* 输出提问 */
	while(1){
		int c,answer;
		fputc(' ',stdout);	/* 写一空格分开问题与回答 */
		/* 读此行第一个字符。它应当是回答字符，但也可能不是 */
		c = tolower(fgetc(stdin));
		answer = c;
		while(c != '\n' && c != EOF)		/* 忽略此行其余字符 */
			c = fgetc(stdin);
		if(answer == 'y')			/* 如果是回答字符，则响应回答 */
			return 1;
		if(answer =='n')
			return 0;
		fputs("Please answer y or n:",stdout);		/* 非回答字符，继续要求合法回答 */
	}
}
