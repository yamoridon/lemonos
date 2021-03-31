all: kernel.elf

clean:
	rm -f kernel.elf main.o

kernel.elf: main.o
	ld.lld -L$(HOME)/osbook/devenv/x86_64-elf/lib --entry KernelMain -z norelro --image-base 0x100000 --static -o $@ $<

main.o: main.cpp
	clang++ -I$(HOME)/osbook/devenv/x86_64-elf/include/c++/v1 -I$(HOME)/osbook/devenv/x86_64-elf/include -I$(HOME)/osbook/devenv/x86_64-elf/include/freetype2 -nostdlibinc -D__ELF__ -D_LDBL_EQ_DBL -D_GNU_SOURCE -D_POSIX_TIMERS -O2 -Wall -g --target=x86_64-elf -ffreestanding -mno-red-zone -fno-exceptions -fno-rtti -std=c++17 -o $@ -c $<
