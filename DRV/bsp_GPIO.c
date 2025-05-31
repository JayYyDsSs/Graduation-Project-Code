#include "bsp_GPIO.h"

//Ӳ�����ӣ�LED1----PC13

void LED_GPIO_Init(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd( LED1_CLK, ENABLE); 	/*����GPIO������ʱ��*/																   
		GPIO_InitStructure.GPIO_Pin = LED1_Pin;	/*ѡ��Ҫ���Ƶ�GPIO����*/	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; /*��������ģʽΪͨ���������*/   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; /*������������Ϊ50MHz */ 
		GPIO_Init(LED1_PORT, &GPIO_InitStructure);/*���ÿ⺯������ʼ��GPIOC13*/	
}

//LED��˸
void LED1_Flash(int time)
{
			 static int temp;
		if(++temp==time)
		{
			GPIO_WriteBit(LED1_PORT, LED1_Pin, (BitAction) (1 - GPIO_ReadInputDataBit(LED1_PORT, LED1_Pin)))	;//LED ��ɫɫ״̬��ת
			temp=0;
		}
}
