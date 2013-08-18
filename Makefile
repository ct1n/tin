CC=gcc
LD=ld
CFLAGS=-fno-pic -static -fno-builtin -nostdinc -I. -fno-strict-aliasing -Wall -MD -ggdb -m32 -Werror -fno-omit-frame-pointer -fno-stack-protector
ASFLAGS=-m32 -gdwarf-2 -Wa,-divide
LDFLAGS=-m elf_i386

all: tin.img

tin.img: bootblock kernel
	dd if=/dev/zero of=tin.img count=10000
	dd if=bootblock of=tin.img conv=notrunc
	dd if=kernel of=tin.img seek=1 conv=notrunc

mkboot: mkboot.c
	gcc -o mkboot mkboot.c

bootblock: bootasm.S mkboot
	$(CC) $(CFLAGS) -c bootasm.S
	$(CC) $(CFLAGS) -O -c bootmain.c
	$(LD) $(LDFLAGS) -N -e start -Ttext 0x7C00 -o bootblock.o bootasm.o bootmain.o
	objcopy -S -O binary -j .text bootblock.o bootblock
	./mkboot bootblock

kernel: entry.o main.o
	$(LD) -T kernel.ld -o kernel entry.o main.o

-include *.d

clean:
	rm -f *.o *.d bootblock mkboot kernel tin.img

qemu-gdb: kernel
	qemu -serial mon:stdio -S -gdb tcp::26000 tin.img
