/*
Author: Gabriel Rodgers
Date: 12/27/2024
*/

#ifndef TCNT_H_
#define TCNT_H_

#define TIM2 0x40000000

#define TIM2_CR1 (*((volatile uint32_t *) (TIM2)))
#define TIM2_DIER (*((volatile uint32_t *) (TIM2 + 0x0C)))
#define TIM2_SR (*((volatile uint32_t *) (TIM2 + 0x10)))
#define TIM2_EGR (*((volatile uint32_t *) (TIM2 + 0x14)))
#define TIM2_CCMR1 (*((volatile uint32_t *) (TIM2 + 0x18)))
#define TIM2_CCER (*((volatile uint32_t *) (TIM2 + 0x20)))
#define TIM2_CNT (*((volatile uint32_t *) (TIM2 + 0x24)))
#define TIM2_PSC (*((volatile uint32_t *) (TIM2 + 0x28)))
#define TIM2_ARR (*((volatile uint32_t *) (TIM2 + 0x2C)))
#define TIM2_CCR1 (*((volatile uint32_t *) (TIM2 + 0x34)))

void timer2_init(void);
void timer2_enable(void);
void timer2_disable(void);
void timer2_nonblocking_delay(uint32_t cycles);
void timer2_blocking_delay(uint32_t cycles);

#endif /* TCNT_H_ */