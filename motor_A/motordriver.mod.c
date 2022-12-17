#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x813e3d9c, "module_layout" },
	{ 0x454d6fba, "cdev_del" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0xe36d3323, "class_destroy" },
	{ 0x981b1a4d, "device_destroy" },
	{ 0xfe990052, "gpio_free" },
	{ 0x47229b5c, "gpio_request" },
	{ 0xbad589d0, "cdev_add" },
	{ 0x5b7f122a, "cdev_init" },
	{ 0xbff39870, "device_create" },
	{ 0x34e45255, "__class_create" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x8da6585d, "__stack_chk_fail" },
	{ 0xdcb764ad, "memset" },
	{ 0x12a4e128, "__arch_copy_from_user" },
	{ 0xa1a89fc3, "gpiod_direction_output_raw" },
	{ 0x2c84a8c2, "gpiod_set_raw_value" },
	{ 0xc9cb0d2e, "gpio_to_desc" },
	{ 0x92997ed8, "_printk" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "1C6F1C80660834EE7FE3A32");
