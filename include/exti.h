/*
Author: Gabriel Rodgers
Date: 10/13/2024
*/

#ifndef EXTI_H_
#define EXTI_H_

#define EXTI 0x40010400
#define SYSCFG 0x40010000

#define EXTI_IMR1 (*((volatile uint32_t *) EXTI))
#define EXTI_EMR1 (*((volatile uint32_t *) (EXTI + 0x04)))
#define EXTI_PR1 (*((volatile uint32_t *) (EXTI + 0x14)))
#define EXTI_RTSR1 (*((volatile uint32_t *) (EXTI + 0x08)))
#define EXTI_FTSR1 (*((volatile uint32_t *) (EXTI + 0x0C)))
#define SYSCFG_EXTICR4 (*((volatile uint32_t *) (SYSCFG + 0x14)))

void exti_init(void);
void exti_enable(void);
void exti_disable(void);
void EXTI15_10_IRQHandler(void);

#endif /* EXTI_H_ */
