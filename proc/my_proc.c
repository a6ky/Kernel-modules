#include "include/my_proc.h"


ssize_t proc_read(struct file *filp, char *buf, size_t len, loff_t *offp)
{
	if (len > LEN_MSG)
		len = LEN_MSG;

	if (*offp != 0) {
		pr_info("read return : 0\n");  /* EOF */
		return 0;
	}

	if (copy_to_user(buf, buf_msg, len))
		goto err;

	*offp = len;

	return len;

err:
	pr_info("read_proc: error copying data to user space\n");
	return -1;
}

ssize_t proc_write(struct file *filp, const char *buf, size_t len, loff_t *offp)
{
	char *msg = kzalloc(LEN_MSG, GFP_KERNEL);

	if (copy_from_user(msg, buf, len))
		goto err;

	pr_info("write_proc: %s\n", msg);

	return len;

err:
	pr_info("read_proc: error copying data from user space\n");
	return -1;
}

static int __init proc_init(void)
{
	int ret;
	struct proc_dir_entry *own_proc_node;

	own_proc_node = proc_create(PROCFS_NAME, S_IFREG | S_IRUGO | S_IWUGO,
								NULL, &fops);
	if (own_proc_node == NULL) {
		ret = -ENOMEM;
		pr_info("can't create /proc/%s\n", PROCFS_NAME);
		goto err_node;
	}

	pr_info("/proc/%s created\n", PROCFS_NAME);

	return 0;

err_node:
	return ret;
}

static void __exit proc_exit(void)
{
	remove_proc_entry(PROCFS_NAME, NULL);
	pr_info("/proc/%s removed\n", PROCFS_NAME);
}
