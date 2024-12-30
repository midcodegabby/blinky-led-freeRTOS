/*
main.h

Author: Gabriel Rodgers
Date: 12/26/2024
*/

#ifndef MAIN_H_
#define MAIN_H_

#define SCB 0xE000E008

#define AIRCR (*((volatile uint32_t *) (SCB + 0x0C)))

#define VECTKEY (0x5FA << 16)

static void hardware_init(void);
int main(void); 

#endif /* MAIN_H_*/
