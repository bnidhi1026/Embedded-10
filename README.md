# Hello Driver - Linux Kernel Module

This project contains a simple Linux kernel module named `hello_driver`.

## Files

- **hello_driver.c**: The source code for the kernel module.
- **Makefile**: Used to compile and clean the kernel module.

## Build Instructions

### To build the kernel module, run:
make

### To clean the build artifacts, run:
make clean

### Load and Remove the Module

#### After building, you can insert the module into the kernel using:
sudo insmod hello_driver.ko

### To verify that the module is loaded:
lsmod | grep hello_driver

### To check kernel messages related to the module:
dmesg | tail

### To remove the module from the kernel:
sudo rmmod hello_driver

### Verify it has been removed:
lsmod | grep hello_driver

### Load and Remove the Module
#### Insert the Module
sudo insmod hello_driver.ko

#### Check if the module is loaded:
lsmod | grep hello_driver

### View kernel log messages:
dmesg | tail

Example dmesg output:
[ 1234.567890] Hello Driver: Module loaded into the kernel

### Remove the Module
sudo rmmod hello_driver

### Check that it's been removed:
lsmod | grep hello_driver

### View the logs again:
dmesg | tail

Example dmesg output:
[ 1235.678901] Hello Driver: Module removed from the kernel

## Makefile Overview
### makefile

obj-m += hello_driver.o
KDIR := /lib/modules/$(shell uname -r)/build

all:
	make -C $(KDIR) M=$(shell pwd) modules

clean:
	make -C $(KDIR) M=$(shell pwd) clean


#### For Debian/Ubuntu:
sudo apt install linux-headers-$(uname -r)

#### For Fedora:
sudo dnf install kernel-devel

Module not found after make: Ensure there are no typos in the Makefile and that you’re in the correct directory.

⚠️ Note: Kernel modules can cause system instability if written incorrectly. Only test on non-critical systems or virtual machines.

