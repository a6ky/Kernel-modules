#ifndef _CHANGE_PORT_H
#define _CHANGE_PORT_H

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/skbuff.h>
#include <linux/inet.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <linux/uaccess.h>
#include <uapi/linux/udp.h>
#include <net/ip.h>

#define NF_IP_PRE_ROUTING	0
#define NF_IP_LOCAL_IN      1
#define NF_IP_POST_ROUTING	4

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Alexey Stolpovsky <stolpovsky6@gmail.com>");
MODULE_DESCRIPTION("change dest port");
MODULE_VERSION("1.0");

struct nf_hook_ops netfilter_ops_in;

unsigned int filter_hook(void *, struct sk_buff *,
	const struct nf_hook_state *);

/* hook-функкия для входящих пакетов */
struct nf_hook_ops netfilter_ops_in = {
	.hook = filter_hook,
	.pf = PF_INET,
	.hooknum = NF_IP_PRE_ROUTING,
	.priority = NF_IP_PRI_FIRST,
};

#endif
