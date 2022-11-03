#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>

/* Meta Infornation*/ 
MOCULE_LICENSE("GPL");
MOOULE_AUTHOR("Johannes 4 GNU/Linux");
MOOULE_DESCRIPTION("A simple gpio driver for segments");

/*Variables for device and device class */
static dev_t my_device_nr;
static struct class *my_class;
static struct cdev my_device;

#define DRIVER_NAME "my_segment"
#define DRIVER_CLASS "HyModuleClass_seg"
/***
*brief Write data to buffer
*/
static ssize_t driver_write(struct file *File, const char *user_buffer,size_t count, loff_t *offs) {
    int to_copy, not_copied, delta;
    unsigned short value = 0;

    /* Get anount of data to copy */ 
    to_copy = min(count, sizeof (value));

    /* Copy data to user*/
    not_copied = copy_from_user (&value, user_buffer, to_copy);
    /* Setting the segrents LED */
    if(value & (1 <‹ 0)){ 
        gpio_set_value(2, 1);
    }
    else{
        gpio_set_value (2, 0);
    }

    if(value & (1 << 1)) {
        gpio_set_value(3, 1);
    }
    else {
        gpio_ set_value(3, 0);
    }

    if(value & (1 << 2)) {
        gpio_set_value(4, 1);
    }
    else {
        gpio_ set_value(4, 0);
    }

    if(value & (1 << 3)) {
        gpio_set_value(17, 1);
    }
    else {
        gpio_ set_value(17, 0);
    }

    if(value & (1 << 4)) {
        gpio_set_value(21, 1);
    }
    else {
        gpio_ set_value(21, 0);
    }

    if(value & (1 << 5)) {
        gpio_set_value(20, 1);
    }
    else {
        gpio_ set_value(20, 0);
    }

    if(value & (1 << 6)) {
        gpio_set_value(16, 1);
    }
    else {
        gpio_ set_value(16, 0);
    }

    if(value & (1 << 7)) {
        gpio_set_value(12, 1);
    }
    else {
        gpio_ set_value(12, 0);
    }

    if(value & (1 << 8)) {
        gpio_set_value(7, 1);
    }
    else {
        gpio_ set_value(7, 0);
    }

    if(value & (1 << 9)) {
        gpio_set_value(8, 1);
    }
    else {
        gpio_ set_value(8, 0);
    }

    if(value & (1 << 10)) {
        gpio_set_value(25, 1);
    }
    else {
        gpio_ set_value(25, 0);
    }

    if(value & (1 << 11)) {
        gpio_set_value(24, 1);
    }
    else {
        gpio_ set_value(24, 0);
    }

    delta = to_copy - not_copied;
    return delta;
}

/**
 * @brief This function is called, when the device file is opend
*/
static int driver_open(struct inode *device_file, struct file *instance){
    printk("segment - open was called!\n");
    return 0;
}

/**
 * @brief This function is called, when the device file is closed
*/
static int driver_close(struct inode *device_file, struct file *instance){
    printk("segment - close was called!\n");
    return 0;
}

static struct file_operation fops = {
    .owner = THIS_MODULE,
    .open = driver_open,
    .release = driver_close,
    //.read = driver_read,
    .write = driver_write 
};






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
AddError:
    device_destroy(my_class, my_device_nr);
FileError:
    class_destroy(my_class);
ClassError:
    unregister_chrdev_region(my_device_nr, 1);
    return -1;

    
