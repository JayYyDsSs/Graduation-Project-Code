#include "bsp_sys.h"
#include "stdio.h"

unsigned char BLE_RX[64];
extern int SetPoint;
extern u8 wave_flag;
char xj_flag=0;
u8 juli_r;//右边距离
u8 juli_l;
u8 juli_m;
extern int Moto_A,Moto_B,Moto_C,Moto_D;//PWM 
extern int para_A,para_B,para_C,para_D;//增量
extern u16 Distance;

int main(void)
{	
	STM32_System_Init();//所有系统配置在这个函数里完成
	
	while (1)
	{
		
		USART2_Receive(BLE_RX, 6);//蓝牙接收到的数据
		Delay_ms(20);
		//USART2_Send(BLE_RX, 6);//将蓝牙接收到的数据再通过JDY--33发送出来观察，不需要可以注释
		//Delay_ms(500);

		if((BLE_RX[3] == 0xBA)&&(BLE_RX[4]==0xBE))//循迹模块
		{
			xj_flag =1;
			TIM_Cmd(TIM6, ENABLE);//启动定时器
			MOTOR_PWM_Out(2500,2500,2500,2500);
			Find();
		}
			if((BLE_RX[3] == 0xBB)&&(BLE_RX[4]==0xBF))//避障模块
		{	
			xj_flag=0;
			Car_Go();
			Distance = Wave_Start();//读取一次测距
		if(Distance <=25)//车子小于15cm的避障距离
		{
			wave_flag = 1;
		}
		
			if(wave_flag == 1)
		{
			wave_flag = 0;//清除标志位
			Car_Stop();//停车
			TIM_Cmd(TIM6, DISABLE);//关闭定时器
			Moto_A=0;Moto_B=0;Moto_C=0;Moto_D=0;
			para_A=0;para_B=0;para_C=0;para_D=0;
			
			//以下找出障碍物位置
			TIM_SetCompare1(TIM1,45);//舵机转到右端
			Duoji_Control(ON);
			Delay_ms(500);//
			Delay_ms(500);//
			Duoji_Control(OFF);
			juli_r=Wave_Start();//测距
			
			TIM_SetCompare1(TIM1,115);//舵机转到左端
			Duoji_Control(ON);
			Delay_ms(500);//
			Delay_ms(500);//
			Duoji_Control(OFF);			
			juli_l=Wave_Start();//测距
			
			TIM_SetCompare1(TIM1,75);//舵机转到中间
			Duoji_Control(ON);
			Delay_ms(500);//
			Delay_ms(500);//
			Duoji_Control(OFF);			
			juli_m=Wave_Start();//测距
			
			if((juli_l<=25)&&(juli_m>25)&&(juli_r>25))//障碍物在左边
			{
				MOTOR_PWM_Out(2700,2700,2700,2700);
				Car_Turn_Right();
				Delay_ms(700);//转约90度
				Delay_ms(700);
				Car_Go();//
				Moto_A=0;Moto_B=0;Moto_C=0;Moto_D=0;
				para_A=0;para_B=0;para_C=0;para_D=0;
				TIM2 -> CNT=30000;
				TIM3 -> CNT=30000;
				TIM4 -> CNT=30000;
				TIM5 -> CNT=30000;
				TIM_Cmd(TIM6, ENABLE);//启动定时器
			}
			else if((juli_l<=25)&&(juli_m<25)&&(juli_r>25))//障碍物在左边和中间
			{
				MOTOR_PWM_Out(2700,2700,2700,2700);
				Car_Turn_Right();
				Delay_ms(700);//转约90度
				Delay_ms(700);//转约90度
				Car_Go();//
				Moto_A=0;Moto_B=0;Moto_C=0;Moto_D=0;
				para_A=0;para_B=0;para_C=0;para_D=0;
				TIM2 -> CNT=30000;
				TIM3 -> CNT=30000;
				TIM4 -> CNT=30000;
				TIM5 -> CNT=30000;
				TIM_Cmd(TIM6, ENABLE);//启动定时器
			}
			else if((juli_l<=25)&&(juli_m<=25)&&(juli_r<=25))//障碍物在左边和中间和右边
			{
				MOTOR_PWM_Out(2700,2700,2700,2700);
				Car_Back();
				Delay_ms(700);//转约90度
				Car_Turn_Right();
				Delay_ms(700);//转约90度
				Delay_ms(700);
				Car_Go();//
				Moto_A=0;Moto_B=0;Moto_C=0;Moto_D=0;
				para_A=0;para_B=0;para_C=0;para_D=0;
				TIM2 -> CNT=30000;
				TIM3 -> CNT=30000;
				TIM4 -> CNT=30000;
				TIM5 -> CNT=30000;
				TIM_Cmd(TIM6, ENABLE);//启动定时器
			}
			else if((juli_l>25)&&(juli_m<=25)&&(juli_r>25))//障碍物在中间
			{
				MOTOR_PWM_Out(2700,2700,2700,2700);
				Car_Turn_Right();
				Delay_ms(700);//转约90度
				Delay_ms(700);
				Car_Go();//
				Moto_A=0;Moto_B=0;Moto_C=0;Moto_D=0;
				para_A=0;para_B=0;para_C=0;para_D=0;
				TIM2 -> CNT=30000;
				TIM3 -> CNT=30000;
				TIM4 -> CNT=30000;
				TIM5 -> CNT=30000;
				TIM_Cmd(TIM6, ENABLE);//启动定时器
			}
			else if((juli_l>25)&&(juli_m<=25)&&(juli_r<=25))//障碍物在中间和右端
			{
				MOTOR_PWM_Out(2700,2700,2700,2700);
				Car_Turn_Left();
				Delay_ms(700);//转约90度
				Delay_ms(700);
				Car_Go();//
				Moto_A=0;Moto_B=0;Moto_C=0;Moto_D=0;
				para_A=0;para_B=0;para_C=0;para_D=0;
				TIM2 -> CNT=30000;
				TIM3 -> CNT=30000;
				TIM4 -> CNT=30000;
				TIM5 -> CNT=30000;
				TIM_Cmd(TIM6, ENABLE);//启动定时器
			}
			else if((juli_l>25)&&(juli_m>25)&&(juli_r<=25))//障碍物在右端
			{
				MOTOR_PWM_Out(2700,2700,2700,2700);
				Car_Turn_Left();
				Delay_ms(700);//转约90度
				Delay_ms(700);//转约90度
				Car_Go();//
				Moto_A=0;Moto_B=0;Moto_C=0;Moto_D=0;
			  para_A=0;para_B=0;para_C=0;para_D=0;
				TIM2 -> CNT=30000;
				TIM3 -> CNT=30000;
				TIM4 -> CNT=30000;
				TIM5 -> CNT=30000;
				TIM_Cmd(TIM6, ENABLE);//启动定时器
			}	
		else 	
		{
			Car_Go();
			Moto_A=0;Moto_B=0;Moto_C=0;Moto_D=0;
			para_A=0;para_B=0;para_C=0;para_D=0;
			TIM2 -> CNT=30000;
			TIM3 -> CNT=30000;
			TIM4 -> CNT=30000;
			TIM5 -> CNT=30000;
			TIM_Cmd(TIM6, ENABLE);//启动定时器
		}			
		}
		}
		if((BLE_RX[3] == 0xB1)&&(BLE_RX[4]==0xB5))//加速
		{
			xj_flag=0;
			TIM_Cmd(TIM6, ENABLE);//启动定时器
			SetPoint = SetPoint + 10;
			BLE_RX[3] = 0x00;//清缓存
		}
		if((BLE_RX[3] == 0xB3)&&(BLE_RX[4]==0xB7))//减速
		{
			xj_flag=0;
			TIM_Cmd(TIM6, ENABLE);//启动定时器
			SetPoint = SetPoint - 10;
			BLE_RX[3] = 0x00;//清缓存
		}
		if((BLE_RX[3] == 0xB2)&&(BLE_RX[4]==0xB6))//前进
		{
			xj_flag=0;
			TIM_Cmd(TIM6, ENABLE);//启动定时器
			Moto_A=0;Moto_B=0;Moto_C=0;Moto_D=0;
			para_A=0;para_B=0;para_C=0;para_D=0;
			TIM2 -> CNT=30000;
			TIM3 -> CNT=30000;
			TIM4 -> CNT=30000;
			TIM5 -> CNT=30000;
			Car_Go();BLE_RX[3] = 0x00;//清缓存
		}
		if((BLE_RX[3] == 0xB4)&&(BLE_RX[4]==0xB8))//左转圈
		{
			xj_flag=0;
			TIM_Cmd(TIM6, ENABLE);//启动定时器
			Moto_A=0;Moto_B=0;Moto_C=0;Moto_D=0;
			para_A=0;para_B=0;para_C=0;para_D=0;
			TIM2 -> CNT=30000;
			TIM3 -> CNT=30000;
			TIM4 -> CNT=30000;
			TIM5 -> CNT=30000;
			Car_Turn_Left();
//		Delay_ms(700);//车无角度传感器，且由于车速不同，调整延时长短实现大概的转角 90度。
//		Delay_ms(700);
//		Car_Go();
			BLE_RX[3] = 0x00;//清缓存
		}
		if((BLE_RX[3] == 0xB5)&&(BLE_RX[4]==0xB9))//停车
		{
			xj_flag=0;
			TIM_Cmd(TIM6, ENABLE);//启动定时器
			Moto_A=0;Moto_B=0;Moto_C=0;Moto_D=0;
			para_A=0;para_B=0;para_C=0;para_D=0;
			TIM2 -> CNT=30000;
			TIM3 -> CNT=30000;
			TIM4 -> CNT=30000;
			TIM5 -> CNT=30000;
			Car_Stop();BLE_RX[3] = 0x00;//清缓存
		}
		if((BLE_RX[3] == 0xB6)&&(BLE_RX[4]==0xBA))//右转圈
		{		xj_flag=0;
				TIM_Cmd(TIM6, ENABLE);//启动定时器
				Moto_A=0;Moto_B=0;Moto_C=0;Moto_D=0;
				para_A=0;para_B=0;para_C=0;para_D=0;
				TIM2 -> CNT=30000;
				TIM3 -> CNT=30000;
				TIM4 -> CNT=30000;
				TIM5 -> CNT=30000;
				Car_Turn_Right();

				BLE_RX[3] = 0x00;//清缓存
		}
		if((BLE_RX[3] == 0xB8)&&(BLE_RX[4]==0xBC))//后退
		{
				xj_flag=0;
				TIM_Cmd(TIM6, ENABLE);//启动定时器
				Moto_A=0;Moto_B=0;Moto_C=0;Moto_D=0;
				para_A=0;para_B=0;para_C=0;para_D=0;
				TIM2 -> CNT=30000;
				TIM3 -> CNT=30000;
				TIM4 -> CNT=30000;
				TIM5 -> CNT=30000;
				Car_Back();
				BLE_RX[3] = 0x00;//清缓存
		} 
	}	
}
