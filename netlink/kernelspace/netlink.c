#include "include/netlink.h"

static void hello_nl_recv_msg(struct sk_buff *skb)
{
	struct nlmsghdr *nlh;
	int pid;
	struct sk_buff *skb_out;
	int msg_size;
	char *msg = "Hello from kernel";
	int res;

	pr_info("Entering: %s\n", __PRETTY_FUNCTION__);

	msg_size = strlen(msg);

	nlh = (struct nlmsghdr *)skb->data;
	pr_info("Netlink received msg payload:%s\n", (char *)nlmsg_data(nlh));
	pid = nlh->nlmsg_pid; /*pid of sending process */

	skb_out = nlmsg_new(msg_size, 0);
	if (!skb_out) {
		pr_info("Failed to allocate new skb\n");
		return;
	}

	nlh = nlmsg_put(skb_out, 0, 0, NLMSG_DONE, msg_size, 0);
	NETLINK_CB(skb_out).dst_group = 0; /* not in mcast group */
	strncpy(nlmsg_data(nlh), msg, msg_size);

	res = nlmsg_unicast(nl_sk, skb_out, pid);
	if (res < 0)
		pr_info("Error while sending bak to user\n");
}

static int __init hello_init(void)
{
	pr_info("Entering: %s\n", __PRETTY_FUNCTION__);
	/*nl_sk = netlink_kernel_create(&init_net, NETLINK_USER,
				0, hello_nl_recv_msg, NULL, THIS_MODULE);*/
	nl_sk = netlink_kernel_create(&init_net, NETLINK_USER, &cfg);
	if (!nl_sk) {
		pr_info("Error creating socket.\n");
		return -10;
	}

	return 0;
}

static void __exit hello_exit(void)
{
	pr_info("exiting hello module\n");
	netlink_kernel_release(nl_sk);
}


