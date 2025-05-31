#include "find.h"
#include "bsp_timer.h"
#include "bsp_sys.h"
#include "delay.h"

//寻迹传感器从右到左以此O1 O2 O3 O4 
//硬件连接:O1-PA4，O2-PA5，O3-PA6，O4-PA7.
//要初始化为输入模式
void Find_IO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	//开启GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6 | GPIO_Pin_7;//选择IO端口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//配置为上拉输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);//根据GPIO_InitStructure中指定的参数初始化外设GPIOD寄存器

} 

//循迹模块:黑线输出高电平1，白线低电平0。
//循迹路面：白色路面黑色引导线，即寻黑线。
void Find(void)
{
	//O4 白色，O3 黑色，O2 黑色，O1 白色。即循迹传感器中间在黑线上，前进
	if((Find_O4 == 0)&&(Find_O3 == 1)&&(Find_O2 == 1)&&(Find_O1 == 0))
	{
			MOTOR_PWM_Out(3000,3000,3000,3000);
			Car_Go();
	}
	//O4 白色，O3 白色，O2 白色，O1 白色。即循迹传感器全白线上，前进
	else if((Find_O4 == 0)&&(Find_O3 == 	0)&&(Find_O2 == 0)&&(Find_O1 == 0))
	{	MOTOR_PWM_Out(3000,3000,3000,3000);
			Car_Go();
	}
	//O4 白色，O3 白色，O2 黑色，O1 白色。小车偏左
	//应向右转调整到前进方向	。即左轮加速右轮减速
	else if((Find_O4 == 0)&&(Find_O3 == 0)&&(Find_O2 == 1)&&(Find_O1 == 0))// O2寻到黑线
	{
			MOTOR_PWM_Out(3000,0,0,3000);
			Car_Go();
			//Car_Turn_Right();
	}
	//O4 白色，O3 白色，O2 黑色，O1 黑色。小车偏偏左
	//应向右转调整到前进方向	。即左轮加速右轮减速
	else if((Find_O4 == 0)&&(Find_O3 == 0)&&(Find_O2 == 1)&&(Find_O1 == 1))// O2 O1寻到黑线
	{
			MOTOR_PWM_Out(3000,3000,3000,3000);
			Car_Turn_Right();
			Delay_ms(200);
			while(Find_O3 != 1);//等带小车转过来
			Car_Go();
			Delay_ms(50);
	}
	//O4 白色，O3 黑，O2 黑色，O1 黑色。小车偏偏左（L型路况）
	//应向右转调整到前进方向	。即左轮加速右轮减速
	else if((Find_O4 == 0)&&(Find_O3 == 1)&&(Find_O2 == 1)&&(Find_O1 == 1))
	{	
			MOTOR_PWM_Out(3000,3000,3000,3000);
			Car_Turn_Right();
			Delay_ms(50);
			while(Find_O3 != 1);//等带小车转过来
			Car_Go();
			Delay_ms(50);
	}
	//O4 白色，O3 白色，O2 白色，O1 黑色。小车偏偏偏左
	//应向右转调整到前进方向	。即左轮加速右轮减速
	else if((Find_O4 == 0)&&(Find_O3 == 0)&&(Find_O2 == 0)&&(Find_O1 == 1))
	{		
			MOTOR_PWM_Out(3000,3000,3000,3000);
			Car_Turn_Right();
			while(Find_O3 != 1);//等带小车转过来
			Car_Go();
			Delay_ms(50);
	}
	//O4 白色，O3 黑色，O2 白色，O1 白色。小车偏右
	//应向左转调整到前进方向	。即右轮加速左轮减速
	else if((Find_O4 == 0)&&(Find_O3 == 1)&&(Find_O2 == 0)&&(Find_O1 == 0))
	{
		MOTOR_PWM_Out(3000,0,0,3000);
		Car_Go();
	}
	//O4 黑色，O3 黑色，O2 白色，O1 白色。小车偏偏右
	//应向左转调整到前进方向	。即右轮加速左轮减速
	else if((Find_O4 == 1)&&(Find_O3 == 1)&&(Find_O2 == 0)&&(Find_O1 == 0))// O4寻到黑线
	{
		MOTOR_PWM_Out(3000,3000,3000,3000);
		Car_Turn_Left();
			Delay_ms(200);
			while(Find_O2 != 1);//等带小车转过来
			Car_Go();
			Delay_ms(50);	
	}
	//O4 黑色，O3 黑色，O2 黑，O1 白色。小车偏偏右（L型路况）
	//应向左转调整到前进方向	。即右轮加速左轮减速
	else if((Find_O4 == 1)&&(Find_O3 == 1)&&(Find_O2 == 1)&&(Find_O1 == 0))
	{
		MOTOR_PWM_Out(3000,3000,3000,3000);
		Car_Turn_Left();
			Delay_ms(50);
			while(Find_O2 != 1);//等带小车转过来
			Car_Go();
			Delay_ms(50);
	}
	//O4 黑色，O3 白色，O2 白色，O1 白色。小车偏偏右
	//应向左转调整到前进方向	。即右轮加速左轮减速
		else if((Find_O4 == 1)&&(Find_O3 == 0)&&(Find_O2 == 0)&&(Find_O1 == 0))
	{
		MOTOR_PWM_Out(3000,3000,3000,3000);
			Car_Turn_Left();
			while(Find_O2 != 1);//等带小车转过来
			Car_Go();
			Delay_ms(50);
	}
/*停车
			else if((Find_O4 == 0)&&(Find_O3 == 0)&&(Find_O2 == 0)&&(Find_O1 == 0))
	{
		MOTOR_PWM_Out(3000,3000,3000,3000);
		Car_Stop();
	}
*/
}
