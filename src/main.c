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
#include "exti.h"
#include "nvic.h"
#include "uart.h"
#include "misc.h"

#include "stm32h723xx.h"

#include <FreeRTOS.h>
#include <task.h>
//#include <portable.h>

#define STACK_SIZE (50)
#define NVIC_PriorityGroup_4 (~(1 << 10))

const GPIO_mode_t led_mode = OUTPUT;
const uint8_t pwm_max = 0xF;
volatile button_state_t button = UNPRESSED;


/* task prototypes */

void task1_handler(void *args);
void task2_handler(void *args);


//This function initializes all the hardware required for the rtos tasks
static void hardware_init(void) {
	clock_peripherals_init();
	gpio_button_init();
	gpio_led_init(led_mode);
	nvic_enable();
	exti_init(); 
	//timer3_pwm_init();
	//timer12_pwm_init();
	//timer3_down_init(); 	
	//uart_init(38400);   	
	uart_init(921600);
	SCB->AIRCR |= (VECTKEY);	//use the VECTKEY to gain write access to the AIRCR register
    SCB->AIRCR &= (NVIC_PriorityGroup_4); //clear bit 10 in AIRCR, resulting in no subpriorities
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
    const TickType_t xDelay = pdMS_TO_TICKS(3000);  /* 1 second */
    //int size = 27;
    //char* pTimeStamp = (char*) pvPortMalloc(size);
    //int timeList[12] = {9};     /* init to 0 */

    /* Digits for time/date */
    /* 0H:0M:0S  0D/0M/0Y */
/*
    snprintf(pTimeStamp, 27, "Time: %d%d:%d%d:%d%d  %d%d/%d%d/%d%d\r\n", timeList[0], timeList[1], \
             timeList[2], timeList[3], timeList[4], timeList[5], timeList[6], timeList[7],         \
             timeList[8], timeList[9], timeList[10], timeList[11]);
*/

	while(1) {
        gpio_on('B', 0);
        gpio_on('E', 1);
        gpio_on('B', 14);

        
        //write(pTimeStamp);
        write("Hello World\r\n");

        vTaskDelay(xDelay);
    
	}
    //vPortFree(pTimeStamp);
}

void task2_handler (void *args) {
	while(1) {
        gpio_off('B', 0);
        gpio_off('E', 1);
        gpio_off('B', 14);
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

    gpio_on('B', 0);
    gpio_on('E', 1);
    gpio_on('B', 14);

	//do stuff in here to debug
    for( ; ; ) {
	}
    
}
/*-----------------------------------------------------------*/

