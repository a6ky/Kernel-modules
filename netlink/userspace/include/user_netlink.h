#ifndef _USER_NETLINK_H
#define _USER_NETLINK_H

#include <sys/socket.h>
#include <linux/netlink.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define NETLINK_USER 31
#define MAX_PAYLOAD 1024 /* maximum payload size*/

struct sockaddr_nl src_addr, dest_addr;
struct nlmsghdr *nlh;
struct iovec iov;
struct msghdr msg;

#endif