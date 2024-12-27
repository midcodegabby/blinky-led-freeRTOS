/*
Author: Gabriel Rodgers
Date: 10/13/2024
*/

#ifndef GPIO_H_
#define GPIO_H_

#define GPIOA 0x48000000
#define GPIOB 0x48000400
#define GPIOC 0x48000800
//#define GPIOF 0x48001400

#define GPIOA_MODER (*((volatile uint32_t *) GPIOA))
#define GPIOA_OTYPER (*((volatile uint32_t *) (GPIOA + 0x04)))
#define GPIOA_ODR (*((volatile uint32_t *) (GPIOA + 0x14)))

#define GPIOB_MODER (*((volatile uint32_t *) GPIOB))
#define GPIOB_OTYPER (*((volatile uint32_t *) (GPIOB + 0x4)))
#define GPIOB_OSPEEDR (*((volatile uint32_t *) (GPIOB + 0x8)))
#define GPIOB_PUPDR (*((volatile uint32_t *) (GPIOB + 0xC)))
#define GPIOB_IDR (*((volatile uint32_t *) (GPIOB + 0x10)))
#define GPIOB_AFRH (*((volatile uint32_t *) (GPIOB + 0x24)))

#define GPIOC_MODER (*((volatile uint32_t *) GPIOC))
#define GPIOC_PUPDR (*((volatile uint32_t *) (GPIOC + 0x0C)))
#define GPIOC_IDR (*((volatile uint32_t *) (GPIOC + 0x10)))

void gpio_button_init(void);
uint8_t gpio_button_poll(uint8_t);
void gpio_led_init(void);
void gpio_led_on(void);
void gpio_led_off(void);
void gpio_led_toggle(void);

#endif /* GPIO_H_ */
