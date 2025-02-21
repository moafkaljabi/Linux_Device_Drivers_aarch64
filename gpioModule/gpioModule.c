#include <linux/module.h>
#include <linux/kernel.h>

static int __init gpio_module_init(void){
	pr_info("GPIO Module loaded!\n");
	return 0;
}

static void __exit gpio_module_exit(void){
	pr_info("GPIO Module unloaded\n");
	
}

module_init(gpio_module_init);
module_exit(gpio_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Moafk Aljabi");
MODULE_DESCRIPTION("Starter GPIO kernel module");
