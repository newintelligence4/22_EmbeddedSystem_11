obj-m += motordriver.o
KDIR = ~/working/Raspbian/kernel

all	:
	make -C ~/working/Raspbian/kernel
	M=$(PWD) modules

clean	:
	make -C ~/working/kernel
	M=$(PWD) clean
