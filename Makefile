# note for compilation: can call a specific function defined here by using
# [make func_name] --> e.g., make clean

-include Makefile.assignments

AS := arm-none-eabi-as
CC := arm-none-eabi-gcc
MACH := cortex-m7
MCU := -mcpu=$(MACH) -mfloat-abi=hard -mfpu=fpv5-d16
AFLAGS=-mcpu=$(MACH) -mthumb 
CFLAGS := $(MCU) -mthumb $(INCLUDES) --std=gnu11 -Wall -Wextra -Wpedantic -O1 -g3
LDFLAGS := $(MCU) -mthumb --specs=nano.specs -T $(LINKER) -lc -lm -Wl,-Map=final.map
#LDFLAGS := -nostdlib -T $(LINKER) -Wl,-Map=final.map 

VPATH := $(dir $(SOURCES))
OBJ := $(patsubst %.c, %.o, $(notdir $(SOURCES)))

all: final.elf

# compilation
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

startup.o: $(STARTUP_FILE)
	$(AS) -c $(AFLAGS) -o $@ $^

# linking
final.elf: $(OBJ) startup.o
	$(CC) $(LDFLAGS) -o $@ $^

.PHONY: clean load client flash

clean:
	rm -rf *.o *.elf *.map memory_debug/*.txt

load:
	openocd -f interface/stlink.cfg -c "transport select dapdirect_swd" -f target/stm32h7x.cfg 

client:
	arm-none-eabi-gdb

flash:
	openocd -f interface/stlink.cfg -c "transport select dapdirect_swd" -f target/stm32h7x.cfg -c "program final.elf verify reset exit"

# -Wall: show all warnings
#  clean: function description deletes all .o and .elf files
#  -c: do not link the files
#  -o: create object files
#

