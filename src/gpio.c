/* 
Author: Gabriel Rodgers <gabrielrodgers4i@gmail.com>
Date: 6/5/2025
*/

#include <stdint.h>

#include "stm32h723xx.h"
#include "gpio.h"

void gpio_button_init(void){
    GPIOC->MODER &= ~(0x3 << 26); //input mode for PC13
	GPIOC->PUPDR |= (1 << 27); //pull down R for PC13
}

void gpio_led_init(GPIO_mode_t MODE){
    switch(MODE) {
        case(OUTPUT):
            GPIOB->MODER &= ~(1 << 1); //output mode for PB0
            GPIOB->MODER &= ~(1 << 29); //output mode for PB14
            GPIOE->MODER &= ~(1 << 3); //output mode for PE1
            break;
        case(PWM):
            GPIOB->MODER &= ~(1 << 0); //alt func for PB0
            GPIOB->MODER &= ~(1 << 28); //alt func for PB14

            GPIOB->AFR[0] |= GPIO_AFRL_AFSEL0_1; //TIM3_CH3, AF2
            GPIOB->AFR[1] |= GPIO_AFRH_AFSEL14_1; //TIM12_CH2, AF2  
            break;
        default:
            break;
    }
}

void gpio_toggle(char port, uint8_t pin){
    switch(port) {
        case('B'):
            GPIOB->ODR ^= (1 << pin);
            break;
        case('C'):
            GPIOC->ODR ^= (1 << pin); 
            break;
        case('E'):
            GPIOE->ODR ^= (1 << pin); 
            break;
        default:
            break;
    }
}

void gpio_on(char port, uint8_t pin) {
    switch(port) {
        case('B'):
            GPIOB->BSRR |= (1 << pin);
            break;
        case('C'):
            GPIOC->BSRR |= (1 << pin); 
            break;
        case('E'):
            GPIOE->BSRR |= (1 << pin); 
            break;
        default:
            break;
    }
}

void gpio_off(char port, uint8_t pin) {
    switch(port) {
        case('B'):
            GPIOB->BSRR |= (1 << (pin + 16));
            break;
        case('C'):
            GPIOC->BSRR |= (1 << (pin + 16)); 
            break;
        case('E'):
            GPIOE->BSRR |= (1 << (pin + 16)); 
            break;
        default:
            break;
    }
}

