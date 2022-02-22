//read.c
#include "header.h"

int main(int argc, char const *argv[])
{
    printf("read proc\n");
    int shmid, semid;
    sscanf(argv[1], "%d", &shmid);
    sscanf(argv[2], "%d", &semid);
    shm_struct *shm_handle = (shm_struct *)shmat(shmid, NULL, SHM_R | SHM_W);
    int from;
    int rbytes; //读入的字节数
    if ((from = open(argv[3], O_RDONLY)) == -1)
    {
        fprintf(stderr, "err: fail to open source file '%s'\n", argv[3]);
        return 1;
    }
    do
    {
        P(semid, e1);
        rbytes = read(from, shm_handle->buf1, BUFSIZE);
        shm_handle->l1 = rbytes;
        V(semid, f1);
        if (rbytes == -1)
        {
            fprintf(stderr, "err: %s\n", strerror(errno));
            close(from);
            return 1;
        }
        // else 
        // {
        //     printf("read %d bytes\n", rbytes);
        // }
    } while (rbytes != 0);
    close(from);
    return 0;
}