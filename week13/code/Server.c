#include "./ch13.h"
/* 
Server 通过 Server FIFO 获取Client信息 即读之
Server 通过 Client FIFO 向Client输出响应信息 即写之
*/
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
	int server_fifo_fd,client_fifo_fd;		// Server用的fd Client用的fd
	struct data_to_pass my_data;			// 定义数据包
	int nbytes;					// 接受读入请求数据的返回值 
	char client_fifo_name[256],*tmp_char_ptr;	// 等待合成的客户fifo name
	pid_t pidChild;
	int reqNum=0;
	int checkBit=0;
	/* 创建Server FIFO 并打开之 */
	if(mkfifo(SERVER_FIFO_NAME,0777)==-1){
		perror("mkfifo failed!\n");		// 成功为0 失败为-1，于errno得知原因
		exit(-1);
	}			
	
	server_fifo_fd = open(SERVER_FIFO_NAME,O_RDONLY);	// 打开管道,以读方式
	if(server_fifo_fd==-1){
		perror("open server failed!\n");
		exit(-1);	
	}
	
	do{
		/* 获得来自Client的信息 */
		nbytes=read(server_fifo_fd,&my_data,sizeof(my_data));
		//checkBit=0;
		if(nbytes>0){					// 处理Client的请求，大变小，小变大，回车换行变\0
			pidChild=fork();
			if(pidChild<0){
				perror("fork failed!\n");
				exit(-1);
			}
			else if(pidChild==0){
				tmp_char_ptr = my_data.data;
				while(*tmp_char_ptr){
					checkBit += getCharsBit(tmp_char_ptr);
					if(isupper(*tmp_char_ptr))
						*tmp_char_ptr = tolower(*tmp_char_ptr);
					else if(islower(*tmp_char_ptr))
						*tmp_char_ptr = toupper(*tmp_char_ptr);
					else if(*tmp_char_ptr == '\n')
						*tmp_char_ptr = '\0';
					tmp_char_ptr++;

				}
				if(checkBit==my_data.checkBit)
					printf("transfer %d,Right!\n",my_data.checkBit);

				/* 将处理后的数据返回给客户。根据客户的进程ID确定回答所用的FIFO */		
				sprintf(client_fifo_name,CLIENT_FIFO_NAME,my_data.client_pid);
				client_fifo_fd = open(client_fifo_name,O_WRONLY);	
				if(client_fifo_fd!=-1){
					write(client_fifo_fd,&my_data,sizeof(my_data));
					close(client_fifo_fd);
				}
				printf("robot:%d finished!\n",getpid());
				exit(0);
			}
			else{
				reqNum++;
			}
		}
	}while(nbytes>0);
	printf("Deal %d request!\n",reqNum);
	close(server_fifo_fd);
	unlink(SERVER_FIFO_NAME);
	return 0;
}	
