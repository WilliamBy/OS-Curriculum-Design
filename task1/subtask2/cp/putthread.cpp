#include "putthread.h"
#include "pv.h"

PutThread::PutThread(QObject *parent, int shmid):
    QThread(parent),
    shmid(shmid)
{
    return;
}

PutThread::~PutThread()
{
    return;
}

void PutThread::run()
{
    shm_struct *shm_handle = (shm_struct *)shmat(shmid, NULL, SHM_R | SHM_W);
    int wbytes;           //写入的字节数
    int wBytesAll = 0;
    do
    {
        P(shm_handle->semid, f2);
        if (shm_handle->l2 < 0)
        {
            fprintf(stderr, "err: write proccess aborted\n");
            emit err();
            exit(1);
        }
        wbytes = write(shm_handle->to, shm_handle->buf2, shm_handle->l2);
        fprintf(stderr, "put %d\n", wbytes);
        V(shm_handle->semid, e2);
        if (wbytes < 0)
        {
            fprintf(stderr, "err: %s\n", strerror(errno));
            emit err();
            exit(1);
        }
        else if (wbytes > 0 && shm_handle->amountBytes != 0)
        {
            wBytesAll += wbytes;
//            emit rate((100 * wBytesAll) / shm_handle->amountBytes);
        }
    } while (wbytes != 0);
    fprintf(stderr, "put should ok\n");
    exit(0);
}

void PutThread::errHandle()
{
    this->exit(1);
}
