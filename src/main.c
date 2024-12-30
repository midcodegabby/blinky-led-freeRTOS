/*
Author: Gabriel Rodgers
Date: 8/1/2024
Purpose: To get the LD2 on the Nucleo-L476RG to turn on. 
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "clock.h"
#include "gpio.h"
#include "timers.h"
#include "nvic.h"
#include "systick.h"

#include <FreeRTOS.h>
#include <task.h>

#define STACK_SIZE (128)
#define NVIC_PriorityGroup_4 (~(1 << 10))

//task prototypes
void slow_led_task (void *argument);
void fast_led_task (void *argument);

extern volatile uint32_t timer2_flag;

//This function initializes all the hardware required for the rtos tasks
static void hardware_init(void) {
	sysclk_init();
	peripheral_clk_init();
	systick_init();
	systick_enable();
	nvic_enable();		
	nvic_priority();	//set interrupts to lowest priority.

	//Make sure NVIC uses no subpriorities
	AIRCR |= (VECTKEY);	//use the VECTKEY to gain write access to the AIRCR register
	AIRCR &= (NVIC_PriorityGroup_4); //clear bit 10 in AIRCR, resulting in no subpriorities

	gpio_led_init();

	timer2_init();
	timer2_enable();
}


int main(void) {

	hardware_init();


	

	while (1) {
	}

	return 0;
}


void slow_led_task(void *argument) {
	while(1) {

	}
}

void fast_led_task(void *argument) {
	while(1) {

	}
}