// copy.c
#include "header.h"

int main(int argc, char const *argv[])
{
    int shmid, semid;
    sscanf(argv[1], "%d", &shmid);
    sscanf(argv[2], "%d", &semid);
    shm_struct *shm_handle = (shm_struct *)shmat(shmid, NULL, SHM_R | SHM_W);
    while (1)
    {
        P(semid, f1);
        if (shm_handle->l1 < 0)
        {
            return 1;
        }
        P(semid, e2);
        memcpy(shm_handle->buf2, shm_handle->buf1, shm_handle->l1);
        shm_handle->l2 = shm_handle->l1;
        if (shm_handle->l2 == 0)
        {
            V(semid, e1);
            V(semid, f2);
            return 0;
        }
        // else
        // {
        //     printf("copy %d bytes\n", shm_handle->l1);
        // }
        V(semid, e1);
        V(semid, f2);
    }
    return 0;
}