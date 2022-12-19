obj-m	+=	seg_driver.o \
			button_driver.o 
all:
	make -C ~/working/kernel/ M=$(PWD) modules

clean:
	make -C ~/working/kernel/ M=$(PWD) clean
