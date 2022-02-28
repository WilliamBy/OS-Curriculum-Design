#include "copythread.h"
#include "pv.h"

CopyThread::CopyThread(QObject *parent, int shmid):
    QThread(parent),
    shmid(shmid)
{
    return;
}

CopyThread::~CopyThread()
{
    return;
}

void CopyThread::run()
{
    int cBytesAll = 0;
    shm_struct *shm_handle = (shm_struct *)shmat(shmid, NULL, SHM_R | SHM_W);
    while (1)
    {
        P(shm_handle->semid, f1);
        if (shm_handle->l1 < 0)
        {
            emit err();
            exit(1);
        }
        P(shm_handle->semid, e2);
        memcpy(shm_handle->buf2, shm_handle->buf1, shm_handle->l1);
        shm_handle->l2 = shm_handle->l1;
        fprintf(stderr, "copy %d\n", shm_handle->l2);
        if (shm_handle->l2 == 0)
        {
            V(shm_handle->semid, e1);
            V(shm_handle->semid, f2);
            fprintf(stderr, "copy should ok\n");
            exit(0);
        }
        V(shm_handle->semid, e1);
        V(shm_handle->semid, f2);
        if (shm_handle != 0)
        {
            cBytesAll += shm_handle->l2;
//            emit rate((100 * cBytesAll) / shm_handle->amountBytes);
        }
    }
}

void CopyThread::errhandle()
{
    this->exit(1);
}
