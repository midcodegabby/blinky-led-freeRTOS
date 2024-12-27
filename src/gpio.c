/*
Author: Gabriel Rodgers
Date: 10/13/2024
Purpose: configure GPIOs for I2C2, button input, and LED2
*/

//include files
#include <stdint.h>
#include "gpio.h"

void gpio_button_init(void) {
	//set button pin (B1, connected to PC13) to be general purpose input mode
	GPIOC_MODER &= ~(0x3 << 26);

	//set input to pull up R
	GPIOC_PUPDR &= ~(0x3 << 26);
	GPIOC_PUPDR |= (1 << 26);
}

uint8_t gpio_button_poll(uint8_t button) {
	//check input data register and assign it to the button parameter
	button = ((GPIOC_IDR >> 13) & 1);

	//should probably do some debouncing here

	return button;
}

void gpio_led_init(void) {
	//set LED pin (GPIOA pin 5) to be general purpose output mode
	GPIOA_MODER |= (1 << 10);
	GPIOA_MODER &= ~(1 << 11);

	GPIOA_OTYPER &= ~(1 << 5); // set PA5 to be push-pull
}

void gpio_led_on(void) {
	GPIOA_ODR |= (1 << 5); 
}

void gpio_led_off(void) {
	GPIOA_ODR &= ~(1 << 5); 
}

void gpio_led_toggle(void) {
	GPIOA_ODR ^= (1 << 5); 
}

