#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR ("Johannes 4 GNU/Linux");
MODULE_DESCRIPTION("A simple gpio driver for setting a LED and reading a button");

/* Variables for device and device class */
static dev_t my_device_nr;
static struct class *my_class;
static struct cdev my_device;

#define DRIVER_NAME "my_joystick"
#define DRIVER_CLASS "MyModuleClass_joy"

/**
* @brief Read data out of the buffer
*/
static ssize_t driver_read(struct file *File, char *user_buffer, size_t count, loff_t *offs) {
	int to_copy, not_copied, delta;
	char tmp[2];

	/* Get amount of data to copy */
	to_copy = min(count, sizeof(tmp));

	/* Read value of button */

	tmp[0] = gpio_get_value(15) + '0';
	tmp[1] = gpio_get_value(18) + '0';



	not_copied = copy_to_user(user_buffer, &tmp, to_copy);

/*
	tmp = gpio_get_value(5) + '0';
	not_copied = copy_to_user(user_buffer, &tmp, to_copy);


	tmp = gpio_get_value(6) + 'A';
	not_copied = copy_to_user(user_buffer, &tmp, to_copy);
*/


	/* Calculate data */
	delta = to_copy - not_copied;


	return delta;
}

/**
* @brief Write data to buffer
*/
static ssize_t driver_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs) {
	int to_copy, not_copied, delta;
	char value;
	
	/* Get amount of data to copy */
	to_copy = min(count, sizeof(value));
	
	/* Copy data to user */
	not_copied = copy_from_user(&value, user_buffer, to_copy);

	/* Calculate data */
	delta = to_copy - not_copied;
	return delta;
}

/**
* @brief This function is called, when the device file is opened
*/
static int driver_open(struct inode *device_file, struct file *instance) {
	printk("joystick driver - open was called! \n");
	return 0;
}
/**
* @brief This function is called, when the device file is opened
*/
static int driver_close(struct inode *device_file, struct file *instance) {
	printk("joystick  driver - close was called! \n");
	return 0;
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close,
	.read = driver_read,
	.write = driver_write
};

/**
* @brief This function is called, when the module is loaded into the kernel
*/
static int __init ModuleInit(void) {
	printk("Hello, Kernel! by joystick\n");

	/* Allocate a device nr */
	if ( alloc_chrdev_region(&my_device_nr, 0, 1, DRIVER_NAME) < 0) {
		printk("Device Nr. could not be allocated! \n");
		return -1;
	}
	printk("joy) read_write - Device Nr. Major: %d, Minor: %d was registered! \n", my_device_nr >> 20, my_device_nr && 0xfffff);
	
	/* Create device class */
	if((my_class = class_create(THIS_MODULE, DRIVER_CLASS)) == NULL) {
		printk("Device class can not be created! \n");
		goto ClassError;
	}
	/* create device file */
	if (device_create(my_class, NULL, my_device_nr, NULL, DRIVER_NAME) == NULL) {
		printk("Can not create device file! \n");
		goto FileError;
	}
	
	/* Initialize device file */
	cdev_init(&my_device, &fops);

	/* Regisering device to kernel */
	if (cdev_add(&my_device, my_device_nr, 1) == -1) {
		printk("Registering of device to kernel failed! \n");
		goto AddError;
	}

	/* GPIO 15 init */
	if (gpio_request(15, "rpi-gpio-15")) {
		printk("Can not allocate GPIO 15\n");
		goto AddError;
	}
	
	/* Set GPIO 15 direction */
	if(gpio_direction_input(15)) {
		printk("Can not set GPIO 15 to input!\n");
		goto Gpio5Error;
	}
	
	/* GPIO 18 init */
	if(gpio_request(18, "rpi-gpio-18")) {
		printk("Can not allocate GPIO 18\n");
		goto AddError;
	}
	
	/* Set GPIO 18 direction */
	if(gpio_direction_input(18)) {
		printk("Can not set GPIO 18 to input!\n");
	goto Gpio6Error;
	}

	return 0;
Gpio5Error:
	gpio_free(15);
Gpio6Error:
	gpio_free(18);
AddError:
	device_destroy(my_class, my_device_nr);
FileError:
	class_destroy (my_class);
ClassError:
	unregister_chrdev_region(my_device_nr, 1);
	return -1;
}

/**
* @brief This function is called, when the module is removed from the kernel
*/
static void __exit ModuleExit(void) {
	gpio_free(15);
	gpio_free(18);
	cdev_del (&my_device);
	device_destroy(my_class, my_device_nr);
	class_destroy(my_class);
	unregister_chrdev_region(my_device_nr, 1);
	printk("Goodbye, Kernel\n");
}

module_init(ModuleInit);
module_exit(ModuleExit);
