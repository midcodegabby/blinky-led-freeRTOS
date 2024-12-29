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

int main(void) {
	
	sysclk_init();
	peripheral_clk_init();

	//nvic_enable();
	//nvic_priority();

	gpio_led_init();
	//gpio_led_on();

	timer2_init();
	timer2_enable();

	while (1) {
		/*
		if (timer2_check() == 1) {
			//timer2_clear();
			//gpio_led_toggle();
		}
		*/

		while (TIM2_CNT <= 0xFFFFF) {
		}

		//gpio_led_toggle();

		/*
		while ((TIM2_SR & 1) != 1) {
		}
		gpio_led_toggle();
		TIM2_SR &= ~(1);
		*/
	}

	return 0;
}
