# blinky_led_freeRTOS
### Basic LED blinky project using FreeRTOS on STM32L476 MCUs.  
- 2 tasks with equal priority toggle an LED on and off.   
- No CMSIS used for in-depth learning about FreeRTOS use with Cortex-M MCUs.   
    
### Features:  
- HardFault debugging handler
- Timer2 blocking and non-blocking delays
- Easy to adapt and configure for a new project with more source and header files!
    
### Usage Guide (requires OpenOCD and Arm-GNU toolchain):
#### Build as-is:
```
make
make install
```
    
#### Use HardFault debugging to find cause of the Hard Fault:
1. Create memory debug files
```
make symbols
make dump
```
-> this creates two files in the folder memory_debug:   
- disassembly.txt - contains raw memory and instructions of the application  
- symbols.txt - contains the symbol table of the application  
   
2. Check where the program counter (pc) was at when the Hard Fault occurred:  
- search for `pc` in symbols.txt: this will give you the memory address of pc, which we will call `pc_address`   
    
3. Run a gdb server/client to check what address `pc` holds during the Hard Fault:   
- run the load and client commands in separate terminals:    
```
make load
make client
    target remote localhost:3333
    monitor reset init
    monitor flash write_image erase final.elf
    monitor reset halt
    monitor resume
    monitor mdw 0xpc_address 1
```
-> this will return the address that `pc` contained when the Hard Fault occurred, which we will call `hardfault_address`.  
   
4. Find the hardfault_address in disassembly.txt by searching for the 6 nibbles in the middle of `hardfault_address`  
- i.e., if `hardfault_address` = 08001049, then you would search for 800104 in disassembly.txt.   
   
5. This much information should allow you to figure out the root cause of the Hard Fault.   
- i.e., if you have a misaligned address (like the example above), then you can find which function/IRQ_Handler caused that issue and go from there.  
    

