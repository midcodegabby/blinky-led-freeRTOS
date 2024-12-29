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

#include <FreeRTOS.h>
#include <task.h>

int main(void) {
	
	sysclk_init();
	peripheral_clk_init();

	//nvic_enable();
	//nvic_priority();

	//gpio_led_init();
	//gpio_led_on();

	//timer2_init();
	//timer2_enable();

	while (1) {
		
	}

	return 0;
}
