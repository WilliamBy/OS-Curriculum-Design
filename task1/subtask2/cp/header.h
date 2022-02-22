//header.h
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
#define BUFSIZE 256 //共享缓冲区大小

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
    int l1; //buf1有效字节长度
    int l2; //buf2有效字节长度
} shm_struct;

const int e1 = 0, f1 = 1, e2 = 2, f2 = 3; //信号灯编号，e代表空缓冲区，f代表满缓冲区

void P(int semid, int index)
{
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = -1;
    sem.sem_flg = 0;       //操作标记：0或IPC_NOWAIT等
    semop(semid, &sem, 1); // 1:表示执行命令的个数
    return;
}

void V(int semid, int index)
{
    struct sembuf sem;
    sem.sem_num = index;
    sem.sem_op = 1;
    sem.sem_flg = 0;
    semop(semid, &sem, 1);
    return;
}