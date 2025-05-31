#include "car.h"
#include "pid.h"
#include "bsp_sys.h"

int Encoder_A,Encoder_B,Encoder_C,Encoder_D;  //编码器脉冲数
int Moto_A,Moto_B,Moto_C,Moto_D;//PWM 
int para_A,para_B,para_C,para_D;//增量

//这个设置很重要
int SetPoint=50;//设置目标值单位RPM，如果转换成线速度  = setopint*轮子周长 = setpoint*3.14*0.065(轮子直径65mm) 单位就是m/min  一定要搞清楚车轮转速和线速的关系

//使用减速比是1：120的减速箱。
//6240=13*4*120：霍尔编码器13线，STM32编码器模式 4倍频，减速箱1：120
#define SetPointA SetPoint*6240/1200                 //换算成编码器脉冲数，因为最终pid控制的是编码器的脉冲数量
#define SetPointB SetPoint*6240/1200                 //换算成编码器脉冲数，因为最终pid控制的是编码器的脉冲数量
#define SetPointC SetPoint*6240/1200                 //换算成编码器脉冲数，因为最终pid控制的是编码器的脉冲数量
#define SetPointD SetPoint*6240/1200                 //换算成编码器脉冲数，因为最终pid控制的是编码器的脉冲数量

//各种变量
u32 temp1,temp2,temp3,temp4;
float sudu;
char set_speed[5];//车速显示小数
char speed[5];//车速显示小数
extern  char xj_flag;
u8 speed11[5];//车速显示小数
extern u16 Distance;
u8 wave_flag=0;//障碍物标志


//Time6定时器1中断服务函数
//50ms定时

void TIM6_IRQHandler(void)
{
	if(TIM_GetFlagStatus(TIM6, TIM_IT_Update) != RESET) //时间到了
	{
		TIM_ClearITPendingBit(TIM6, TIM_FLAG_Update);     //清中断
		
			
			if(xj_flag == 1)
			{

		
		  Encoder_A=Read_Encoder(5)-30000;                   //读取编码器 
			Encoder_B=Read_Encoder(2)-30000;                  //读取编码器
			Encoder_C=Read_Encoder(3)-30000;                   //读取编码器 
			Encoder_D=Read_Encoder(4)-30000;                  //读取编码器
			//小车的移动速度，即轮子线速度
			sudu = (Encoder_A+Encoder_B+Encoder_C+Encoder_D)/4*1200/6240 * 0.065*3.1415;//计算车速，左轮和右轮速度和除以2 单位 m/min
			sprintf(speed,"%2.2f",sudu);
		  OLED_ShowString(48,0, speed,16);  //OLED显示车速
			
			if(Encoder_A<0)//如果电机反转了
			{
				Encoder_A = -Encoder_A;
			}
				if(Encoder_B<0)
			{
				Encoder_B = -Encoder_B;
			}
			if(Encoder_C<0)//如果电机反转了
			{
				Encoder_C = -Encoder_C;
			}
				if(Encoder_D<0)
			{
				Encoder_D = -Encoder_D;
			}
			//显示左轮和右轮的输出转速 单位RPM 
  		temp1 = Encoder_A*1200/6240;
  		OLED_ShowNum(16,2,temp1,3,12);      //A轮实际减速箱输出转速  单位RPM
  		temp2 = Encoder_B*1200/6240;
			OLED_ShowNum(80,2,temp2,3,12);      //B轮实际减速箱输出转速  单位RPM
  		temp4 = Encoder_D*1200/6240;
  		OLED_ShowNum(16,3,temp4,3,12);      //D轮实际减速箱输出转速  单位RPM
			temp3 = Encoder_C*1200/6240;
			OLED_ShowNum(80,3,temp3,3,12);      //C轮实际减速箱输出转速  单位RPM
			OLED_ShowNum(48,6,SetPoint,3,12);   //显示设定的车轮转速 单位RPM
		}

	else
	{
			Encoder_A=Read_Encoder(5)-30000;                   //读取编码器 
			Encoder_B=Read_Encoder(2)-30000;                  //读取编码器
			Encoder_C=Read_Encoder(3)-30000;                   //读取编码器 
			Encoder_D=Read_Encoder(4)-30000;                  //读取编码器
			//小车的移动速度，即轮子线速度
			sudu = (Encoder_A+Encoder_B+Encoder_C+Encoder_D)/4*1200/6240 * 0.065*3.1415;//计算车速，左轮和右轮速度和除以2 单位 m/min
			sprintf(speed,"%2.2f",sudu);
		  OLED_ShowString(48,0, speed,16);  //OLED显示车速
			
			if(Encoder_A<0)//如果电机反转了
			{
				Encoder_A = -Encoder_A;
			}
				if(Encoder_B<0)
			{
				Encoder_B = -Encoder_B;
			}
			if(Encoder_C<0)//如果电机反转了
			{
				Encoder_C = -Encoder_C;
			}
				if(Encoder_D<0)
			{
				Encoder_D = -Encoder_D;
			}
			para_A=PID_Calc_A(Encoder_A,SetPointA);	  //A电机，计数得到增量式PID的增量数值 
		  para_B=PID_Calc_B(Encoder_B,SetPointB);	  //B电机，计数得到增量式PID的增量数值 
			para_C=PID_Calc_C(Encoder_C,SetPointC);	  //C电机，计数得到增量式PID的增量数值 
		  para_D=PID_Calc_D(Encoder_D,SetPointD);	  //D电机，计数得到增量式PID的增量数值 
			if((para_A<-3)||(para_A>3))                     //不做 PID 调整，避免误差较小时频繁调节引起震荡。
			{
				Moto_A +=para_A;  
			}   
			if((para_B<-3)||(para_B>3))                     //不做 PID 调整，避免误差较小时频繁调节引起震荡。
			{
				Moto_B +=para_B;  
			}		
			if((para_C<-3)||(para_C>3))                     //不做 PID 调整，避免误差较小时频繁调节引起震荡。
			{
				Moto_C +=para_C;  
			}   
			if((para_D<-3)||(para_D>3))                     //不做 PID 调整，避免误差较小时频繁调节引起震荡。
			{
				Moto_D +=para_D;  
			}
       
			//PWM输出限幅
			if(Moto_A > 3500) Moto_A = 3500; else if(Moto_A < 0) Moto_A = 0;
      if(Moto_B > 3500) Moto_B = 3500; else if(Moto_B < 0) Moto_B = 0;
      if(Moto_C > 3500) Moto_C = 3500; else if(Moto_C < 0) Moto_C = 0;
      if(Moto_D > 3500) Moto_D = 3500; else if(Moto_D < 0) Moto_D = 0;

			TIM8->CCR1=Moto_A;  //更新pwm
			TIM8->CCR2=Moto_B; //更新pwm
			TIM8->CCR3=Moto_C;  //更新pwm
			TIM8->CCR4=Moto_D; //更新pwm
			//显示pid参数
			showPID();
			//显示左轮和右轮的输出转速 单位RPM 
  		temp1 = Encoder_A*1200/6240;
  		OLED_ShowNum(16,2,temp1,3,12);      //A轮实际减速箱输出转速  单位RPM
  		temp2 = Encoder_B*1200/6240;
			OLED_ShowNum(80,2,temp2,3,12);      //B轮实际减速箱输出转速  单位RPM
  		temp4 = Encoder_D*1200/6240;
  		OLED_ShowNum(16,3,temp4,3,12);      //C轮实际减速箱输出转速  单位RPM
			temp3 = Encoder_C*1200/6240;
			OLED_ShowNum(80,3,temp3,3,12);      //D轮实际减速箱输出转速  单位RPM
			OLED_ShowNum(48,6,SetPoint,3,12);   //显示设定的车轮转速 单位RPM
	}
	}
}
