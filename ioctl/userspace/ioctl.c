#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define IOC_MAGIC 'h' 
#define READ_IOCTL _IOR(IOC_MAGIC, 0, char *)
#define WRITE_IOCTL _IOW(IOC_MAGIC, 1, char *)

int main()
{
    int  fd;
    char recv_msg[160];
    char send_msg[] = "Hello, kernel!\0";

    fd = open("/dev/my_ioctl_dev", O_RDWR);
    if (fd < 0){
        perror("open /dev/my_ioctl");
        return -1;
    }

    ioctl(fd, READ_IOCTL, send_msg);
    ioctl(fd, WRITE_IOCTL, recv_msg);
    printf("Read from kernel space: %s\n", recv_msg);

    close(fd);
    return 0;
}
