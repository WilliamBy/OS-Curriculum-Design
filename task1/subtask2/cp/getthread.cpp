#include "getthread.h"
#include "pv.h"

GetThread::GetThread(QObject *parent, int shmid):
    QThread(parent),
    shmid(shmid)
{
    return;
}

GetThread::~GetThread()
{
    return;
}

void GetThread::run()
{
    shm_struct *shm_handle = (shm_struct *)shmat(shmid, NULL, SHM_R | SHM_W);
    int rbytes; //读入的字节数
    int rbytesAll = 0;
    do
    {
        P(shm_handle->semid, e1);
        rbytes = read(shm_handle->from, shm_handle->buf1, BUFSIZE);
        fprintf(stderr, "get %d\n", rbytes);
        shm_handle->l1 = rbytes;
        V(shm_handle->semid, f1);
        if (rbytes == -1)
        {
            fprintf(stderr, "err: %s\n", strerror(errno));
            emit err();
            exit(1);
        } else if (rbytes != 0 && shm_handle->amountBytes != 0) {
            rbytesAll += rbytes;
//            emit rate((100 * rbytesAll) / shm_handle->amountBytes);
        }
    } while (rbytes != 0);
    fprintf(stderr, "get should ok\n");
    exit(0);
}

void GetThread::errHandle()
{
    this->exit(1);
}
