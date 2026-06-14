obj-m += rpi_gpio_module.o

ARCH := arm64
CROSS_COMPILE := aarch64-linux-gnu-

KDIR := /home/seif/workspace/linux

all:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean