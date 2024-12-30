ENTRY(Reset_Handler)

/*define the stack end/bottom, which is just the end of SRAM1*/
_estack = 0x20018000;

/*define min size for the heap and the stack*/
_Min_Heap_Size = 0x400;
_Min_Stack_Size = 0x200;

MEMORY
{
	SRAM1 (rwx):ORIGIN = 0x20000000, LENGTH = 96K
	SRAM2 (rwx):ORIGIN = 0x10000000, LENGTH = 32K
	FLASH (rx):ORIGIN = 0x08000000, LENGTH = 1024K
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
		_etext = .; 
			     

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

	_la_data = LOADADDR(.data); /*load the address of data into this symbol*/

	/*This section should include .data (read/write data) section of all input files*/
	.data : 
	{
		. = ALIGN(4);
		_sdata = .; /*start of data section*/
		*(.data)
		*(.data*) /* this merges all seperate .text sections together!!!*/
		. = ALIGN(4);
		_edata = .; /*end of data section*/

	}> SRAM1 AT> FLASH
	/* this section is loaded into the flash right after the .text section, but it is within the SRAM*/

	/*This section should include .bss section of all input files*/
	.bss : 
	{
		. = ALIGN(4);
		_sbss = .;
		__bss_start__ = _sbss; /*used for newlib.nano*/
		*(.bss)
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		_ebss = .;
		__bss_end__ = _ebss;  /*used for newlib.nano*/
	
	}> SRAM1

	.dynamic_allocations : 
	{
		. = ALIGN(8);
		_ssystem_ram = .;
		PROVIDE(end = .); /*used for newlib nano*/
		PROVIDE(_end = .); /*used for newlib nano*/
		. = . + _Min_Heap_Size;
		. = . + _Min_Stack_Size;
		. = ALIGN(8);
		_esystem_ram = .;
	}> SRAM1

	/DISCARD/ :
	{
		libc.a (*)
		libm.a(*)
		libgcc.a(*)
	}
	.ARM.attributes 0 : { *(.ARM.attributes) }
}