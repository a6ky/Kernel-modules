#ifndef _NETLINK_H
#define _NETLINK_H

#include <linux/module.h>
#include <net/sock.h> 
#include <linux/netlink.h>
#include <linux/skbuff.h> 
#define NETLINK_USER 31

struct sock *nl_sk = NULL;

static void hello_nl_recv_msg(struct sk_buff *);

struct netlink_kernel_cfg cfg = {
	.input = hello_nl_recv_msg,
};

static int __init hello_init(void);
module_init(hello_init);

static void __exit hello_exit(void);
module_exit(hello_exit);

#endif