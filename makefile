PROJDIRS := boot kernel libc drivers
SRCFILES := $(shell find $(PROJDIRS) -type f -name "*.c")
HDRFILES := $(shell find $(PROJDIRS) -type f -name "*.h")
OBJFILES := $(patsubst %.c,%.o,$(SRCFILES)) 
DEPFILES    := $(patsubst %.c,%.d,$(SRCFILES))
.PHONY: all clean iso run
WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
            -Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
            -Wconversion -Wstrict-prototypes -Wno-int-conversion
CFLAGS := -mgeneral-regs-only -mno-red-zone -g -nostdlib -nostdinc -std=gnu99 -ffreestanding $(WARNINGS)
CC :=  /usr/local/i386elfgcc/bin/i386-elf-gcc
all: run
run: iso
	qemu-system-i386 -cdrom myos.iso
debug: iso 
	qemu-system-i386 -s -cdrom myos.iso -d guest_errors,int &
	gdb -ex "target remote localhost:1234" -ex "symbol-file kernel.kernel"
iso: kernel
	mkdir -p isodir
	mkdir -p isodir/boot
	mkdir -p isodir/boot/grub
	cp kernel.kernel isodir/boot/os
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso isodir
kernel: ${OBJFILES} linker.ld boot/boot.o kernel/kernel.o drivers/cpu/interrupts/interrupt.o
	$(CC) ${CFLAGS} -T linker.ld -o kernel.kernel boot/boot.o ${OBJFILES} drivers/cpu/interrupts/interrupt.o
	grub-file --is-x86-multiboot2 kernel.kernel
clean:
	rm -rf isodir
	rm -f kernel.kernel
	rm -f myos.iso
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS)

.S.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS)
drivers/cpu/interrupts/interrupt.o: drivers/cpu/interrupts/interrupt.S
	nasm $< -f elf -o $@