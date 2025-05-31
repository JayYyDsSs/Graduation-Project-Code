#ifndef __BSP_GPIO_H
#define	__BSP_GPIO_H

#include "stm32f10x.h"

#define ON  0
#define OFF 1
//配置LED1
#define LED1_CLK  RCC_APB2Periph_GPIOC
#define LED1_PORT GPIOC
#define LED1_Pin  GPIO_Pin_13

/* 带参宏，可以像内联函数一样使用 */
#define LED1(a)	if (a)	\
					GPIO_SetBits(LED1_PORT,LED1_Pin);\
					else		\
					GPIO_ResetBits(LED1_PORT,LED1_Pin)

void LED_GPIO_Init(void);
void LED1_Flash(int time);

#endif /* __LED_H */
