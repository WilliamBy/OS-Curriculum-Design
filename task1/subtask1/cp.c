//cp.c
#include "header.h"

int main(int argc, char const *argv[])
{
    /* 命令行格式检查 */
    if (argc == 1)
    {
        printf("cp: missing file operand\n");
    }
    else if (argc == 2)
    {
        printf("cp: missing destination file operand after '%s'\n", argv[1]);
    }
    /* 创建共享内存 */
    int shmid;
    if ((shmid = shmget(IPC_PRIVATE, sizeof(shm_struct), IPC_CREAT | 0666)) < 0)
    {
        fprintf(stderr, "shmget failed: %s\n", strerror(shmid));
        return 1;
    }
    shm_struct *shm_handle = (shm_struct *)shmat(shmid, NULL, SHM_R | SHM_W);
    shm_handle->l1 = 0;
    shm_handle->l2 = 0;

    /* 创建信号灯集 */
    int semid; //信号灯集合句柄
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

    /* 创建read, copy, write进程 */
    pid_t pr, pc, pw;
    // 传参给子进程：共享内存号、信号灯集号、誊抄源文件/目标文件路径
    char *const _argv[5] = {(char *)malloc(64 * sizeof(char)), (char *)malloc(256 * sizeof(char)), (char *)malloc(256 * sizeof(char)), (char *)malloc(64 * sizeof(char)), NULL};
    sprintf(_argv[1], "%d", shmid);
    sprintf(_argv[2], "%d", semid);
    if ((pr = fork()) == 0)
    {
        sprintf(_argv[0], "%s", "read");
        sprintf(_argv[3], "%s", argv[1]);
        execv("./read", (char *const *)_argv);
        fprintf(stderr, "fail to execute read proc\n");
        return 1;
    }
    else if ((pc = fork()) == 0)
    {
        sprintf(_argv[0], "%s", "copy");
        execv("./copy", (char *const *)_argv);
        fprintf(stderr, "fail to execute copy proc\n");
        return 1;
    }
    else if ((pw = fork()) == 0)
    {
        sprintf(_argv[0], "%s", "write");
        sprintf(_argv[3], "%s", argv[2]);
        execv("./write", (char *const *)_argv);
        fprintf(stderr, "fail to execute write proc\n");
        return 1;
    }
    else
    {
        int pr_stat, pc_stat, pw_stat;
        /* 等待子进程结束 */
        waitpid(pr, &pr_stat, 0);
        waitpid(pc, &pc_stat, 0);
        waitpid(pw, &pw_stat, 0);
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