/*
Author: Gabriel Rodgers
Date: 12/27/2024
Purpose: To control timers/counters
*/

#include <stdint.h>

#include "tcnt.h"
#include "gpio.h"
#include "nvic.h"
#include "main.h"

volatile uint32_t timer2_flag = 0;

//init the timer2 with internal clock, compare mode, and interrupts.
void timer2_init() {
    TIM2_CR1 |= (1 << 7);   //enable buffering for auto-reload
    TIM2_PSC = 47;  //prescaler for 1MHz timer frequency
    TIM2_ARR = duration_1s;  
    TIM2_EGR |= (1 << 0); //update registers
    //TIM2_DIER |= (1 << 0); //enable event interrupt
}

void timer2_enable() {
    TIM2_CR1 |= (1 << 0); //enable timer/counter
}

void timer2_disable() {
    TIM2_CR1 &= ~(1 << 0); //disable timer/counter
}

//Takes as input a duration in clock pulses, and sets the duration to that value.
void timer2_nonblocking_delay(uint32_t cycles) {
    TIM2_ARR = cycles;
    TIM2_EGR |= (1 << 0); //update registers
}

//THIS FUNCTION DOES NOT WORK RIGHT NOW
void timer2_blocking_delay(uint32_t cycles) {
    TIM2_ARR = cycles+1;
    TIM2_EGR |= (1 << 0); //update registers
    TIM2_CNT = 0;

    while (TIM2_CNT < cycles);   //loop until duration is reached (995 is the breaking point)
}

// IRQ handler for Timer2 global interrupt
void TIM2_IRQHandler(void) {
    nvic_disable();

    //gpio_led_toggle();
    timer2_flag = 1;

    TIM2_SR &= ~(1 <<0); //clear the UIF flag
    nvic_enable();
}