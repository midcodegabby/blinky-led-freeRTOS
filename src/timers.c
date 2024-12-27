/*
Author: Gabriel Rodgers
Date: 12/27/2024
Purpose: To control timers/counters
*/

#include <stdint.h>
#include "timers.h"

//uint32_t compare_val = 0x02DC6C00;
uint32_t compare_val = 0x0000FFFF;

//init the timer2 with internal clock, compare mode, and no interrupts.
void timer2_init() {
    TIM2_CR1 |= (1 << 7);   //enable buffering for auto-reload
    TIM2_CCER |= (1 << 0); //enable CC1 as output

    TIM2_CCMR1 |= (1 << 3); //enable preload for output compare register

    TIM2_ARR = compare_val;
    TIM2_CCR1 = compare_val;
}

void timer2_enable() {
    TIM2_CR1 |= (1 << 0); //enable timer/counter
}

uint8_t timer2_check() {
    return (uint8_t) ((TIM2_SR >> 1) & (0x1));
}