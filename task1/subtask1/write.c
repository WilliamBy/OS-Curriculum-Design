// write.c
#include "header.h"

int main(int argc, char const *argv[])
{
    int shmid, semid;
    sscanf(argv[1], "%d", &shmid);
    sscanf(argv[2], "%d", &semid);
    shm_struct *shm_handle = (shm_struct *)shmat(shmid, NULL, SHM_R | SHM_W);
    int to;
    int wbytes; //写入的字节数
    if ((to = open(argv[3], O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO)) == -1)
    {
        fprintf(stderr, "err: fail to open destinate file '%s'\n", argv[3]);
        return 1;
    }
    do
    {
        P(semid, f2);
        if (shm_handle->l2 < 0)
        {
            fprintf(stderr, "err: write proccess aborted\n");
            close(to);
            return 1;
        }
        wbytes = write(to, shm_handle->buf2, shm_handle->l2);
        V(semid, e2);
        if (wbytes < 0)
        {
            fprintf(stderr, "err: %s\n", strerror(errno));
            close(to);
            return 1;
        }
        // else
        // {
        //     printf("write %d bytes\n", wbytes);
        // }
    } while (wbytes != 0);
    close(to);
    return 0;
}