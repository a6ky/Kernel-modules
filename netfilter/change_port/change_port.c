#include "include/change_port.h"

unsigned int filter_hook(void *priv, struct sk_buff *skb,
	const struct nf_hook_state *state)
{
	struct iphdr *ip_header = ip_hdr(skb);
	struct udphdr *udp_header = udp_hdr(skb);
	static unsigned int upd_len;

	unsigned int src_ip = (unsigned int)ip_header->saddr;
	unsigned int dest_ip = (unsigned int)ip_header->daddr;

	unsigned int src_port = 0;
	unsigned int dest_port = 0;

	if (ip_header->protocol == IPPROTO_UDP) {
		src_port = (unsigned int)ntohs(udp_header->source);
		dest_port = (unsigned int)ntohs(udp_header->dest);

		if (udp_header->dest == htons(32000)) {
			udp_header->dest = htons(32002);
			pr_info("old csum: %d", udp_header->check);
			upd_len = skb->len - ip_hdrlen(skb);
			udp_header->check = 0;
			udp_header->check = csum_tcpudp_magic(ip_header->saddr,
						ip_header->daddr,
						upd_len,
						IPPROTO_UDP,
						csum_partial((char *)udp_header,
							upd_len, 0));
			pr_info("new csum: %d", udp_header->check);
		}
	}

	pr_info("src ip: %pI4  dst ip: %pI4\n", &src_ip, &dest_ip);
	pr_info("src port: %d  dst port: %d\n", src_port, dest_port);

	return NF_ACCEPT;
}

int init_module(void)
{
	pr_info("Module started ...\n");
	nf_register_hook(&netfilter_ops_in);

	return 0;
}

void cleanup_module(void)
{
	nf_unregister_hook(&netfilter_ops_in);
	pr_info("Module stopped ...\n");
}


