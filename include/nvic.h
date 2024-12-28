/*
Author: Gabriel Rodgers
Date: 10/13/2024
*/

#ifndef NVIC_H_
#define NVIC_H_

#define NVIC_ISER 0xE000E100
#define NVIC_ICER 0xE000E180
#define NVIC_IPR 0xE000E400

#define NVIC_ISER0 (*((volatile uint32_t *) (NVIC_ISER)))
#define NVIC_ICER0 (*((volatile uint32_t *) (NVIC_ICER)))
#define NVIC_ISER1 (*((volatile uint32_t *) (NVIC_ISER + 0x04)))
#define NVIC_ICER1 (*((volatile uint32_t *) (NVIC_ICER + 0x04)))
#define NVIC_IPR7 (*((volatile uint32_t *) (NVIC_IPR + 0x1C)))
#define NVIC_IPR8 (*((volatile uint32_t *) (NVIC_IPR + 0x20)))
#define NVIC_IPR10 (*((volatile uint32_t *) (NVIC_IPR + 0x28)))
#define NVIC_IPR13 (*((volatile uint32_t *) (NVIC_IPR + 0x34)))

void nvic_enable(void);
void nvic_disable(void);
void nvic_priority(void);

#endif /* NVIC_H_ */
