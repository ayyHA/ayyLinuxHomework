#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <dlfcn.h>
#include <setjmp.h>
#include <wait.h>
#include <errno.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/utsname.h>
#define SERVPORT 3333
#define MAXDATASIZE 100

#define SERVER_FIFO_NAME "./server_fifo"	// Server专用FIFO文件名
#define CLIENT_FIFO_NAME "./client_%d_fifo"	// Client专用FIFO文件名
#define BUFFER_SIZE 132

#define PIPE_BUF 100
#define FIFO_FILE "./testfifo"
#define TEN_MEG 1000
#define INFILE "./in.txt"
#define OUTFILE "./out.txt"
#define MODE S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH
#define SHMSIZ 27
/*void err_exit(char* s){
	printf("USAGE: %s is failed!\n",s);
	exit(0);*/
//}
struct data_to_pass{
	pid_t client_pid;		// 客户进程的PID
	char data[BUFFER_SIZE];		// 正文内容
	int checkBit;			// 奇偶校验位
};

struct my_msg{
	long int my_msg_type;
	char text[100];
};
