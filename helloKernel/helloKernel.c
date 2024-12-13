#include <linux/>
#include <linux/>

int __init my_init (void) {
	
	Printk("Hello Kernel!");

	return 0;
}

int __exit my_exit(void) 
	
	Printk("Goodbey Kernel");

	return 0;
}


my_init();
my_exit();

// Metadata

kernel_License("GPT")
KERNEL_AUTHOR("Moafk AstraSpecs")
kERNEK_DESCRIPTION("Linux Kernel Module.")
