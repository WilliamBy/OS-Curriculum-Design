#include <unistd.h>
#include <fcntl.h>
//cp_legacy.c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 256
char buffer[BUFFER_SIZE];

int main(int argc, char const *argv[])
{
    if (argc == 1)
    {
        printf("cp: missing file operand\n");
    }
    else if (argc == 2)
    {
        printf("cp: missing destination file operand after '%s'\n", argv[1]);
    }
    int src_fd = open(argv[1], O_RDONLY);
    if (src_fd == -1)
    {
        fprintf(stderr, "err: fail to open source file '%s'\n", argv[1]);
        return -1;
    }
    // the third parameter is about permission of new file
    int des_fd = open(argv[2], O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
    if (des_fd == -1)
    {
        fprintf(stderr, "err: fail to open target file '%s'\n",argv[2]);
        return -1;
    }
    ssize_t rn = 0, wn = 0; //number of read or write
    while ((rn = read(src_fd, buffer, BUFFER_SIZE)) != 0)
    {
        if (rn == -1)
        {
            fprintf(stderr, "err: %s\n", strerror(errno));
            return -1;
        }
        wn = write(des_fd, buffer, rn);
        if (wn == -1)
        {
            fprintf(stderr, "err: %s\n", strerror(errno));
            return -1;
        }
    }
    close(src_fd);
    close(des_fd);
    return 0;
}
