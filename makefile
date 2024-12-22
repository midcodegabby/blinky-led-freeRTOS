# note for compilation: can call a specific function defined here by using
# [make func_name] --> e.g., make clean
CC=arm-none-eabi-gcc
MACH=cortex-m4
CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=hard -mfpu=auto --std=c11 -Wall -Wextra -o2 -g3
LDFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=hard -mfpu=auto --specs=nano.specs -T stm32_ls.ld -Wl,-Map=final.map
LDFLAGS_SH= -mcpu=$(MACH) -mthumb -mfloat-abi=hard -mfpu=auto --specs=rdimon.specs -T stm32_ls.ld -Wl,-Map=final.map

# optimizations: oz-min size; os-size/speed; o3-max speed; o2-med speed, less size than o3

all: main.o stm32_startup.o final.elf

main.o:main.c
	$(CC) $(CFLAGS) -o $@ $^

stm32_startup.o:stm32_startup.c
	$(CC) $(CFLAGS) -o $@ $^

final.elf: main.o stm32_startup.o
	$(CC) $(LDFLAGS) -o $@ $^

final_sh.elf: main.o stm32_startup.o
	$(CC) $(LDFLAGS_SH) -o $@ $^

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

