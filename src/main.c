/*
Author: Gabriel Rodgers
Date: 8/1/2024
Purpose: To get the LD2 on the Nucleo-L476RG to turn on. 
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "clock.h"
#include "gpio.h"
#include "tcnt.h"
#include "nvic.h"

#include <FreeRTOS.h>
#include <task.h>

#define STACK_SIZE (50)
#define NVIC_PriorityGroup_4 (~(1 << 10))

//task prototypes
void task1_handler(void *args);
void task2_handler(void *args);

extern volatile uint32_t timer2_flag;

//This function initializes all the hardware required for the rtos tasks
static void hardware_init(void) {
	sysclk_init();
	peripheral_clk_init();
	//nvic_enable();		
	//nvic_priority();	//set interrupts to lowest priority.

	//Make sure NVIC uses no subpriorities
	AIRCR |= (VECTKEY);	//use the VECTKEY to gain write access to the AIRCR register
	AIRCR &= (NVIC_PriorityGroup_4); //clear bit 10 in AIRCR, resulting in no subpriorities

	gpio_led_init();

	timer2_init();
	timer2_enable();
}


int main(void) {

	BaseType_t status;

	hardware_init();

	status = xTaskCreate( (TaskFunction_t) task1_handler, "task1", STACK_SIZE, NULL, 1, NULL);
	configASSERT(status == pdPASS);

	status = xTaskCreate( (TaskFunction_t) task2_handler, "task2", STACK_SIZE, NULL, 1, NULL);
	configASSERT(status == pdPASS);

	vTaskStartScheduler();

	//if the program gets to here, then that means that the heap was overrun - which is not good.
	while (1) {
	}

	return 0;
}

/*---------------------------TASKS---------------------------*/
/*-----------------------------------------------------------*/
void task1_handler(void *args) {
	while(1) {
		gpio_led_on();
		//timer2_blocking_delay(duration_1ms*100);
	}
}

void task2_handler (void *args) {
	while(1) {
		gpio_led_off();
		//timer2_blocking_delay(duration_1s);
	}
}
/*-----------------------------------------------------------*/

/*----------------------------HOOKS--------------------------*/
/*-----------------------------------------------------------*/
//allows for debugging in the case of stack overflow.
void vApplicationStackOverflowHook( TaskHandle_t pxTask,
                                    char * pcTaskName )
{
    ( void ) pcTaskName;
    ( void ) pxTask;

    /* Run time stack overflow checking is performed if
     * configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
     * function is called if a stack overflow is detected. */
    taskDISABLE_INTERRUPTS();

	//do stuff in here to debug
    for( ; ; ) {
		gpio_led_on();
		timer2_blocking_delay(duration_1ms*100);
	}
    
}
/*-----------------------------------------------------------*/

