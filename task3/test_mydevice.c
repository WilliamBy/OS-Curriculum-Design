#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
int main(int argc, char const *argv[])
{
    int mydev_fd = open("/dev/mydev", O_RDWR, 0666);
    if (mydev_fd == -1)
    {
        fprintf(stderr, "fail to open '/dev/mydev': %s\n", strerror(errno));
        return 1;
    }
    ssize_t wbytes = 0;
    if ((wbytes = write(mydev_fd, "hello, world!", 13)) < 0)
    {
        fprintf(stderr, "write failed\n");
    }
    else
    {
        printf("%d bytes writen\n");
    }
    ssize_t rbytes = 0;
    char buf[256];
    if ((rbytes = read(mydev_fd, buf, 13)) < 0)
    {
        fprintf(stderr, "read failed\n");
        return 1;
    }
    else
    {
        printf("%d bytes read: %s\n", buf);
    }
    return 0;
}
