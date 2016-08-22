#include "include/my_cdev.h"

/* Прием аргументов командной строки */
module_param(major, int, S_IRUGO);

static int dev_open(struct inode *n, struct file *f)
{
	if (device_open)
		return -EBUSY;

	device_open++;

	return -EOK;
}

static int dev_release(struct inode *n, struct file *f)
{
	device_open--;

	return -EOK;
}

static ssize_t dev_read(struct file *file, char *buf,
			size_t count, loff_t *offp)
{
	int len = strlen(hello_str);

	pr_info("=== read : %d\n", (int)count);

	if (count < len)
		return -EINVAL;

	if (*offp != 0) {
		pr_info("=== read return : 0\n");  /* EOF */
		return 0;
	}

	if (copy_to_user(buf, hello_str, len))
		return -EINVAL;

	*offp = len;
	pr_info("=== read return : %d\n", (int)len);

	return len;
}

static ssize_t dev_write(struct file *file, const char *buf,
						size_t len, loff_t *offp)
{
	char *usr_msg = kzalloc(len, GFP_KERNEL);

	if (!usr_msg)
		return -ENOMEM;

	if (!strncpy_from_user(usr_msg, buf, len)) {
		pr_info("FAILED strncpy_from_user\n");
		return -EFAULT;
	}

	pr_info("=== write msg from userspace: %s\n", usr_msg);
	pr_info("=== write return : %d\n", (int)len);

	kfree(usr_msg);

	return len;
}

static int __init dev_init(void)
{
	int ret;
	dev_t dev;

	/* если мы явно задали номера утроства */
	if (major != 0) {
		dev = MKDEV(major, DEVICE_FIRST);
		ret = register_chrdev_region(dev, DEVICE_COUNT, MODNAME);
	} else {
	/* Получаем свободный мажорный */
		ret = alloc_chrdev_region(&dev, DEVICE_FIRST, DEVICE_COUNT,
			MODNAME);
		major = MAJOR(dev);
	}

	if (ret < 0) {
		pr_info("=== Can not register char device region\n");
		goto err;
	}

	/* регестрируем устройство */
	cdev_init(&hcdev, &dev_fops);
	hcdev.owner = THIS_MODULE;
	ret = cdev_add(&hcdev, dev, DEVICE_COUNT);

	if (ret < 0) {
		unregister_chrdev_region(MKDEV(major, DEVICE_FIRST),
								DEVICE_COUNT);
		pr_info("=== Can not add char device\n");
		goto err;
	}

	pr_info("=========== module installed %d:%d =========\n",
			MAJOR(dev), MINOR(dev));

err:
	return ret;
}

static void __exit dev_exit(void)
{
	cdev_del(&hcdev);
	unregister_chrdev_region(MKDEV(major, DEVICE_FIRST), DEVICE_COUNT);
	pr_info("=============== module removed =============\n");
}
