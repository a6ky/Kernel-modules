#include "include/ioctl_dev.h"

static long dev_ioctl(struct file *filp, unsigned int cmd,
			unsigned long arg)
{
	char *buf_msg = kzalloc(LEN_MSG, GFP_KERNEL);

	switch (cmd) {
	case WRITE_IOCTL:
		if (copy_to_user((char *)arg, hello_str, LEN_MSG))
			return -EFAULT;
		pr_info("write to user space: %s\n", (char *)arg);
		break;
	case READ_IOCTL:
		if (copy_from_user(buf_msg, (char *)arg, LEN_MSG))
			return -EFAULT;
		pr_info("read from user space: %s\n", buf_msg);
		break;
	default:
		return -ENOTTY;
	}

	return 0;
}

static int __init dev_init(void)
{
	int ret;

	ret = misc_register(&misc_chardev);
	if (ret < 0) {
		pr_info("misc_register failed with %d\n", ret);
		goto err;
	}

	pr_info("=========== module installed %d:%d =========\n",
			10, misc_chardev.minor);

err:
	return ret;
}

static void __exit dev_exit(void)
{
	misc_deregister(&misc_chardev);
	pr_info("=============== module removed =============\n");
}
