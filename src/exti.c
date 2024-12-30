/*
Author: Gabriel Rodgers
Date: 10/13/2024
Purpose: to enable interrupts and handle some IRQs
*/

#include <stdint.h>

#include "exti.h"
#include "clock.h"
#include "nvic.h"
#include "gpio.h"

//enable interrupts
void exti_init(void) {

        //enable falling edge trigger for line 13
        EXTI_FTSR1 |= (1 << 13);

        //disable rising edge trigger for line 13
        EXTI_RTSR1 &= ~(1 << 13);

        //choose PC13 to be the event trigger for EXTI13
        SYSCFG_EXTICR4 |= (1 << 5);
}

void exti_enable(void) {
        //enable interrupts for line 13, corresponding to the user button
        EXTI_IMR1 |= (1 << 13);
}

void exti_disable(void) {
        //disable interrupts for line 13, corresponding to the user button
        EXTI_IMR1 &= ~(1 << 13);
}

//IRQ handler for button push interrupt
void EXTI15_10_IRQHandler(void) {
	//disable interrupts
        nvic_disable(); 
	
	gpio_led_toggle();

        //clear any pending interrupts and re-enable interrupts
        EXTI_PR1 |= (1 << 13);
	nvic_enable();
}

