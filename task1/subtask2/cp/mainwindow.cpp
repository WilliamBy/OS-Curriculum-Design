#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    cDialog(new ConfirmDialog(this)),
    popup(new Dialog(this)),
    debug(new Dialog(this)),
    getProg(new Progressor(this)),
    copyProg(new Progressor(this)),
    putProg(new Progressor(this)),
    ui(new Ui::MainWindow)
{
    getProg->setProgress(0);
    copyProg->setProgress(0);
    putProg->setProgress(0);
    getProg->setTitle("GET PROGRESS");
    copyProg->setTitle("COPY PROGRESS");
    putProg->setTitle("PUT PROGRESS");
    ui->setupUi(this);
    getProg->move(0, 0);
    copyProg->move(0 + 200, 0 + 100);
    putProg->move(0 + 400, 0 + 200);
    /* 创建共享内存 */
    if ((shmid = shmget(IPC_PRIVATE, sizeof(shm_struct), IPC_CREAT | 0666)) < 0)
    {
        fprintf(stderr, "shmget failed: %s\n", strerror(shmid));
    }
    shm_handle = (shm_struct *)shmat(shmid, NULL, SHM_R | SHM_W);
    QObject::connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &MainWindow::recConfirm);
    QObject::connect(cDialog, &ConfirmDialog::accept, [this]
    {
        QByteArray srcArr, desArr;
        srcArr.append(ui->srcEdit->text());
        desArr.append(ui->desEdit->text());
        getProg->show();
        copyProg->show();
        putProg->show();
        cp(srcArr.data(), desArr.data());
    });
}

MainWindow::~MainWindow()
{
    /* 删除信号灯集和共享内存 */
    union semun arg;
    if (semctl(shm_handle->semid, 0, IPC_RMID, arg) == -1)
    {
        fprintf(stderr, "can't delete sems!\n");
    }
    if (shmctl(shmid, IPC_RMID, 0) < 0)
    {
        fprintf(stderr, "can't delete shms!\n");
    }
    delete ui;
}

void MainWindow::recConfirm()
{
    QString src = ui->srcEdit->text(), des = ui->desEdit->text();
    if (src.isEmpty() || des.isEmpty())
    {
        popup->setText("input cannot be empty!");
        popup->show();
        return;
    }
    cDialog->setDes(des);
    cDialog->setSrc(src);
    cDialog->show();
}

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

int MainWindow::cp(const char *src, const char *des)
{
    /* 创建文件描述符 */
    if ((shm_handle->from = open(src, O_RDONLY)) == -1)
    {
        fprintf(stderr, "err: fail to open source file '%s'\n%s", src, strerror(errno));
        return 1;
    }
    struct stat src_stat; //获取源文件mode
    if (stat(src, &src_stat) == -1)
    {
        fprintf(stderr, "err: fail to get file stat '%s'\n%s\n", src, strerror(errno));
        return 1;
    }
    shm_handle->amountBytes = src_stat.st_size;
    fprintf(stderr, "filesize: %d\n", shm_handle->amountBytes);
    if ((shm_handle->to = open(des, O_CREAT | O_WRONLY | O_TRUNC, src_stat.st_mode)) == -1)
    {
        fprintf(stderr, "err: fail to open destinate file '%s'\n%s\n", des, strerror(errno));
        return 1;
    }
    shm_handle->l1 = 0;
    shm_handle->l2 = 0;

    /* 创建信号灯集 */
    if ((shm_handle->semid = semget(IPC_PRIVATE, 5, IPC_CREAT | 0666)) < 0)
    {
        fprintf(stderr, "semget failed: %s\n", strerror(shm_handle->semid));
        return 1;
    }

    /* 信号灯赋予初值, 初始设置信号灯初始值 */
    union semun arg;
    arg.val = 1;
    if (semctl(shm_handle->semid, e1, SETVAL, arg) == -1)
    {
        fprintf(stderr, "can't set a value for 'e1'!\n");
        semctl(shm_handle->semid, e1, IPC_RMID, NULL);
        return 1;
    }
    if (semctl(shm_handle->semid, e2, SETVAL, arg) == -1)
    {
        fprintf(stderr, "can't set a value for 'e2'!\n");
        semctl(shm_handle->semid, e2, IPC_RMID, NULL);
        return 1;
    }
    arg.val = 0;
    if (semctl(shm_handle->semid, f1, SETVAL, arg) == -1)
    {
        fprintf(stderr, "can't set a value for 'f1'!\n");
        semctl(shm_handle->semid, f1, IPC_RMID, NULL);
        return 1;
    }
    if (semctl(shm_handle->semid, f2, SETVAL, arg) == -1)
    {
        fprintf(stderr, "can't set a value for 'f2'!\n");
        semctl(shm_handle->semid, f2, IPC_RMID, NULL);
        return 1;
    }
    /* 创建get, copy, put进程 */
    getThread = new GetThread(nullptr, shmid);
    copyThread = new CopyThread(nullptr, shmid);
    putThread = new PutThread(nullptr, shmid);
    QObject::connect(getThread, &GetThread::err, [&](){
        putThread->exit(1);
        copyThread->exit(1);
    });
    QObject::connect(copyThread, &CopyThread::err, [&](){
        putThread->exit(1);
        getThread->exit(1);
    });
    QObject::connect(putThread, &PutThread::err, [&](){
        getThread->exit(1);
        copyThread->exit(1);
    });
    QObject::connect(getThread, &GetThread::rate, [&](int rate)
    {
        if (rate > getProg->getProgress())
        {
            fprintf(stderr, "refresh get: %d\n", rate);
            getProg->setProgress(rate);
        }
    });
    QObject::connect(copyThread, &CopyThread::rate, [&](int rate)
    {
        if (rate > copyProg->getProgress())
        {
            fprintf(stderr, "refresh copy: %d\n", rate);
            copyProg->setProgress(rate);
        }
    });
    QObject::connect(putThread, &PutThread::rate, [&](int rate)
    {
        if (rate > putProg->getProgress())
        {
            fprintf(stderr, "refresh put: %d\n", rate);
            putProg->setProgress(rate);
        }

    });
    QObject::connect(putThread, &PutThread::complete, this, &MainWindow::copyCompleted);
    ui->buttonBox->setEnabled(false);
    getThread->start();
    copyThread->start();
    putThread->start();
    ui->buttonBox->setEnabled(false);
    return 0;
}

int SysIO::close(int fd)
{
    return close(fd);
}

void MainWindow::copyCompleted()
{
    fprintf(stderr, "the whole copy completed!\n");
    ui->buttonBox->setEnabled(true);
    popup->setText("Copy Proccess Succeed.");
    popup->show();
    return;
}
