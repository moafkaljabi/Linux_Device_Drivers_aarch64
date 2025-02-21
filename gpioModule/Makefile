# Define the kernel source path
KERNEL_SOURCE := /usr/src/linux-6.6.62

# Define the cross-compile toolchain and architecture
CROSS_COMPILE := aarch64-linux-gnu-
ARCH := arm64

# Define the module source directory
MODULE_SOURCE := gpioModule

# Include path to kernel headers
INCLUDE_PATH := $(KERNEL_SOURCE)/include

# CFLAGS for compiling the module (includes kernel headers)
CFLAGS += -I$(INCLUDE_PATH)

# Object file target
obj-m := gpioModule.o

# All target to build the module
all:
	make -C $(KERNEL_SOURCE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) M=$(KERNEL_SOURCE)/$(MODULE_SOURCE) modules

# Build the module
modules:
	make -C $(KERNEL_SOURCE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) M=$(KERNEL_SOURCE)/$(MODULE_SOURCE) modules

# Clean target to remove built files
clean:
	make -C $(KERNEL_SOURCE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) M=$(KERNEL_SOURCE)/$(MODULE_SOURCE) clean

# Additional target to create the Module.symvers if missing
modules_prepare:
	make -C $(KERNEL_SOURCE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) M=$(KERNEL_SOURCE)/$(MODULE_SOURCE) modules_prepare

# Check for missing Module.symvers and create if necessary
check-modules-symvers:
	if [ ! -f $(KERNEL_SOURCE)/Module.symvers ]; then make -C $(KERNEL_SOURCE) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) M=$(KERNEL_SOURCE)/$(MODULE_SOURCE) modules_prepare; fi

.PHONY: all clean modules_prepare check-modules-symvers modules

