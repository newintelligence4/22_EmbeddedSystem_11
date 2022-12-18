#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>

/* Meta Infornation*/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Johannes 4 GNU/Linux");
MODULE_DESCRIPTION("A simple gpio driver for motor");

/*Variables for device and device class */
static dev_t my_device_nr;
static struct class* my_class;
static struct cdev my_device;

#define DRIVER_NAME "my_motor"
#define DRIVER_CLASS "HyModuleClass_seg"

/***
*@brief Write data to buffer
*/
static ssize_t driver_write(struct file* File, const char* user_buffer, size_t count, loff_t* offs) {
	int to_copy, not_copied, delta;
	unsigned short value = 0;

	/* Get anount of data to copy */
	to_copy = min(count, sizeof(value));

	/* Copy data to user*/
	not_copied = copy_from_user(&value, user_buffer, to_copy);
	/* Setting the segrents LED */

	/*add*/
	//////////////////////////////////////////
	//left
	if (value & (1 << 12)) {
		gpio_set_value(19, 1);
	}
	else {
		gpio_set_value(19, 0);
	}

	//right
	if (value & (1 << 13)) {
		gpio_set_value(26, 1);
	}
	else {
		gpio_set_value(26, 0);
	}
	//////////////////////////////////////////

	delta = to_copy - not_copied;//ÃÊ±âÈ­?
	return delta;
}

/**
 * @brief This function is called, when the device file is opend
*/
static int driver_open(struct inode* device_file, struct file* instance) {
	printk("segment - open was called!\n");
	return 0;
}

/**
 * @brief This function is called, when the device file is closed
*/
static int driver_close(struct inode* device_file, struct file* instance) {
	printk("segment - close was called!\n");
	return 0;
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close,
	//.read = driver_read,
	.write = driver_write
};


/**
 * @brief This function is called, when the module is loaded into the kernel
 */
static int __init ModuleInit(void) {
	printk("Hello, Kernel!\n");

	/* Allocate a device nr*/
	if (alloc_chrdev_region(&my_device_nr, 0, 1, DRIVER_NAME) < 0) {
		printk("Device Nr. could not be allocated!\n");
		return -1;
	}

	printk("read_write - Device Nr. Major : %d, Minor : %d was registered!\n", my_device_nr >> 20, my_device_nr && 0xffffff);

	/*Create device class*/
	if ((my_class = class_create(THIS_MODULE, DRIVER_CLASS)) == NULL) {
		printk("Device class can not e created! \n");
		goto ClassError;
	}

	/* create device file */
	if (device_create(my_class, NULL, my_device_nr, NULL, DRIVER_NAME) == NULL) {
		printk("Can not create device file!\n");
		goto FileError;
	}

	/* Initialize device fIle */
	cdev_init(&my_device, &fops);

	/*Regisaring device to kernel */
	if (cdev_add(&my_device, my_device_nr, 1) == -1) {
		printk("Registering of device to kernel failed!\n");
		goto AddError;
	}


	/*add*/
	////////////////////////////////////////////
	/* GPIO 19 init LEFT*/
	if (gpio_request(19, "rpi-gpio-19")) {
		printk("Can not allocate GPIO19 \n");
		goto AddError;
	}
	/* Set GPIO 19 direction*/
	if (gpio_direction_output(19, 0)) {
		printk("Can not set GPI0  to output!\n");
		goto Gpio19Error;
	}

	/* GPIO 26 init RIGHT*/
	if (gpio_request(26, "rpi-gpio-26")) {
		printk("Can not allocate GPIO26 \n");
		goto AddError;
	}
	/* Set GPIO 26 direction*/
	if (gpio_direction_output(26, 0)) {
		printk("Can not set GPI0  to output!\n");
		goto Gpio26Error;
	}
	/////////////////////////////////////////////
	return 0;



	/*19,26*/
Gpio19Error:
	gpio_free(19);

Gpio26Error:
	gpio_free(26);

AddError:
	device_destroy(my_class, my_device_nr);
FileError:
	class_destroy(my_class);
ClassError:
	unregister_chrdev_region(my_device_nr, 1);
	return -1;

}


/**
 * @brief This function is called, when the module is removed from the kernel
 */
static void __exit ModuleExit(void) {
	
	gpio_set_value(19, 0);//add
	gpio_set_value(26, 0);//add
	gpio_free(19);//add
	gpio_free(26);//add
	cdev_del(&my_device);
	device_destroy(my_class, my_device_nr);
	class_destroy(my_class);
	unregister_chrdev_region(my_device_nr, 1);
	printk("Goodbye, Kernel\b");
}

module_init(ModuleInit);
module_exit(ModuleExit);

