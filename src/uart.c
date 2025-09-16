/* 
Author: Gabriel Rodgers <gabrielrodgers4i@gmail.com>
Date: 31/8/2025
*/

#include <stdint.h>

#include "stm32h723xx.h"
#include "uart.h"
#include "main.h"
#include "misc.h"

#define GPIO_AFRL_AFSEL5_AF7 (GPIO_AFRL_AFSEL5_Msk & \
				~GPIO_AFRL_AFSEL5_3)
#define GPIO_AFRL_AFSEL6_AF7 (GPIO_AFRL_AFSEL6_Msk & \
				~GPIO_AFRL_AFSEL6_3)

/*
 * Initialize UART2 with the given clock rate. 
 *
 * In: None
 * Out: status (ERROR/OK)
 * 
 * Pins:
 * PD6 - USART2_RX
 * PD5 - USART2_TX
 *
 * To connect in Linux, run (to copy, install gvim, run "+y" on the line below:
 * picocom -b 921600 --databits 8 --parity n --stopbits 2 --flow n /dev/ttyUSB0
 *
*/
status_t uart_init(uint32_t rate) {
    uint16_t usartdiv = 2*SYSCLK_FREQ/rate;

    /* Clock */
	RCC->AHB4ENR |= (RCC_AHB4ENR_GPIODEN_Msk); 
	RCC->APB1LENR |= (RCC_APB1LENR_USART2EN_Msk);

	/* GPIO */
	GPIOD->MODER &= ~(GPIO_MODER_MODER5_0);
	GPIOD->MODER &= ~(GPIO_MODER_MODER6_0);
	GPIOD->AFR[0] |= GPIO_AFRL_AFSEL5_AF7;
	GPIOD->AFR[0] |= GPIO_AFRL_AFSEL6_AF7;

	/* UART */
	USART2->CR1 |= USART_CR1_OVER8;
	USART2->CR1 |= USART_CR1_TE;
	USART2->CR1 |= USART_CR1_RE;

	USART2->CR2 |= USART_CR2_STOP_1; //2 stop bits

	USART2->CR3 |= USART_CR3_ONEBIT; //one-bit sampling

	/* 
	 * BRR[15:4] = USARTDIV[15:4] 
	 * BRR[3:0] = USARTDIV[3:0] >> 1
	*/
	USART2->BRR = (usartdiv & USART_BRR_DIV_MANTISSA) | 
                    ((usartdiv >> 1) & USART_BRR_DIV_FRACTION);
					 
	USART2->CR1 |= USART_CR1_UE;

	return OK;
}

/*
 * Send a byte of data over UART2
 *
 * In: Data buffer
 * Out: status (ERROR/OK)
 *
*/
status_t uart_tx(const char buf) {
	USART2->TDR = buf;
	
	while ((USART2->ISR & USART_ISR_TC) != USART_ISR_TC);

	return OK;
}


/*
 * Send a buffer over uart
 *
 * In: Data buffer (must be null terminated
 * Out: status (ERROR/OK)
 *
*/
status_t write(const char* buf) {
    uint32_t i = 0;     /* iterator for buf */

    if (!buf) {
        return ERROR;
    }

    for (i = 0; buf[i] != '\0'; i++) {
        uart_tx(buf[i]);
    }

	return OK;
}






