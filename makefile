# Author: Gabriel Rodgers
# Date: 12/26/2024
# Purpose: compile and link all files.

-include makefile.assignments

CC := arm-none-eabi-gcc
MACH := cortex-m4
MCU := -mcpu=$(MACH) -mfloat-abi=hard -mfpu=auto
CFLAGS := $(MCU) -mthumb $(INCLUDES) --std=c11 -Wall -Wextra -o2 -g3
LDFLAGS := $(MCU) -mthumb --specs=nano.specs -T $(LINKER) -lc -lm -Wl,-Map=final.map

VPATH := $(dir $(SOURCES))
OBJ := $(patsubst %.c, %.o, $(notdir $(SOURCES))) 

all: final.elf

# compilation
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

# linking
final.elf: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

.PHONY: clean install load client
clean:
	rm -rf *.o *.elf *.map memory_debug/*.txt

install:
	openocd -f interface/stlink.cfg -c "transport select hla_swd" -f target/stm32l4x.cfg -c \
	"program final.elf verify reset exit"	

# GDB server
load:
	openocd -f interface/stlink.cfg -c "transport select hla_swd" -f target/stm32l4x.cfg
	# openocd -f interface/stlink.cfg -c "reset_config none" -f target/stm32l4x.cfg
	# openocd -f interface/jlink.cfg -c "transport select swd" -f target/stm32l4x.cfg 

# GDB client
client:
	arm-none-eabi-gdb

# objump
dump:
	arm-none-eabi-objdump -D final.elf > memory_debug/disassembly.txt

# symbol table
symbols:
	nm final.elf > memory_debug/symbols.txt

# optimizations: oz-min size; os-size/speed; o3-max speed; o2-med speed, less size than o3
# For Bare-Metal applications: use --specs=nosys.specs to disable syscalls.
# VPATH - search paths for make.
# -I(folder) - search paths for header files.
