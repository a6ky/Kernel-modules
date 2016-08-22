CC = gcc
CFLAGS = -Wall

all: ioctl

user: ioctl.o
	$(CC) $(CFLAGS) ioctl.c -o ioctl

clean:
	rm -rf ioctl *.o

