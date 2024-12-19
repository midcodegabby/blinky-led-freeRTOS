# note for compilation: can call a specific function defined here by using
# [make func_name] --> e.g., make clean
CC=arm-none-eabi-gcc
MACH=cortex-m4
CFLAGS=-c -mcpu=$(MACH) -mthumb --std=gnu11 -Wall -o0 -g3
LDFLAGS=-nostdlib -T stm32_ls.ld -Wl,-Map=final.map #-Wl specifies a linker input

all: main.o stm32_startup.o final.elf

main.o:main.c
	$(CC) $(CFLAGS) -o $@ $^

stm32_startup.o:stm32_startup.c
	$(CC) $(CFLAGS) -o $@ $^

final.elf: main.o stm32_startup.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -rf *.o *.elf *.map

load:
	openocd -f interface/stlink.cfg -c "transport select hla_swd" -f target/stm32l4x.cfg
	# openocd -f interface/stlink.cfg -c "reset_config none" -f target/stm32l4x.cfg
	# openocd -f interface/jlink.cfg -c "transport select swd" -f target/stm32l4x.cfg 

client:
	arm-none-eabi-gdb

# -Wall: show all warnings
#  clean: function description deletes all .o and .elf files
#  -c: do not link the files
#  -o: create object files
#

