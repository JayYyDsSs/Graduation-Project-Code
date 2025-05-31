#include "bsp_sys.h"

void STM32_System_Init(void)
{	
	//STM32内部初始化
	Delay_Init(72);        //滴答时钟初始化
	NVIC_Config();         //中断配置配置初始化
	LED_GPIO_Init();     //LED初始化
	USART1_Init(115200);   //串口初始化
	Bluetooth_Init(9600); //蓝牙串口初始化
	//外接设备初始化
	Find_IO_Init();
	Wave_IO_Init();
	TIM1_PWM_Init(1000,1440);
	TIM_SetCompare1(TIM1,75);//占空比5%，90度;//舵机转到中间
	Duoji_Control(ON);
	Delay_ms(500);//
	Duoji_Control(OFF);
	MOTOR_GPIO_Init();     //电机驱动IO配置
  TIM8_PWM_Init(3600,1);      //PWM频率初始化20KHz
	
	Encoder_Init_TIM2();TIM2 -> CNT=30000;
	Encoder_Init_TIM3();TIM3 -> CNT=30000;
	Encoder_Init_TIM4();TIM4 -> CNT=30000;
	Encoder_Init_TIM5();TIM5 -> CNT=30000;
	OLED_Init();
	OLED_Clear();
	OLED_ShowCHinese(0,0,2);  //显示汉字 车
	OLED_ShowCHinese(16,0,3); //显示汉字 速
	OLED_ShowString(88,0,"m/min",16);          //OLED第一行显示整体车速 单位m/min
	OLED_ShowString(0,2,"A:      B:      ",12);          //显示左轮转  R单位RPM 表示每分钟车轮的圈数
	OLED_ShowString(0,3,"D:      C:      ",12);         //显示右轮转  R单位RPM 表示每分钟车轮的圈数
	OLED_ShowString(0,4,"P:   I:   D:   ",12); //显示PID参数
	OLED_ShowString(0,6,"Set_C:    RPM",12);      //显设置的车轮转速单位RPM
	Timer6_Init();
	Delay_ms(100);         //等待初始化完成
}
