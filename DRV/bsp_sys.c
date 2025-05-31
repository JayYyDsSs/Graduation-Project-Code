#include "bsp_sys.h"

void STM32_System_Init(void)
{	
	//STM32�ڲ���ʼ��
	Delay_Init(72);        //�δ�ʱ�ӳ�ʼ��
	NVIC_Config();         //�ж��������ó�ʼ��
	LED_GPIO_Init();     //LED��ʼ��
	USART1_Init(115200);   //���ڳ�ʼ��
	Bluetooth_Init(9600); //�������ڳ�ʼ��
	//����豸��ʼ��
	Find_IO_Init();
	Wave_IO_Init();
	TIM1_PWM_Init(1000,1440);
	TIM_SetCompare1(TIM1,75);//ռ�ձ�5%��90��;//���ת���м�
	Duoji_Control(ON);
	Delay_ms(500);//
	Duoji_Control(OFF);
	MOTOR_GPIO_Init();     //�������IO����
  TIM8_PWM_Init(3600,1);      //PWMƵ�ʳ�ʼ��20KHz
	
	Encoder_Init_TIM2();TIM2 -> CNT=30000;
	Encoder_Init_TIM3();TIM3 -> CNT=30000;
	Encoder_Init_TIM4();TIM4 -> CNT=30000;
	Encoder_Init_TIM5();TIM5 -> CNT=30000;
	OLED_Init();
	OLED_Clear();
	OLED_ShowCHinese(0,0,2);  //��ʾ���� ��
	OLED_ShowCHinese(16,0,3); //��ʾ���� ��
	OLED_ShowString(88,0,"m/min",16);          //OLED��һ����ʾ���峵�� ��λm/min
	OLED_ShowString(0,2,"A:      B:      ",12);          //��ʾ����ת  R��λRPM ��ʾÿ���ӳ��ֵ�Ȧ��
	OLED_ShowString(0,3,"D:      C:      ",12);         //��ʾ����ת  R��λRPM ��ʾÿ���ӳ��ֵ�Ȧ��
	OLED_ShowString(0,4,"P:   I:   D:   ",12); //��ʾPID����
	OLED_ShowString(0,6,"Set_C:    RPM",12);      //�����õĳ���ת�ٵ�λRPM
	Timer6_Init();
	Delay_ms(100);         //�ȴ���ʼ�����
}
