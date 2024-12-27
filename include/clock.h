/*
Author: Gabriel Rodgers
Date: 10/13/2024
*/

#ifndef CLOCK_H
#define CLOCK_H

#define RCC 0x40021000
#define FLASH 0x40022000

#define RCC_CR (*((volatile uint32_t *) (RCC))) 
#define RCC_CFGR (*((volatile uint32_t *) (RCC + 0x08)))
#define RCC_AHB1ENR (*((volatile uint32_t *) (RCC + 0x48)))
#define RCC_AHB2ENR (*((volatile uint32_t *) (RCC + 0x4C)))
#define RCC_APB1ENR1 (*((volatile uint32_t *) (RCC + 0x58)))
#define RCC_APB2ENR (*((volatile uint32_t *) (RCC + 0x60)))
#define RCC_CCIPR (*((volatile uint32_t *) (RCC + 0x88)))
									
#define FLASH_ACR (*((volatile uint32_t *) (FLASH)))		

void sysclk_init(void);
void hsi_init(void);
void peripheral_clk_init(void);

#endif /* CLOCK_H_ */
