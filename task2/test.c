#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

int main(int argc, char*argv[])
{
	long int a=syscall(335, argv[1], argv[2]);
        printf("System call sys_helloworld return %ld\n",a);
        return 0;
}
