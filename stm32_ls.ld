ENTRY(Reset_Handler)

/*define the stack end/bottom, which is just the end of SRAM1*/
_estack = 0x20018000;

/*define min size for the heap and the stack*/
_Min_Heap_Size = 0x400;
_Min_Stack_Size = 0x200;

MEMORY
{
	FLASH (rx):ORIGIN = 0x08000000, LENGTH = 1024K
	SRAM1 (rwx):ORIGIN = 0x20000000, LENGTH = 96K
	SRAM2 (rwx):ORIGIN = 0x10000000, LENGTH = 32K
}

SECTIONS
{
	/*The following sections are created in the following order*/
	/*put the vector table at the start of the flash, right here*/
	.isr_vector :
	{
		. = ALIGN(4);
		KEEP(*(.isr_vector))
		. = ALIGN(4);
	} > FLASH


	/*This section should include .text section (which is the main program code) of all input files*/
	.text : 
	{
		/*The * char says to merge .text section of all input files*/
		. = ALIGN(4);
		*(.text)
		*(.text*)
		. = ALIGN(4);
		_etext = .; /*Store the updated location counter value in to a symbol called _etext, note that
			     the location counter only tracks the VMA, not the LMA!!!*/

	}> FLASH 
	/*This part shows where to put the section in memory*/
	/* syntax: > vma AT> lma, for this case no need for second part due to vma = lma
	/* vma = virtual memory address, lma = load memory address*/
	
	/*This section contains read-only data*/
	.rodata : 
	{
		. = ALIGN(4);
		*(.rodata)
		*(.rodata*)
		. = ALIGN(4);
	}> FLASH

	/*This section should include .data (read/write data) section of all input files*/
	.data : 
	{
		. = ALIGN(4);
		_sdata = .; /*start of data section*/
		*(.data)
		*(.data*)
		_edata = .; /*end of data section*/
		. = ALIGN(4);

	/*}> SRAM1 AT> FLASH*/
	}> SRAM1 
	/* this section is loaded into the flash right after the .text section, but it is within the SRAM*/

	/*This section should include .bss section of all input files*/
	.bss : 
	{
		. = ALIGN(4);
		_sbss = .;
		*(.bss)
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		_ebss = .;
	
	}> SRAM1

	.dynamic_allocations : 
	{
		. = ALIGN(4);
		_ssystem_ram = .;
		. = . + _Min_Stack_Size;
		. = ALIGN(4);
		_esystem_ram = .;
	}> SRAM1

}
