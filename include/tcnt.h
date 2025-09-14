/* 
Author: Gabriel Rodgers <gabrielrodgers4i@gmail.com>
Date: 6/9/2025
*/

#include <stdint.h>

#ifndef _TCNT_H
#define _TCNT_H

#define ONE_SECOND_10KHZ		(0x2710U)

void timer3_pwm_init(void);
void timer12_pwm_init(void);
void timer3_up_init(void);
void timer3_blocking_delay(const uint32_t delay); 
void timer_pwm_set_duty(uint8_t timer_num, uint8_t duty);

#endif /* _TCNT_H */
