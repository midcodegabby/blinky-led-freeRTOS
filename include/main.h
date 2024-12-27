/*
main.h

Author: Gabriel Rodgers
Date: 12/26/2024
*/

#ifndef MAIN_H_
#define MAIN_H_

#define GPIOA 0x48000000
#define RCC 0x40021000

#define GPIOA_ODR (*((volatile uint32_t *) (GPIOA + 0x14)))
#define GPIOA_MODER (*((volatile uint32_t *) GPIOA))
#define GPIOA_OTYPER (*((volatile uint32_t *) (GPIOA + 0x04)))
#define GPIOA_OSPEEDR (*((volatile uint32_t *) (GPIOA + 0x08)))
#define GPIOA_PUPDR (*((volatile uint32_t *) (GPIOA + 0x0C)))
#define GPIOA_BSRR (*((volatile uint32_t *) (GPIOA + 0x18)))

int main(void); 

#endif /* MAIN_H_*/
