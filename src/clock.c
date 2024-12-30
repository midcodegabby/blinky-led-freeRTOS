/* 
Author: Gabriel Rodgers
Date: 10/13/2024
Purpose: Configure clocks for system and peripherals
*/

#include <stdint.h>

#include "clock.h"

//initialize sysclk and flash wait state
void sysclk_init(void) {
	FLASH_ACR |= (1 << 1); //2 wait states

	//select MSI range from RCC_CR register
	RCC_CR |= (1 << 3);
	
	//set MSI range to 48 MHz
	RCC_CR &= ~(0xF << 4);
	RCC_CR |= (0xB << 4);

	for (volatile uint8_t i = 0; i < 8; i++);
}

//enable HSI16 clock
void hsi_init(void) {
	RCC_CR |= (1 << 9); //enable HSI16 for Stop modes
	RCC_CR |= (1 << 8); //enable HSI16
	
	//loop until HSI16 is ready
	while (((RCC_CR >> 10) & 1) != 1);
}


//initialize peripheral clocks: GPIOA/C/F, SYSCFG
void peripheral_clk_init(void) {
	RCC_AHB2ENR |= (1 << 0); //GPIOA enable
	RCC_APB1ENR1 |= (1 << 0); //TIM2 enable
	//RCC_AHB2ENR |= (1 << 1); //GPIOB enable
	//RCC_AHB2ENR |= (1 << 2); //GPIOC enable
	//RCC_APB2ENR |= (1 << 0); //SYSCFG enable

	for (volatile uint8_t i = 0; i < 8; i++);
}
