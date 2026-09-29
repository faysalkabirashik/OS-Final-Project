# This is the standard makefile for building an external kernel module.

# 'obj-m' specifies the object files to be built as loadable kernel modules.
# The '.o' is replaced with '.ko' (kernel object) after compilation.
obj-m += sample.o

# 'all' is the default target. When you run 'make', this is what gets executed.
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

# 'clean' is a target to remove all compiled files.
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean