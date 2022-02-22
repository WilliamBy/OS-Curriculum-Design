// 多进程双缓冲并发誊抄源程序 cp.c
#include "header.h"

int shmid; //共享内存句柄
int semid; //信号灯集合句柄
int from = 0, to = 0;  //源文件、目标文件描述符
pid_t pid_main, pid_get, pid_copy, pid_put;   //进程号

int get()
{
    shm_struct *shm_handle = (shm_struct *)shmat(shmid, NULL, SHM_R | SHM_W);
    int rbytes; //读入的字节数
    do
    {
        P(semid, e1);
        rbytes = read(from, shm_handle->buf1, BUFSIZE);
        shm_handle->l1 = rbytes;
        V(semid, f1);
        if (rbytes == -1)
        {
            fprintf(stderr, "err: %s\n", strerror(errno));
            kill(pid_main, SIGUSR1);
            return 1;
        }
    } while (rbytes != 0);
    return 0;
}

int copy()
{
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
        V(semid, e1);
        V(semid, f2);
    }
    return 0;
}

int put()
{
    shm_struct *shm_handle = (shm_struct *)shmat(shmid, NULL, SHM_R | SHM_W);
    int wbytes;           //写入的字节数
    do
    {
        P(semid, f2);
        if (shm_handle->l2 < 0)
        {
            fprintf(stderr, "err: write proccess aborted\n");
            kill(pid_main, SIGUSR1);
            return 1;
        }
        wbytes = write(to, shm_handle->buf2, shm_handle->l2);
        V(semid, e2);
        if (wbytes < 0)
        {
            fprintf(stderr, "err: %s\n", strerror(errno));
            kill(pid_main, SIGUSR1);
            return 1;
        }
    } while (wbytes != 0);
    return 0;
}

/* 父进程的中断信号处理 */
void sig_handler(int sig_no)
{
    if (sig_no == SIGUSR1)
    {
        kill(pid_get, SIGKILL);
        kill(pid_copy, SIGKILL);
        kill(pid_put, SIGKILL);
        wait(NULL);
        wait(NULL);
        wait(NULL);
        close(from);
        close(to);
    }
}

int main(int argc, char const *argv[])
{
    if (signal(SIGUSR1, sig_handler) == SIG_ERR)
    {
        fprintf(stderr, "%s", strerror(errno));
        return 1;
    }
    /* 命令行格式检查 */
    if (argc == 1)
    {
        printf("cp: missing file operand\n");
        return 0;
    }
    else if (argc == 2)
    {
        printf("cp: missing destination file operand after '%s'\n", argv[1]);
        return 0;
    }

    /* 创建文件描述符 */
    if ((from = open(argv[1], O_RDONLY)) == -1)
    {
        fprintf(stderr, "err: fail to open source file '%s'\n%sn", argv[1], strerror(errno));
        return 1;
    }
    struct stat src_stat; //获取源文件mode
    if (stat(argv[1], &src_stat) == -1)
    {
        fprintf(stderr, "err: fail to get file stat '%s'\n%s\n", argv[1], strerror(errno));
        return 1;
    }
    if ((to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, src_stat.st_mode)) == -1)
    {
        fprintf(stderr, "err: fail to open destinate file '%s'\n%s\n", argv[2], strerror(errno));
        return 1;
    }

    /* 创建共享内存 */
    if ((shmid = shmget(IPC_PRIVATE, sizeof(shm_struct), IPC_CREAT | 0666)) < 0)
    {
        fprintf(stderr, "shmget failed: %s\n", strerror(shmid));
        return 1;
    }
    shm_struct *shm_handle = (shm_struct *)shmat(shmid, NULL, SHM_R | SHM_W);
    shm_handle->l1 = 0;
    shm_handle->l2 = 0;

    /* 创建信号灯集 */
    if ((semid = semget(IPC_PRIVATE, 5, IPC_CREAT | 0666)) < 0)
    {
        fprintf(stderr, "semget failed: %s\n", strerror(semid));
        return 1;
    }

    /* 信号灯赋予初值, 初始设置信号灯初始值 */
    union semun arg;
    arg.val = 1;
    if (semctl(semid, e1, SETVAL, arg) == -1)
    {
        fprintf(stderr, "can't set a value for 'e1'!\n");
        semctl(semid, e1, IPC_RMID, NULL);
        return 1;
    }
    if (semctl(semid, e2, SETVAL, arg) == -1)
    {
        fprintf(stderr, "can't set a value for 'e2'!\n");
        semctl(semid, e2, IPC_RMID, NULL);
        return 1;
    }
    arg.val = 0;
    if (semctl(semid, f1, SETVAL, arg) == -1)
    {
        fprintf(stderr, "can't set a value for 'f1'!\n");
        semctl(semid, f1, IPC_RMID, NULL);
        return 1;
    }
    if (semctl(semid, f2, SETVAL, arg) == -1)
    {
        fprintf(stderr, "can't set a value for 'f2'!\n");
        semctl(semid, f2, IPC_RMID, NULL);
        return 1;
    }

    pid_main = getpid();    //存储父进程pid
    /* 创建read, copy, write进程 */
    if ((pid_get = fork()) == 0)
    {
        return get();
    }
    else if ((pid_copy = fork()) == 0)
    {
        return copy();
    }
    else if ((pid_put = fork()) == 0)
    {
        return put();
    }
    else
    {
        int pr_stat, pc_stat, pw_stat;
        /* 等待子进程结束 */
        waitpid(pid_get, &pr_stat, 0);
        waitpid(pid_copy, &pc_stat, 0);
        waitpid(pid_put, &pw_stat, 0);
        close(from);
        close(to);
        if (!WIFEXITED(pr_stat))
        {
            fprintf(stderr, "read proc terminated incorrectly");
        }
        if (!WIFEXITED(pc_stat))
        {
            fprintf(stderr, "copy proc terminated incorrectly");
        }
        if (!WIFEXITED(pw_stat))
        {
            fprintf(stderr, "write proc terminated incorrectly");
        }
        /* 删除信号灯集和共享内存 */
        if (semctl(semid, 0, IPC_RMID, arg) == -1)
        {
            fprintf(stderr, "can't delete sems!\n");
            return 1;
        }
        if (shmctl(shmid, IPC_RMID, 0) < 0)
        {
            fprintf(stderr, "can't delete shms!\n");
            return 1;
        }
    }
    return 0;
}