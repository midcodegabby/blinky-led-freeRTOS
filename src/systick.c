/*
Author: Gabriel Rodgers
Date: 12/29/2024
Purpose: Enable and configure systick registers for 1 ms interrupts for FreeRTOS use.
*/

#include <stdint.h>

#include "systick.h"

//Register Definitions
#define STK 0xE000E010

#define STK_CTRL (*((volatile uint32_t *) STK))
#define STK_LOAD (*((volatile uint32_t *) (STK + 0x04)))

static uint32_t AHB_CLK = 48000000U;

//initialize systick
void systick_init(void) {
	
	//set clock source of systick to AHB 
	STK_CTRL |= (1<<2);

	//enable interrupts when systick reaches 0
	STK_CTRL |= (1<<1);

	//Calculate N and put it into the STK_LOAD register to generate a systick interrupt every 1ms
	STK_LOAD = (AHB_CLK/1000) - 1;
}

//enable systick
void systick_enable(void) {
	STK_CTRL |= (1);
}

//disable systick
void systick_disable(void) {
	STK_CTRL &= ~(1);
}

//IRQ handler for systick interrupt - keep as weak alias in startup code so that freeRTOS can use it.