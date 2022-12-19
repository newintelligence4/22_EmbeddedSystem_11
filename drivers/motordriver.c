#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>

/* Meta Infornation*/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Johannes 4 GNU/Linux");
MODULE_DESCRIPTION("A simple gpio driver for segments");

/*Variables for device and device class */
static dev_t my_device_nr;
static struct class* my_class;
static struct cdev my_device;

#define DRIVER_NAME "my_motordriver"
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
	if (value & (1 << 0)) {//0b0000 0000 0000 0000 0000 0000 0000 0001
		gpio_set_value(2, 1);
	}
	else {
		gpio_set_value(2, 0);
	}

	if (value & (1 << 1)) {//0b0000 0000 0000 0000 0000 0000 0000 0010
		gpio_set_value(3, 1);
	}
	else {
		gpio_set_value(3, 0);
	}

	if (value & (1 << 2)) {//0b0000 0000 0000 0000 0000 0000 0000 0100
		gpio_set_value(4, 1);
	}
	else {
		gpio_set_value(4, 0);
	}

	if (value & (1 << 3)) {
		gpio_set_value(17, 1);
	}
	else {
		gpio_set_value(17, 0);
	}

	if (value & (1 << 4)) {
		gpio_set_value(21, 1);
	}
	else {
		gpio_set_value(21, 0);
	}

	if (value & (1 << 5)) {
		gpio_set_value(20, 1);
	}
	else {
		gpio_set_value(20, 0);
	}

	if (value & (1 << 6)) {
		gpio_set_value(16, 1);
	}
	else {
		gpio_set_value(16, 0);
	}

	if (value & (1 << 7)) {
		gpio_set_value(12, 1);
	}
	else {
		gpio_set_value(12, 0);
	}

	if (value & (1 << 8)) {
		gpio_set_value(7, 1);
	}
	else {
		gpio_set_value(7, 0);
	}

	if (value & (1 << 9)) {
		gpio_set_value(8, 1);
	}
	else {
		gpio_set_value(8, 0);
	}

	if (value & (1 << 10)) {
		gpio_set_value(25, 1);
	}
	else {
		gpio_set_value(25, 0);
	}

	if (value & (1 << 11)) {
		gpio_set_value(24, 1);
	}
	else {
		gpio_set_value(24, 0);
	}

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

	delta = to_copy - not_copied;//�ʱ�ȭ?
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

	/* Set GPIO 2 segments GPIO*/
	/* GPIO 2 init */
	if (gpio_request(2, "rpi-gpio-2")) {
		printk("Can not allocate GPIO 2\n");
		goto AddError;
	}
	/* Set GPIO 2 direction*/
	if (gpio_direction_output(2, 0)) {
		printk("Can not set GPI0 2 to output!\n");
		goto Gpio2Error;
	}

	/* GPIO 3 init */
	if (gpio_request(3, "rpi-gpio-3")) {
		printk("Can not allocate GPIO 3\n");
		goto AddError;
	}
	/* Set GPIO 3 direction*/
	if (gpio_direction_output(3, 0)) {
		printk("Can not set GPI0 3 to output!\n");
		goto Gpio3Error;
	}

	/* GPIO 4 init */
	if (gpio_request(4, "rpi-gpio-4")) {
		printk("Can not allocate GPIO 4\n");
		goto AddError;
	}
	/* Set GPIO 4 direction*/
	if (gpio_direction_output(4, 0)) {
		printk("Can not set GPI0 4 to output!\n");
		goto Gpio4Error;
	}

	/* GPIO 17 init */
	if (gpio_request(17, "rpi-gpio-17")) {
		printk("Can not allocate GPIO 17\n");
		goto AddError;
	}
	/* Set GPIO 17 direction*/
	if (gpio_direction_output(17, 0)) {
		printk("Can not set GPI0 17 to output!\n");
		goto Gpio17Error;
	}

	/* GPIO 21 init */
	if (gpio_request(21, "rpi-gpio-21")) {
		printk("Can not allocate GPIO21 \n");
		goto AddError;
	}
	/* Set GPIO 21 direction*/
	if (gpio_direction_output(21, 0)) {
		printk("Can not set GPI0 21 to output!\n");
		goto Gpio21Error;
	}

	/* GPIO 20 init */
	if (gpio_request(20, "rpi-gpio-20")) {
		printk("Can not allocate GPIO20 \n");
		goto AddError;
	}
	/* Set GPIO 20 direction*/
	if (gpio_direction_output(20, 0)) {
		printk("Can not set GPI0 20 to output!\n");
		goto Gpio20Error;
	}

	/* GPIO 16 init */
	if (gpio_request(16, "rpi-gpio-16")) {
		printk("Can not allocate GPIO 16\n");
		goto AddError;
	}
	/* Set GPIO 16 direction*/
	if (gpio_direction_output(16, 0)) {
		printk("Can not set GPI0 16 to output!\n");
		goto Gpio16Error;
	}

	/* GPIO 12 init */
	if (gpio_request(12, "rpi-gpio-12")) {
		printk("Can not allocate GPIO 12\n");
		goto AddError;
	}
	/* Set GPIO 12 direction*/
	if (gpio_direction_output(12, 0)) {
		printk("Can not set GPI0 12 to output!\n");
		goto Gpio12Error;
	}

	/* GPIO 7 init */
	if (gpio_request(7, "rpi-gpio-7")) {
		printk("Can not allocate GPIO7 \n");
		goto AddError;
	}
	/* Set GPIO 7 direction*/
	if (gpio_direction_output(7, 0)) {
		printk("Can not set GPI0 7 to output!\n");
		goto Gpio7Error;
	}

	/* GPIO 8 init */
	if (gpio_request(8, "rpi-gpio-8")) {
		printk("Can not allocate GPIO8 \n");
		goto AddError;
	}
	/* Set GPIO 8 direction*/
	if (gpio_direction_output(8, 0)) {
		printk("Can not set GPI0 8 to output!\n");
		goto Gpio8Error;
	}

	/* GPIO 25 init */
	if (gpio_request(25, "rpi-gpio-15")) {
		printk("Can not allocate GPIO 25\n");
		goto AddError;
	}
	/* Set GPIO 25 direction*/
	if (gpio_direction_output(25, 0)) {
		printk("Can not set GPI0 25 to output!\n");
		goto Gpio25Error;
	}

	/* GPIO 24 init */
	if (gpio_request(24, "rpi-gpio-24")) {
		printk("Can not allocate GPIO24 \n");
		goto AddError;
	}
	/* Set GPIO 24 direction*/
	if (gpio_direction_output(24, 0)) {
		printk("Can not set GPI0  to output!\n");
		goto Gpio24Error;
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

Gpio2Error:
	gpio_free(2);

Gpio3Error:
	gpio_free(3);

Gpio4Error:
	gpio_free(4);

Gpio17Error:
	gpio_free(17);

Gpio21Error:
	gpio_free(21);

Gpio20Error:
	gpio_free(20);

Gpio16Error:
	gpio_free(16);

Gpio12Error:
	gpio_free(12);

Gpio7Error:
	gpio_free(7);

Gpio8Error:
	gpio_free(8);

Gpio25Error:
	gpio_free(25);

Gpio24Error:
	gpio_free(24);

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
	gpio_set_value(2, 0);
	gpio_set_value(3, 0);
	gpio_set_value(4, 0);
	gpio_set_value(17, 0);
	gpio_set_value(21, 0);
	gpio_set_value(20, 0);
	gpio_set_value(16, 0);
	gpio_set_value(12, 0);
	gpio_set_value(7, 0);
	gpio_set_value(8, 0);
	gpio_set_value(25, 0);
	gpio_set_value(24, 0);
	gpio_set_value(19, 0);//add
	gpio_set_value(26, 0);//add
	gpio_free(2);
	gpio_free(3);
	gpio_free(4);
	gpio_free(17);
	gpio_free(21);
	gpio_free(20);
	gpio_free(16);
	gpio_free(12);
	gpio_free(7);
	gpio_free(8);
	gpio_free(25);
	gpio_free(24);
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

