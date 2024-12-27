# Author: Gabriel Rodgers
# Date: 12/26/2024
# Purpose: Simplify build process for freeRTOS project.

-include makefile.rule

CC = arm-none-eabi-gcc
MACH = cortex-m4
MCU = -mcpu=$(MACH) -mfloat-abi=hard -mfpu=auto
CFLAGS = $(MCU) -mthumb $(INCLUDES) --std=c11 -Wall -Wextra -o2 -g3
LDFLAGS = $(MCU) -mthumb --specs=nano.specs -T $(LINKER) -Wl,-Map=final.map

VPATH = $(dir $(SOURCES))

OBJ = $(patsubst %.c, %.o, $(notdir $(SOURCES))) 


all: final.elf

main.o: main.c
	$(CC) -c $(CFLAGS) -o $@ $<

syscalls.o: syscalls.c
	$(CC) -c $(CFLAGS) -o $@ $<

sysmem.o: sysmem.c
	$(CC) -c $(CFLAGS) -o $@ $<

stm32_startup.o: stm32_startup.c 
	$(CC) -c $(CFLAGS) -o $@ $<

final.elf: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^


.PHONY: clean load client
clean:
	rm -rf *.o *.elf *.map

load:
	openocd -f interface/stlink.cfg -c "transport select hla_swd" -f target/stm32l4x.cfg
	# openocd -f interface/stlink.cfg -c "reset_config none" -f target/stm32l4x.cfg
	# openocd -f interface/jlink.cfg -c "transport select swd" -f target/stm32l4x.cfg 

client:
	arm-none-eabi-gdb


# optimizations: oz-min size; os-size/speed; o3-max speed; o2-med speed, less size than o3
# For Bare-Metal applications: use --specs=nosys.specs to disable syscalls.
