/*
Author: Gabriel Rodgers
Date: 12/30/2024
Purpose: Provide debugging functionality
*/

#include <stdint.h>

// global registers for debugging hardfaults.
volatile uint32_t r0;
volatile uint32_t r1;
volatile uint32_t r2;
volatile uint32_t r3;
volatile uint32_t r12;
volatile uint32_t lr; //Link register.
volatile uint32_t pc; //Program counter. 
volatile uint32_t psr; //Program status register.

/*-----------------------------------------------------------*/
//Allows debugging in the event of a hardfault. 
void prvGetRegistersFromStack( uint32_t *pulFaultStackAddress ) {
/* These are volatile to try and prevent the compiler/linker optimising them
   away as the variables never actually get used. If the debugger won't show the
   values of the variables, make them global my moving their declaration outside
   of this function. */

    r0 = pulFaultStackAddress[ 0 ];
    r1 = pulFaultStackAddress[ 1 ];
    r2 = pulFaultStackAddress[ 2 ];
    r3 = pulFaultStackAddress[ 3 ];

    r12 = pulFaultStackAddress[ 4 ];
    lr = pulFaultStackAddress[ 5 ];
    pc = pulFaultStackAddress[ 6 ];
    psr = pulFaultStackAddress[ 7 ];

    /* When the following line is hit, the variables contain the register values. */
    for( ;; );
}
/*-----------------------------------------------------------*/