obj-m += motordriver.o
KDIR = ~/working/Raspbian/kernel
RESULT=motor
SRC		= $(RESULT).c

CCC=arm-linux-gnueabihf-gcc

all	:
	make -C $(KDIR) M=$(PWD) modules
	$(CCC) -o $(RESULT) $(SRC)

clean	:
	make -C $(KDIR) M=$(PWD) clean
	rm -f $(RESULT)
