#include "bsp_GPIO.h"

//硬件连接：LED1----PC13

void LED_GPIO_Init(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd( LED1_CLK, ENABLE); 	/*开启GPIO的外设时钟*/																   
		GPIO_InitStructure.GPIO_Pin = LED1_Pin;	/*选择要控制的GPIO引脚*/	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; /*设置引脚模式为通用推挽输出*/   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; /*设置引脚速率为50MHz */ 
		GPIO_Init(LED1_PORT, &GPIO_InitStructure);/*调用库函数，初始化GPIOC13*/	
}

//LED闪烁
void LED1_Flash(int time)
{
			 static int temp;
		if(++temp==time)
		{
			GPIO_WriteBit(LED1_PORT, LED1_Pin, (BitAction) (1 - GPIO_ReadInputDataBit(LED1_PORT, LED1_Pin)))	;//LED 蓝色色状态翻转
			temp=0;
		}
}
