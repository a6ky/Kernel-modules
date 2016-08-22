TARGET = hello
obj-m += $(TARGET).o

KERNELDIR := /usr/src/linux-headers-$(shell uname -r)
PWD := $(shell pwd)

all:
	sudo $(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	sudo rm -rf *.o *.ko *.order *.symvers *.mod.c .chdev.* .tmp_versions

