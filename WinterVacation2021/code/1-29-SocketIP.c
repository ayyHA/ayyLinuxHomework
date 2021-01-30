#include "./ch1-22.h"
int itoa(int num,char* str,int base);

int main(){
	/* 保留IP地址宏符号名 */
	/*
	printf("INADDR_LOOPBACK : %d\n ",INADDR_LOOPBACK);
	printf("INADDR_ANY : %d\n",INADDR_ANY);
	printf("INADDR_BROADCAST : %d\n",INADDR_BROADCAST);
	*/

	/*======================*/
	char* origin_addr_ipv4 = "192.168.1.1";
	int addr_num_ipv4;
	char* addr_str_ipv4;
	addr_str_ipv4 = (char*)malloc(2048*(sizeof(char)));
	
	/* 古老的方法inet_aton  */
	struct in_addr origin_addr_bin;
	inet_aton(origin_addr_ipv4,&origin_addr_bin);
	itoa(origin_addr_bin.s_addr,addr_str_ipv4,2);
	printf("192.168.1.1 by inet_aton Binary : %s\n",addr_str_ipv4);
	
	
	/* 古老的方法inet_ntoa */
	char* reverse_origin_addr_ipv4;
	reverse_origin_addr_ipv4=inet_ntoa(origin_addr_bin);
	printf("192.168.1.1 by inet_ntoa ASCII : %s\n",reverse_origin_addr_ipv4);

	/*======================*/
	/*char* origin_addr_ipv6 = "::FFFF:192.168.1.1";*/
	char* origin_addr_ipv6 = "5FC4:0000:0000:ED00:CF06:0400:BA0E:0021";
	int addr_num_ipv6;
	char* addr_str_ipv6;
	addr_str_ipv6 = (char*)malloc(BUFSIZ*sizeof(char));

	/* 崭新的方法inet_pton */
	struct in6_addr origin_addr6_bin;
	inet_pton(AF_INET6,origin_addr_ipv6,&origin_addr6_bin);	
	for(int i=0;i<16;i++){
		if(i%2!=0){
			printf("%02x:",origin_addr6_bin.s6_addr[i]);
		}
		else{
			printf("%02x",origin_addr6_bin.s6_addr[i]);
		}
	}
	printf("\n");

	/*	
	itoa(origin_addr6_bin.s6_addr[0],addr_str_ipv6,2);
	printf("::FFFF:192.168.1.1 by inet_pton Binary : %s",addr_str_ipv6);
	for(int i=1;i<=15;i++){
		itoa(origin_addr6_bin.s6_addr[i],addr_str_ipv6,2);
		printf("%s",addr_str_ipv6);
	}
	printf("\n");
	*/

	/* 崭新的方法inet_ntop */
	char* reverse_origin_addr_ipv6;
	reverse_origin_addr_ipv6 = (char*)malloc(BUFSIZ*sizeof(char));
	inet_ntop(AF_INET6,&origin_addr6_bin,reverse_origin_addr_ipv6,INET6_ADDRSTRLEN);
	printf("inet_ntop Persentation : %s\n",reverse_origin_addr_ipv6);

	/*======================*/
	free(addr_str_ipv4);
	free(addr_str_ipv6);
	free(reverse_origin_addr_ipv6);
	return 0;
}

int itoa(int num,char* str,int base)
{
	int i=0,j,tmp=num;
	int a[2048];
	char *buf;
	char t[1];
	memset(a,0,sizeof(a));
	buf = (char*)malloc(2048*sizeof(char));
	if(base==2){
		while(tmp){
			a[i++]=tmp%2;
			tmp /=2;
		}		
		/*printf("a[]=");*/
		for(j=i-1;j>=0;j--){
			sprintf(t,"%d",a[j]);
			strcat(buf,t);
			/*printf("%d",a[j]);*/
		}
		/*printf("\n");*/
		/*printf("buf:%s\n",buf);*/
		strcpy(str,buf);
		free(buf);
		return 1;
	}	
	else{
		perror("Base System error!\n");
		exit(EXIT_FAILURE);
	}
}
