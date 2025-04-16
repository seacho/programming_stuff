# 编译内核模块
obj-m += speedhack.o
all:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
