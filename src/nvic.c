/*
Author: Gabriel Rodgers
Date: 10/13/2024
Purpose: To control interrupts through the NVIC;
        this file only effects interrupts 40 (Button)
*/

#include <stdint.h>
#include "nvic.h"

//enable NVIC
void nvic_enable(void) {
        NVIC_ISER1 |= (1 << 8); //enable interrupt 40 (user button)
        NVIC_ISER0 |= (1 << 28); //enable interrupt 28 (TIM2 global interrupt)
}

//disable NVIC
void nvic_disable(void) {
        NVIC_ICER1 |= (1 << 8); //disable interrupt 40 (user button)
        NVIC_ICER0 |= (1 << 28); //disable interrupt 28 (TIM2 global interrupt)
}

//change priorities of nvic
void nvic_priority(void) {
	//change priority of button interrupt (40) to lowest
	NVIC_IPR10 |= (0xF << 4); 
	//change priority of TIM2 global interrupt (28) to lowest
	NVIC_IPR7 |= (0xF << 0);

}

