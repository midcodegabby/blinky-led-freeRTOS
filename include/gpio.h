/* 
Author: Gabriel Rodgers <gabrielrodgers4i@gmail.com>
Date: 6/5/2025
*/

#include <stdint.h>


#ifndef _GPIO_H
#define _GPIO_H

typedef enum {
    PWM,
    OUTPUT,
    INPUT
} GPIO_mode_t;

void gpio_button_init(void);
void gpio_led_init(GPIO_mode_t mode);
void gpio_toggle(char port, uint8_t pin);
void gpio_on(char port, uint8_t pin);
void gpio_off(char port, uint8_t pin);

#endif /* _GPIO_H */