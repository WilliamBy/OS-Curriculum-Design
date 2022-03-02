#ifndef PV_H
#define PV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/fcntl.h>
#include <errno.h>

#define BUFSIZE 32 //共享缓冲区大小

namespace SysIO {
int close(int fd);
}

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

//共享缓冲区结构体
typedef struct SHM_STRUCT
{
    char buf1[BUFSIZE]; //缓冲区1
    char buf2[BUFSIZE]; //缓冲区2
    int semid; //信号灯集合句柄
    int l1; //buf1有效字节长度
    int l2; //buf2有效字节长度
    int from, to;  //源文件、目标文件描述符
    long long amountBytes;    //Bytes num of the whole file
    int rate_get;
    int rate_copy;
    int rate_put;
} shm_struct;

void P(int semid, int index);
void V(int semid, int index);
const int e1 = 0, f1 = 1, e2 = 2, f2 = 3; //信号灯编号，e代表空缓冲区，f代表满缓冲区


#endif // PV_H
