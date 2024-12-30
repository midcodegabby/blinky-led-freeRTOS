/*
Author: Gabriel Rodgers
Date: 12/30/2024
Purpose: startup file for STM32L476RG MCU (with hardfault debugging)
*/

//headers and macros
#include <stdint.h>

#define SRAM_START 0x20000000U
#define SRAM_SIZE (96U*1024U) //96 KB, SRAM1 = 96 KB, SRAM2 = 32 KB (should be 128 KB)
#define SRAM_END (SRAM_START + SRAM_SIZE)

#define STACK_START SRAM_END
#define CPACR (*((volatile uint32_t *) (0xE000ED88))) //for enabling the FPU!

//use extern uint32_t to access symbols from linker script!
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _la_data;

extern uint32_t _estack; 

extern uint32_t _sbss;
extern uint32_t _ebss;

//main() prototype
int main(void); 

//stdlib initialization function prototype
void __libc_init_array(void);

//isr declarations; weak allows later mods of NMI_handler function in .c source file
void Reset_Handler(void);
void NMI_Handler 			(void) __attribute__ ((weak, alias("Default_Handler"))); 
void HardFault_Handler(void);
void MemManage_Handler 			(void) __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler 			(void) __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler 		(void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler 			(void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler 			(void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler   			(void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler  			(void) __attribute__ ((weak, alias("Default_Handler")));
void WWDG_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));
void PVD_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));             
void TAMP_STAMP_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));      
void RTC_WKUP_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));                               
void FLASH_IRQHandler			(void) __attribute__ ((weak, alias("Default_Handler")));                               
void RCC_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));             
void EXTI0_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));           
void EXTI1_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));           
void EXTI2_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));           
void EXTI3_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));           
void EXTI4_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));           
void DMA1_Stream1_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Stream2_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Stream3_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Stream4_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Stream5_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Stream6_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Stream7_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void ADC1_2_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));             
void CAN1_TX_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));         
void CAN1_RX0_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));        
void CAN1_RX1_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));        
void CAN1_SCE_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));        
void EXTI9_5_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));         
void TIM1_BRK_TIM15_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));   
void TIM1_UP_TIM16_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));   
void TIM1_TRG_COM_TIM17_IRQHandler 	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));         
void TIM2_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));            
void TIM3_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));            
void TIM4_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));            
void I2C1_EV_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));         
void I2C1_ER_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));         
void I2C2_EV_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));         
void I2C2_ER_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));         
void SPI1_IRQHandler  			(void) __attribute__ ((weak, alias("Default_Handler")));           
void SPI2_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));            
void USART1_IRQHandler  		(void) __attribute__ ((weak, alias("Default_Handler")));         
void USART2_IRQHandler  		(void) __attribute__ ((weak, alias("Default_Handler")));        
void USART3_IRQHandler   		(void) __attribute__ ((weak, alias("Default_Handler")));        
void EXTI15_10_IRQHandler   		(void) __attribute__ ((weak, alias("Default_Handler")));     
void RTC_Alarm_IRQHandler    		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DFSDM1_FLT3_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler"))); 
void TIM8_BRK_IRQHandler   		(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_UP_IRQHandler    		(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_TRG_COM_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM8_CC_IRQHandler          	(void) __attribute__ ((weak, alias("Default_Handler")));
void ADC3_IRQHandler     		(void) __attribute__ ((weak, alias("Default_Handler")));
void FMC_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void SDMMC1_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM5_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void SPI3_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void UART4_IRQHandler            	(void) __attribute__ ((weak, alias("Default_Handler")));
void UART5_IRQHandler            	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM6_DACUNDER_IRQHandler         	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM7_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream0_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream1_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream2_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream3_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream4_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DFSDM1_FLT0_IRQHandler		(void) __attribute__ ((weak, alias("Default_Handler")));
void DFSDM1_FLT1_IRQHandler		(void) __attribute__ ((weak, alias("Default_Handler")));
void DFSDM1_FLT2_IRQHandler		(void) __attribute__ ((weak, alias("Default_Handler")));
void COMP_IRQHandler			(void) __attribute__ ((weak, alias("Default_Handler")));
void LPTIM1_IRQHandler			(void) __attribute__ ((weak, alias("Default_Handler")));
void LPTIM2_IRQHandler			(void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_FS_IRQHandler			(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream5_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream6_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void LPUART1_IRQHandler			(void) __attribute__ ((weak, alias("Default_Handler")));
void QUADSPI_IRQHandler			(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C3_EV_IRQHandler			(void) __attribute__ ((weak, alias("Default_Handler")));
void SAI1_IRQHandler			(void) __attribute__ ((weak, alias("Default_Handler")));
void SAI2_IRQHandler			(void) __attribute__ ((weak, alias("Default_Handler")));
void SWPMI1_IRQHandler			(void) __attribute__ ((weak, alias("Default_Handler")));
void TSC_IRQHandler			(void) __attribute__ ((weak, alias("Default_Handler")));
void LCD_IRQHandler			(void) __attribute__ ((weak, alias("Default_Handler")));
void RNG_IRQHandler              	(void) __attribute__ ((weak, alias("Default_Handler")));                          
void FPU_IRQHandler              	(void) __attribute__ ((weak, alias("Default_Handler")));                          

//vector table: starts at 0x0000 0000, ends at 0x0000 01A8
//0x0000 0000 - 0x0000 003C: system level exception handlers
//0x0000 0040 - 0x0000 01A8: interrupts (91 total)
//initialize the vector table; the __attribute__ stuff places the vector table
//in a new section called .isr_vector
uint32_t vectors[] __attribute__((section(".isr_vector"))) = {
	STACK_START,
	(uint32_t) Reset_Handler,  //must typecast this
	(uint32_t) NMI_Handler, //address of default_handler is stored here
	(uint32_t) HardFault_Handler, 		
	(uint32_t) MemManage_Handler, 		
	(uint32_t) BusFault_Handler, 		
	(uint32_t) UsageFault_Handler, 	
	0,
	0, 
	0,
	0,
	(uint32_t) SVC_Handler,		
	(uint32_t) DebugMon_Handler,
	0,	
	(uint32_t) PendSV_Handler,   		
	(uint32_t) SysTick_Handler,
	(uint32_t) WWDG_IRQHandler,
	(uint32_t) PVD_IRQHandler,
	(uint32_t) TAMP_STAMP_IRQHandler,
	(uint32_t) RTC_WKUP_IRQHandler,
	(uint32_t) FLASH_IRQHandler,
	(uint32_t) RCC_IRQHandler,
	(uint32_t) EXTI0_IRQHandler,
	(uint32_t) EXTI1_IRQHandler,
	(uint32_t) EXTI2_IRQHandler,
	(uint32_t) EXTI3_IRQHandler,
	(uint32_t) EXTI4_IRQHandler,
	(uint32_t) DMA1_Stream1_IRQHandler,
	(uint32_t) DMA1_Stream2_IRQHandler,
	(uint32_t) DMA1_Stream3_IRQHandler,
	(uint32_t) DMA1_Stream4_IRQHandler,
	(uint32_t) DMA1_Stream5_IRQHandler,
	(uint32_t) DMA1_Stream6_IRQHandler,
	(uint32_t) DMA1_Stream7_IRQHandler,
	(uint32_t) ADC1_2_IRQHandler,
	(uint32_t) CAN1_TX_IRQHandler,
	(uint32_t) CAN1_RX0_IRQHandler,
	(uint32_t) CAN1_RX1_IRQHandler,
	(uint32_t) CAN1_SCE_IRQHandler,
	(uint32_t) EXTI9_5_IRQHandler,
	(uint32_t) TIM1_BRK_TIM15_IRQHandler,
	(uint32_t) TIM1_UP_TIM16_IRQHandler,
	(uint32_t) TIM1_TRG_COM_TIM17_IRQHandler,
	(uint32_t) TIM1_CC_IRQHandler,
	(uint32_t) TIM2_IRQHandler,
	(uint32_t) TIM3_IRQHandler,
	(uint32_t) TIM4_IRQHandler,
	(uint32_t) I2C1_EV_IRQHandler,
	(uint32_t) I2C1_ER_IRQHandler,
	(uint32_t) I2C2_EV_IRQHandler,
	(uint32_t) I2C2_ER_IRQHandler,
	(uint32_t) SPI1_IRQHandler,
	(uint32_t) SPI2_IRQHandler,
	(uint32_t) USART1_IRQHandler,
	(uint32_t) USART2_IRQHandler,
	(uint32_t) USART3_IRQHandler,
	(uint32_t) EXTI15_10_IRQHandler,
	(uint32_t) RTC_Alarm_IRQHandler,
	(uint32_t) DFSDM1_FLT3_IRQHandler,
	(uint32_t) TIM8_BRK_IRQHandler,
	(uint32_t) TIM8_UP_IRQHandler,
	(uint32_t) TIM8_TRG_COM_IRQHandler,
	(uint32_t) TIM8_CC_IRQHandler,
	(uint32_t) ADC3_IRQHandler,
	(uint32_t) FMC_IRQHandler,
	(uint32_t) SDMMC1_IRQHandler,
	(uint32_t) TIM5_IRQHandler,
	(uint32_t) SPI3_IRQHandler,
	(uint32_t) UART4_IRQHandler,
	(uint32_t) UART5_IRQHandler,
	(uint32_t) TIM6_DACUNDER_IRQHandler,
	(uint32_t) TIM7_IRQHandler,
	(uint32_t) DMA2_Stream0_IRQHandler,
	(uint32_t) DMA2_Stream1_IRQHandler,
	(uint32_t) DMA2_Stream2_IRQHandler,
	(uint32_t) DMA2_Stream3_IRQHandler,
	(uint32_t) DMA2_Stream4_IRQHandler,
	(uint32_t) DFSDM1_FLT0_IRQHandler,
	(uint32_t) DFSDM1_FLT1_IRQHandler,
	(uint32_t) DFSDM1_FLT2_IRQHandler,
	(uint32_t) COMP_IRQHandler,
	(uint32_t) LPTIM1_IRQHandler,
	(uint32_t) LPTIM2_IRQHandler,
	(uint32_t) OTG_FS_IRQHandler,
	(uint32_t) DMA2_Stream5_IRQHandler,
	(uint32_t) DMA2_Stream6_IRQHandler,
	(uint32_t) LPUART1_IRQHandler,
	(uint32_t) QUADSPI_IRQHandler,
	(uint32_t) I2C3_EV_IRQHandler,
	(uint32_t) I2C3_EV_IRQHandler,
	(uint32_t) SAI1_IRQHandler,
	(uint32_t) SAI2_IRQHandler,
	(uint32_t) SWPMI1_IRQHandler,
	(uint32_t) TSC_IRQHandler,
	(uint32_t) LCD_IRQHandler,
	0,
	(uint32_t) RNG_IRQHandler,
	(uint32_t) FPU_IRQHandler,
	
}; //can also put __attribute__ stuff at the end of a definition/declaration

//dummy function
void Default_Handler(void){
	while(1);
}

//this handler debugs hardfaults by sending the registers (before hardfault) to a debug function in main.c
void HardFault_Handler(void) {
	 __asm volatile
    (
        " tst lr, #4                                                \n"
        " ite eq                                                    \n"
        " mrseq r0, msp                                             \n"
        " mrsne r0, psp                                             \n"
        " ldr r1, [r0, #24]                                         \n"
        " ldr r2, handler2_address_const                            \n"
        " bx r2                                                     \n"
        " handler2_address_const: .word prvGetRegistersFromStack    \n"
    );
}

//this initializes the .data and .bss section
void Reset_Handler(void){
	
	//initialize the stack pointer using inline asm
	__asm__ ("ldr sp, =_estack");

	//copy .data section to SRAM
	//first find the size of the .data section, must typecast addresses corresponding to the symbols
	uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
	
	//pDst is a pointer to the destination of the data section (in SRAM)
	uint8_t *pDst = (uint8_t*)&_sdata;
	
	//pSrc is a pointer to the source of the data section (in FLASH)
	//uint8_t *pSrc = (uint8_t*)&_edata; //this line causes globals to turn to nonsense.
	uint8_t *pSrc = (uint8_t*)&_la_data;

	for(uint32_t i=0; i < size; i++){
		*pDst++ = *pSrc++;
	}

	//initialize the .bss section to zero in SRAM; first find the size of the .bss section
	size = (uint32_t)&_ebss - (uint32_t)&_sbss;
	
	//reassign pDst to the address of the start of the .bss section
	pDst = (uint8_t*)&_sbss;
	
	for(uint32_t i=0; i < size; i++){
		*pDst++ = 0;
	}

	//enable FPU
    CPACR |= (0xF << 20);

    //call initialization function of stdlib 
    __libc_init_array();	

	//call main()
	main();
}