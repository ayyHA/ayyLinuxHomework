#include "./ch13.h"
int getCharsBit(char buf[1]){
        /* 此处采用奇校验 */
        int checkBit=0;
        for(int i=0;i<8;i++){
                if((buf[0]&(1<<i)))
                        checkBit++;
        }
        return checkBit;
}

int main(){
	int server_fifo_fd,client_fifo_fd;
	struct data_to_pass my_request;
	char client_fifo_name[256],*tmp_char_ptr;
	pid_t mypid;
	int checkBit;

	/* 打开Server管道 */
	server_fifo_fd=open(SERVER_FIFO_NAME,O_WRONLY);
	if(server_fifo_fd==-1){
		perror("Sorry no server");		
	}
	
	/* 创建以PID命名的Clinet FIFO */
	mypid=getpid();
	sprintf(client_fifo_name,CLIENT_FIFO_NAME,mypid);
	if(mkfifo(client_fifo_name,0777)==-1){
		perror("mkfifo failed!\n");
		exit(-1);		
	}	
	/* 向Server Process 连续发送和接收数据 */
	while(1){
		checkBit=0;
		/* 形成给服务进程的数据 */
		printf("Enter your request:");
		fgets(my_request.data,BUFFER_SIZE,stdin);
		if(strcmp(my_request.data,"bye\n")==0||strcmp(my_request.data,"BYE\n")==0)
			break;
		my_request.client_pid = mypid;
		/* 检验位写入 */
		tmp_char_ptr=my_request.data;
		while(*tmp_char_ptr){
			checkBit += getCharsBit(tmp_char_ptr);
			tmp_char_ptr++;
		}
		my_request.checkBit = checkBit;
		/* 向服务发出请求 */
		write(server_fifo_fd,&my_request,sizeof(my_request));
		/* 从Server接受回答,为此,先打开客户接收有名管道 */
		client_fifo_fd = open(client_fifo_name,O_RDONLY);
		if(client_fifo_fd!=-1){
				if(read(client_fifo_fd,&my_request,sizeof(my_request))>0){
					printf("--- I get answer: %s\n",my_request.data);
			}
			close(client_fifo_fd);
		}
	}
	close(server_fifo_fd);
	unlink(client_fifo_name);
	exit(EXIT_SUCCESS);	

}
