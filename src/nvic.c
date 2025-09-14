/* 
Author: Gabriel Rodgers <gabrielrodgers4i@gmail.com>
Date: 6/5/2025
*/

#include <stdint.h>

#include "stm32h723xx.h"
#include "nvic.h"

void nvic_enable(void) {
    NVIC->ISER[1] |= (1 << 8); //enable interrupt 40
}