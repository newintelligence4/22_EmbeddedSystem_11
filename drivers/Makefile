obj-m	+=	seg_driver.o \
			button_driver.o \
			joystick_driver.o \
			motordriver.o

all:
	make -C ~/subjects/temp/linux M=$(PWD) modules

clean:
	make -C ~/subjects/temp/linux M=$(PWD) clean