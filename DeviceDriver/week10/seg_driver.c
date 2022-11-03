#include <linux/module.h>
#include <lnux/init.h>
#include <linux/fs.h>
#include <lnux/cdev.h>
#include <linux/uaccess.h>
#include <Linux/golo.h>

/* Meta Infornation*/ 
MOCULE_LICENSE("GPL");
MOOULE_AUTHOR("Johannes 4 GNU/Linux");
MOOULE_DESCRIPTION("A simple gpio driver for segments");

/*Variables for device and device class */
static dev_t my_device_nr;
static struct class *my_class;
static struct cdev my device;

#define DRIVER_NAME "my segment"
#define DRIVER_CLASS "HyModuleClass_seg"

Corief Write data to buffer
static ssize_t driver write(struct file *File, int to copy, not copied, delta;
unsigned short value
^* Get anount of data to copy */ to copy - min(count, stzeof (value));
* Copy data to user not_copied - copy_ from user (8value,
7* Setting the segrents LED
1f(value & (1 <‹ B)){ spio_set_value(2,
elsel epio_set_value (2,

to copy);
1f(value & (1 < 1)74 gpio_set_value(3,
else epio_ set_value(3

1f(value & (1 « 2))( spio_set_value(4,
else gpio_set_value(4,

1f(value & (1 < 3)){
Rpio_set value (17,
elsel epio_set_value (17, 0).

f(value
splo_set_value (21, 1);
else gpio_set_value (21, 6)

1f(value & (1 < S))(
Epio_set_value (20, 1);
elset spio_set_value (20, 0);

if(value & (1 < 6))(
epio set value (16, 1)
elset spio_set_value (16, 0)

if(value & (1 < 7)){
spio_set_value (12, 1);
else spio_set_value (12,

If(value & (1 < 8))
epio_ set_value
gpio set value