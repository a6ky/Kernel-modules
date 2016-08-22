#ifndef _MY_CDEV_H
#define _MY_CDEV_H

#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <asm/uaccess.h>

#define EOK 0
#define DEVICE_FIRST  0
#define DEVICE_COUNT  1
#define MODNAME "my_cdev_dev"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alexey Stolpovsky <stolpovsky6@gmail.com>");
MODULE_DESCRIPTION("example char dev module");
MODULE_VERSION("1.0");

static int major;
static int device_open;

/* Зарегистрированное устройство */
static struct cdev hcdev;

static char *hello_str = "Hello, world!\n";

static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);

static const struct file_operations dev_fops = {
	.owner = THIS_MODULE,
	.open = dev_open,
	.release = dev_release,
	.read  = dev_read,
	.write = dev_write,
};

static int __init dev_init(void);
module_init(dev_init);

static void __exit dev_exit(void);
module_exit(dev_exit);

#endif
