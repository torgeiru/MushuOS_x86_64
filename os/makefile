# Compiler and options
CC = gcc
AS = nasm
ld = ld
CFLAGS = -ffreestanding -O2 -Wall -Wextra -nostdlib -fno-pie -m32 -fno-stack-protector -Ttext 0x100000

# Output
MULTIBOOT = multiboot.o
KERNEL = kernel.o
MUSHUOS = MushuOS

# Source files
KERNEL_SRC = kernel.cpp
MULTIBOOT_SRC = multiboot.asm

# Targets
all: multiboot kernel
	ld -m elf_i386 -T linker.ld -o $(MUSHUOS) $(MULTIBOOT) $(KERNEL)

multiboot:
	nasm -f elf32 $(MULTIBOOT_SRC) -o $(MULTIBOOT)

kernel: $(KERNEL_SRC)
	$(CC) $(CFLAGS) -c $(KERNEL_SRC) -o $(KERNEL)

clean:
	rm -f $(MUSHUOS)
	rm -f $(MULTIBOOT)
	rm -f $(KERNEL_STRIPPED)
	rm -f *.o $(KERNEL)
	sync