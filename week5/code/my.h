#ifndef MY_H
#define MY_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>


typedef struct user{
	int id;
	char name[8];
	char htel[12];
	char tel[12];
}recorder;

//--
extern recorder* user;
extern recorder** userList;
extern int countOfRecord;
//--
void randdat();
//void showUserList();
void output();
void setUserList();
void input(void);
void save(recorder* user);
int cmpAscend(const void* p1,const void* p2);
int cmpDescend(const void* p1,const void* p2);
void mySort();
void isUnique();
#endif
