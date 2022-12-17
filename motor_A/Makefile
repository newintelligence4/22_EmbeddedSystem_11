obj-m += motordriver.o
KDIR = ~/working/kernel_64bit
RESULT=motor
SRC		= $(RESULT).c

CCC=arm-linux-gnueabihf-gcc

all	:
	make -C $(KDIR) M=$(PWD) modules
	$(CCC) -o $(RESULT) $(SRC)

clean	:
	make -C $(KDIR) M=$(PWD) clean
	rm -f $(RESULT)
