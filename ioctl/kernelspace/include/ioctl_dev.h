#ifndef _IOCTL_DEV_H
#define _IOCTL_DEV_H

#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alexey Stolpovsky <stolpovsky6@gmail.com>");
MODULE_DESCRIPTION("example ioctl dev module");
MODULE_VERSION("1.0");

#define LEN_MSG 160

#define IOC_MAGIC 'h'
#define READ_IOCTL _IOR(IOC_MAGIC, 0, char *)
#define WRITE_IOCTL _IOW(IOC_MAGIC, 1, char *)

static long dev_ioctl(struct file *, unsigned int,
					unsigned long);

static const struct file_operations dev_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = dev_ioctl
};

static struct miscdevice misc_chardev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "my_ioctl_dev",
	.fops = &dev_fops,
	.mode = 0666
};

static char *hello_str = "Hello, user!\n";

static int __init dev_init(void);
module_init(dev_init);

static void __exit dev_exit(void);
module_exit(dev_exit);

#endif
