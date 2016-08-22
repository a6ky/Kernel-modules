#ifndef _MY_PROC_H
#define _MY_PROC_H

#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/stat.h>
#include <linux/slab.h>
#include <asm/uaccess.h>

#define PROCFS_NAME "my_proc"
#define LEN_MSG 160

static char buf_msg[LEN_MSG] = "Hello from proc module!\n";
static const struct file_operations fops;

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alexey Stolpovsky <stolpovsky6@gmail.com>");
MODULE_DESCRIPTION("example proc dev module");
MODULE_VERSION("1.0");

ssize_t proc_read(struct file *, char *, size_t, loff_t *);
ssize_t proc_write(struct file *, const char *, size_t, loff_t *);

static const struct file_operations fops = {
	.read = proc_read,
	.write = proc_write,
};

static int __init proc_init(void);
module_init(proc_init);

static void __exit proc_exit(void);
module_exit(proc_exit);

#endif
