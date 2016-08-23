#include <linux/module.h>
#include <linux/sched.h>

static int __init allproc_init(void)
{
	struct task_struct *p;

	for (p = &init_task ; (p = list_entry_rcu((p)->tasks.next,
	     struct task_struct, tasks)) != &init_task ;)
		pr_info("%s [pid:%d]\n", p->comm, p->pid);

	return 0;
}

static void __exit allproc_fini(void)
{
}

module_init(allproc_init);
module_exit(allproc_fini);
