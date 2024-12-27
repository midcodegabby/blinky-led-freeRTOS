/*
spi.h

Author: Gabriel Rodgers
Date: 12/26/2024
*/

#ifndef INC_SPI_H_
#define INC_SPI_H_

//Register Macros
#define GPIOA 0x48000000
#define RCC 0x40021000

#define GPIOA_ODR (*((volatile uint32_t *) (GPIOA + 0x14)))
#define GPIOA_MODER (*((volatile uint32_t *) GPIOA))
#define GPIOA_OTYPER (*((volatile uint32_t *) (GPIOA + 0x04)))
#define GPIOA_OSPEEDR (*((volatile uint32_t *) (GPIOA + 0x08)))
#define GPIOA_PUPDR (*((volatile uint32_t *) (GPIOA + 0x0C)))
#define GPIOA_BSRR (*((volatile uint32_t *) (GPIOA + 0x18)))

#define RCC_CR (*((volatile uint32_t *) RCC)) 	//sysclk config
#define RCC_CFGR (*((volatile uint32_t *) (RCC + 0x08)))	//clk config
#define RCC_AHB1ENR (*((volatile uint32_t *) (RCC + 0x48)))	//clk enable for peripherals
#define RCC_AHB2ENR (*((volatile uint32_t *) (RCC + 0x4C)))	//clk enable for peripherals
#define RCC_APB1ENR1 (*((volatile uint32_t *) (RCC + 0x58)))	//clk enable for peripherals
#define RCC_CCIPR (*((volatile uint32_t *) (RCC + 0x88)))

void spi_init();
void spi_write(uint8_t c);

#endif 
