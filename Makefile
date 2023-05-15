CROSS_COMPILE:=arm-linux-gnueabihf-

CC:=$(CROSS_COMPILE)gcc
LD:=$(CROSS_COMPILE)ld

KERN_DIR=/home/luo/linux/kernel/linux-imx-rel_imx_4.1.15_2.1.0_ga_alientek

all:
	make -C $(KERN_DIR) M=`pwd` modules
	arm-linux-gnueabihf-gcc -o test_fb test_fb.c
	sudo cp ov7670_csi_driver.ko test_fb /home/luo/mnt/nfs/rootfs/home/luo/drivers/video

clean:
	make -C $(KERN_DIR) M=`pwd` clean

obj-m+=ov7670_csi_driver.o