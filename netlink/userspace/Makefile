CC = gcc
CFLAGS = -Wall

all: user_netlink

user: ioctl.o
	$(CC) $(CFLAGS) user_netlink.c -o user_netlink

clean:
	rm -rf user_netlink *.o

