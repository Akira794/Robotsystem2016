obj-m:= blinkled.o

blink.ko: blinkled.c
	make -C /usr/src/linux M=`pwd` V=1 modules

clean:
	make -C /usr/src/linux M=`pwd` V=1 clean
