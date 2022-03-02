# Kernel lib
KVERS :=$(shell uname -r)

# Path
PWD :=$(shell pwd)

# Build modules
obj-m += mydev_drive.o

build:
	make -C /lib/modules/$(KVERS)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(KVERS)/build M=$(PWD) clean
