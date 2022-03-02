#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <linux/version.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#define MYBUFFSIZE 32

MODULE_LICENSE("GPL");

char mybuff[MYBUFFSIZE];
unsigned int mydev_major = 0;

static int mydev_open(struct inode *inodep, struct file *filep)
{
    printk(KERN_INFO "mydev open\n");
    return 0;
}

static int mydev_release(struct inode *inodep, struct file *filep)
{
    printk(KERN_INFO "mydev release\n");
    return 0;
}

static ssize_t mydev_read(struct file *filep, char __user *usrbuff, size_t count, loff_t *offset)
{
    printk(KERN_INFO "mydev read\n");
    if (verify_area(0, usrbuff, count) == -EFAULT) return -EFAULT;

    int ret;
    size_t avail = MYBUFFSIZE - *offset;

    if (count <= avail)
    {
        if (copy_to_user(usrbuff, mybuff + *offset, count) != 0)
            return -EFAULT;
        *offset += count;
        ret = count;
    }
    else
    {
        if (copy_to_user(usrbuff, mybuff + *offset, avail) != 0)
            return -EFAULT;
        *offset += avail;
        ret = avail;
    }

    printk(KERN_INFO "mydev: read %u bytes\n", ret);
    return ret;
}

static ssize_t mydev_write(struct file *filep, const char __user *usrbuff, size_t count, loff_t *offset)
{
    printk(KERN_INFO "mydev : start write\n");
    if (verify_area(1, usrbuff, count) == -EFAULT) return -EFAULT;   

    int ret;
    size_t avail = MYBUFFSIZE - *offset;

    if (count > avail)
    {
        if (copy_from_user(mybuff + *offset, usrbuff, avail) != 0)
            return -EFAULT;
        *offset += avail;
        ret = avail;
    }
    else
    {
        if (copy_from_user(mybuff + *offset, usrbuff, count) != 0)
            return -EFAULT;
        *offset += count;
        ret = count;
    }

    printk(KERN_INFO "mydevice: written %u bytes\n", ret);
    return ret;
}

static const struct file_operations myfops = {
    .open = mydev_open,
    .release = mydev_release,
    .read = mydev_read,
    .write = mydev_write,
};

static int mydev_init(void)
{
    printk(KERN_INFO "mydev init\n");

    int result;
    result = register_chrdev(0, "mydev", &myfops);
    if (result < 0)
    {
        return result;
    }
    if (mydev_major == 0)
        mydev_major = result;
    return 0;
}

static void mydev_exit(void)
{
    unregister_chrdev(mydev_major, "mydev");
}

module_init(mydev_init);
module_exit(mydev_exit);
