#include <linux/module.h>
#include <linux/kernel.h>
MODULE_LICENSE("Dual BSD/GPL");

int init_module(void)
{
	pr_info("Hello, world\n");
	return 0;
}

void cleanup_module(void)
{
	pr_info("Goodbye, cruel world\n");
}


