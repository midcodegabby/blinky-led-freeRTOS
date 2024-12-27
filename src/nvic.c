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
        NVIC_ISER1 |= (1 << 1); //enable interrupt 33 (I2C2_EV)
}

//disable NVIC
void nvic_disable(void) {
        NVIC_ICER1 |= (1 << 8); //disable interrupt 40 (user button)
        NVIC_ICER1 |= (1 << 1); //disable interrupt 33 (I2C2_EV)
}

//change priorities of nvic
void nvic_priority(void) {
	//change priority of button interrupt (40) to lowest
	NVIC_IPR10 |= (0xF << 4); 
	//change priority of NACK interrupt (33) to second lowest
	NVIC_IPR8 |= (0xE << 12);

}

