/*
Author: Gabriel Rodgers
Date: 12/27/2024
Purpose: To control timers/counters
*/

#include <stdint.h>

#include "timers.h"
#include "gpio.h"
#include "nvic.h"

static uint32_t MAX = 0x02DC6C00;

//init the timer2 with internal clock, compare mode, and interrupts.
void timer2_init() {
    TIM2_CR1 |= (1 << 7);   //enable buffering for auto-reload
    //TIM2_CCER |= (1 << 0); //enable CC1 as output

    TIM2_ARR = MAX;
    //TIM2_CCR1 = MAX;

    //TIM2_CCMR1 |= (1 << 3); //enable preload for output compare register
    TIM2_EGR |= (1 << 0); //update registers

    //TIM2_DIER |= (1 << 1); //enable CC1 interrupt
    TIM2_DIER |= (1 << 0); //enable event interrupt

}

void timer2_enable() {
    TIM2_CR1 |= (1 << 0); //enable timer/counter
}

void timer2_disable() {
    TIM2_CR1 &= ~(1 << 0); //disable timer/counter
}

uint8_t timer2_check() {
    return 1;
}

void timer2_clear() {
    //timer2_flag = 0;
}

// IRQ handler for Timer2 global interrupt
void TIM2_IRQHandler(void) {
    nvic_disable();

    gpio_led_toggle();

    TIM2_SR &= ~(1 <<0); //clear the UIF flag
    nvic_enable();
}