# Author: Gabriel Rodgers
# Date: 12/26/2024
# Purpose: Simplify build process for freeRTOS project.

CC = arm-none-eabi-gcc
MACH = cortex-m4
MCU = -mcpu=$(MACH) -mfloat-abi=hard -mfpu=auto
CFLAGS = -mthumb $(MCU) --std=c11 -Wall -Wextra -o2 -g3
LDFLAGS = -mthumb $(MCU) --specs=nano.specs -T stm32_ls.ld -Wl,-Map=final.map
LDFLAGS_SH = -mthumb $(MCU) --specs=rdimon.specs -T stm32_ls.ld -Wl,-Map=final.map

OBJ = main.o syscalls.o sysmem.o stm32_startup.o
OBJ_SH = main.o stm32_startup.o

all: $(OBJ) final.elf

semi: $(OBJ_SH) final_sh.elf

main.o: main.c main.h
	$(CC) -c $(CFLAGS) -o $@ $<

syscalls.o: syscalls.c
	$(CC) -c $(CFLAGS) -o $@ $<

sysmem.o: sysmem.c
	$(CC) -c $(CFLAGS) -o $@ $<

stm32_startup.o: stm32_startup.c
	$(CC) -c $(CFLAGS) -o $@ $<

final.elf: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

final_sh.elf: $(OBJ_SH)
	$(CC) $(LDFLAGS_SH) -o $@ $^

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
