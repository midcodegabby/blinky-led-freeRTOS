/* 
Author: Gabriel Rodgers <gabrielrodgers4i@gmail.com>
Date: 6/9/2025
*/

#include <stdint.h>

#ifndef _MAIN_H
#define _MAIN_H

#define SYSCLK_FREQ     (64000000U)

//#define SCB 0xE000E008

//#define AIRCR (*((volatile uint32_t *) (SCB + 0x0C)))

#define VECTKEY (0x5FA << 16)

typedef enum {
    PRESSED,
    UNPRESSED
} button_state_t;

#endif /* _MAIN_H */
