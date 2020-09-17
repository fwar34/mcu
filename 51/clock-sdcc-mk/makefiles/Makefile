# CC 编译工具声明
# stc 烧录工具位置
# 功能是编译并完成下载
CC = sdcc
stc = sudo python /home/jikexianfeng/51-demo/.stcflash/stcflash.py

all : main.bin

download: main.bin
    $(stc) main.bin

#main.bin : main.hex
#    ~/51-demo/.Hex2bin-2.5/hex2bin main.hex

main.bin : main.hex
    objcopy -I ihex -O binary main.hex main.bin

main.hex : main.ihx
    packihx main.ihx > main.hex

main.ihx : main.rel delay.rel
    $(CC) main.rel delay.rel

main.rel : main.c delay.h
    $(CC) -c main.c

delay.rel : delay.c
    $(CC) -c delay.c

cleanall:
	rm -rf *.lk *.bin *.asm *.lst *.mem *.rst *.lnk *.rel *.sym *.ihx *.hex *.map
clean:
	rm -rf *.asm *.lst *.mem *.rst *.lnk *.rel *.sym *.ihx *.hex *.map
