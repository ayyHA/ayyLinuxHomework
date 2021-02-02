#include "my.h"

recorder* user=NULL;	//用户新增记录的实例
int countOfRecord=0;	//用户记录的条数
recorder** userList=NULL;	//统计的用户列表
void input(){
	printf("if you don't want to insert a new data,please enter \'n\'");
	char c;
	scanf("%c",&c);
	if(c=='n'||c=='N'){
		isUnique();
		return;
	}

	user =(recorder*)malloc(sizeof(recorder));

	printf("Please input your ID:");
	scanf("%d",&user->id);
	
	printf("Please input your name:");
	scanf("%s",user->name);
	
	printf("Please input your home telephone:");
	scanf("%s",user->htel);
	
	printf("Please input your telephone:");
	scanf("%s",user->tel);
	
	//以下是唯一性检验
	isUnique();
}

void save(recorder* user){
	FILE* fp ;
	if(!(fp = fopen("user.dat","a+"))){
		perror("FILE OPEN FAILED!\n");
		free(user);
		exit(0);
	}
	fprintf(fp,"\n %03d\t%s\t%s\t%s",user->id,user->name,user->htel,user->tel);
	fclose(fp);
	countOfRecord++;
	printf("Save success!\n");
}

int cmpAscend(const void* p1,const void* p2){
	return strcmp((*(recorder**)p1)->name,(*(recorder**)p2)->name);
//	return strcmp(((recorder*)p1)->name,((recorder*)p2)->name);
}

int cmpDescend(const void* p1,const void* p2){
	return -(strcmp((*(recorder**)p1)->name,(*(recorder**)p2)->name));
}

void mySort(){
	printf("Now you can sort your user list\n");
	printf("Please input 1-Ascend 2-Descend\n");
	int option;
	scanf("%d",&option);

	if(option!=1&&option!=2){
		printf("ERROR INPUT!\n");
		return;
	}
//	if(userList==NULL)
		setUserList();
	//printf("set FINISHED\n");
	//showUserList();
	printf("The following is the sorted result!");
	if(option==1){
		//qsort(*userList,countOfRecord,sizeof(recorder),cmpAscend);
		qsort(userList,countOfRecord,sizeof(recorder*),cmpAscend);
		//output();
	}else{
		qsort(userList,countOfRecord,sizeof(recorder*),cmpDescend);
		//output();
	}	
}

void isUnique(){
	
	int flag=0;
        FILE* fp = fopen("./user.dat","r");
        char* buf=(char*)malloc(100);
        int n=0;
	int userId,i;
//	getline(&buf,&n,fp);//此行读去菜单项
        fgets(buf,100,fp);      //读去菜单项

	if(user==NULL){		//此为了在n的状态下算出countOfRecord的值
		while(fgets(buf,100,fp)!=-1&&!feof(fp))
				countOfRecord++;
		countOfRecord++;
		return;
	}

       	while(fgets(buf,100,fp)!=-1&&!feof(fp)){
                userId=0;i=1;
                while(1){
                        if(buf[i]>='0'&&buf[i]<='9'){
                                userId = userId*10 + buf[i]-'0';
                                i++;
                        }
                        else
                                break;

                }
		countOfRecord++;
                if(userId==user->id){
                        flag=1;
                        break;
                }
        }
	
	fgets(buf,100,fp);	//读末项
	userId=0;i=1;
	while(1){
		if(buf[i]>='0'&&buf[i]<='9'){
			userId = userId*10 + buf[i]-'0';
			i++;
		}
		else
			break;
	}
	countOfRecord++;
	if(userId==user->id)
		flag=1;

        fclose(fp);
        free(buf);
        if(flag){
                perror("the ID IS REPEAT!");
                free(user);
		exit(0);
        }

}


// 获得用户的所有信息
void setUserList(){
	
	int id;
	char name[8],htel[12],tel[12];
	memset(name,0,sizeof(name));
	memset(htel,0,sizeof(htel));
	memset(tel,0,sizeof(tel));
	
	userList =(recorder**)malloc(sizeof(recorder*)*countOfRecord);
	FILE* fp;
	if(!(fp=fopen("./user.dat","r"))){
		perror("FILE OPEN FAILED!\n");
		//free(userList);
		exit(0);
	}
	
	char* buf=(char*)malloc(100);
	fgets(buf,100,fp);

	
	for(int i=0;i<countOfRecord;i++){
//		if(feof(fp))
//			break;
		userList[i]=(recorder*)malloc(sizeof(recorder));
		fgets(buf,100,fp);
		
		sscanf(buf,"%d %s %s %s",&id,name,htel,tel);
		userList[i]->id=id;
		strcpy(userList[i]->name,name);
		strcpy(userList[i]->htel,htel);
		strcpy(userList[i]->tel,tel);
		
	}
	
	fclose(fp);
	free(buf);

}

void output(){
	for(int i=0;i<countOfRecord;i++){
		printf(" \n %03d\t%s\t%s\t%s",userList[i]->id,userList[i]->name,userList[i]->htel,userList[i]->tel);
	}
}

void randdat(){
	char* tmpName=NULL;
	int htel1,htel2,tel1,tel2,tel3,tel4;
	char* tmpHtel=NULL;
	char* tmpTel=NULL;

	if(userList==NULL)
		setUserList();
	
	for(int i=0;i<countOfRecord;i++){
		tmpName=userList[i]->name;
		tmpName[0]=tmpName[0]-32;				//首字母大小写转换
		strcpy(userList[i]->name,tmpName);
		sscanf(userList[i]->htel,"%3d %8d",&htel1,&htel2);	//htel
		sprintf(userList[i]->htel,"%d-%d",htel1,htel2);

		sscanf(userList[i]->tel,"%3d %3d %3d %d",&tel1,&tel2,&tel3,&tel4);//tel
		sprintf(userList[i]->tel,"%d,%d,%d,%d",tel1,tel2,tel3,tel4);
	}
	printf("\n\n RANDDAT:\n");
//	output();
}
