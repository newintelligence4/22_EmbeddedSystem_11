obj-m += button_driver.o
RESULT	= button_driver
SRC		= $(RESULT).c

all	:
	make -C ~/working/kernel M=$(PWD) modules
	aarch64-linux-gnu-gcc -o $(RESULT) $(SRC)

clean	:
	make -C ~/working/kernel M=$(PWD) clean
	rm -f $(RESULT)
