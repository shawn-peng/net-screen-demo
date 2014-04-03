
KERNEL	= /work/android-kernel-2.6.35

modules:
	make -C $(KERNEL) M=$(shell pwd) modules

clean:
	make -C $(KERNEL) M=$(shell pwd) modules clean


obj-m	= led.o
