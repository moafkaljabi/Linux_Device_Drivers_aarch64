#include <linux/module.h>
#include <linux/init.h>

static int __init my_init (void) {
	
	printk("Hello Kernel!\n");

	return 0;
}

static void __exit my_exit(void) { 
	
	printk("Goodbey Kernel\n");
}


module_init(my_init);
module_exit(my_exit);

// Metadata

MODULE_LICENSE("GPT");
MODULE_AUTHOR("Moafk AstraSpecs");
MODULE_DESCRIPTION("Linux Kernel Mod:ule.");
