#include "car.h"
#include "pid.h"
#include "bsp_sys.h"

int Encoder_A,Encoder_B,Encoder_C,Encoder_D;  //������������
int Moto_A,Moto_B,Moto_C,Moto_D;//PWM 
int para_A,para_B,para_C,para_D;//����

//������ú���Ҫ
int SetPoint=50;//����Ŀ��ֵ��λRPM�����ת�������ٶ�  = setopint*�����ܳ� = setpoint*3.14*0.065(����ֱ��65mm) ��λ����m/min  һ��Ҫ���������ת�ٺ����ٵĹ�ϵ

//ʹ�ü��ٱ���1��120�ļ����䡣
//6240=13*4*120������������13�ߣ�STM32������ģʽ 4��Ƶ��������1��120
#define SetPointA SetPoint*6240/1200                 //����ɱ���������������Ϊ����pid���Ƶ��Ǳ���������������
#define SetPointB SetPoint*6240/1200                 //����ɱ���������������Ϊ����pid���Ƶ��Ǳ���������������
#define SetPointC SetPoint*6240/1200                 //����ɱ���������������Ϊ����pid���Ƶ��Ǳ���������������
#define SetPointD SetPoint*6240/1200                 //����ɱ���������������Ϊ����pid���Ƶ��Ǳ���������������

//���ֱ���
u32 temp1,temp2,temp3,temp4;
float sudu;
char set_speed[5];//������ʾС��
char speed[5];//������ʾС��
extern  char xj_flag;
u8 speed11[5];//������ʾС��
extern u16 Distance;
u8 wave_flag=0;//�ϰ����־


//Time6��ʱ��1�жϷ�����
//50ms��ʱ

void TIM6_IRQHandler(void)
{
	if(TIM_GetFlagStatus(TIM6, TIM_IT_Update) != RESET) //ʱ�䵽��
	{
		TIM_ClearITPendingBit(TIM6, TIM_FLAG_Update);     //���ж�
		
			
			if(xj_flag == 1)
			{

		
		  Encoder_A=Read_Encoder(5)-30000;                   //��ȡ������ 
			Encoder_B=Read_Encoder(2)-30000;                  //��ȡ������
			Encoder_C=Read_Encoder(3)-30000;                   //��ȡ������ 
			Encoder_D=Read_Encoder(4)-30000;                  //��ȡ������
			//С�����ƶ��ٶȣ����������ٶ�
			sudu = (Encoder_A+Encoder_B+Encoder_C+Encoder_D)/4*1200/6240 * 0.065*3.1415;//���㳵�٣����ֺ������ٶȺͳ���2 ��λ m/min
			sprintf(speed,"%2.2f",sudu);
		  OLED_ShowString(48,0, speed,16);  //OLED��ʾ����
			
			if(Encoder_A<0)//��������ת��
			{
				Encoder_A = -Encoder_A;
			}
				if(Encoder_B<0)
			{
				Encoder_B = -Encoder_B;
			}
			if(Encoder_C<0)//��������ת��
			{
				Encoder_C = -Encoder_C;
			}
				if(Encoder_D<0)
			{
				Encoder_D = -Encoder_D;
			}
			//��ʾ���ֺ����ֵ����ת�� ��λRPM 
  		temp1 = Encoder_A*1200/6240;
  		OLED_ShowNum(16,2,temp1,3,12);      //A��ʵ�ʼ��������ת��  ��λRPM
  		temp2 = Encoder_B*1200/6240;
			OLED_ShowNum(80,2,temp2,3,12);      //B��ʵ�ʼ��������ת��  ��λRPM
  		temp4 = Encoder_D*1200/6240;
  		OLED_ShowNum(16,3,temp4,3,12);      //D��ʵ�ʼ��������ת��  ��λRPM
			temp3 = Encoder_C*1200/6240;
			OLED_ShowNum(80,3,temp3,3,12);      //C��ʵ�ʼ��������ת��  ��λRPM
			OLED_ShowNum(48,6,SetPoint,3,12);   //��ʾ�趨�ĳ���ת�� ��λRPM
		}

	else
	{
			Encoder_A=Read_Encoder(5)-30000;                   //��ȡ������ 
			Encoder_B=Read_Encoder(2)-30000;                  //��ȡ������
			Encoder_C=Read_Encoder(3)-30000;                   //��ȡ������ 
			Encoder_D=Read_Encoder(4)-30000;                  //��ȡ������
			//С�����ƶ��ٶȣ����������ٶ�
			sudu = (Encoder_A+Encoder_B+Encoder_C+Encoder_D)/4*1200/6240 * 0.065*3.1415;//���㳵�٣����ֺ������ٶȺͳ���2 ��λ m/min
			sprintf(speed,"%2.2f",sudu);
		  OLED_ShowString(48,0, speed,16);  //OLED��ʾ����
			
			if(Encoder_A<0)//��������ת��
			{
				Encoder_A = -Encoder_A;
			}
				if(Encoder_B<0)
			{
				Encoder_B = -Encoder_B;
			}
			if(Encoder_C<0)//��������ת��
			{
				Encoder_C = -Encoder_C;
			}
				if(Encoder_D<0)
			{
				Encoder_D = -Encoder_D;
			}
			para_A=PID_Calc_A(Encoder_A,SetPointA);	  //A����������õ�����ʽPID��������ֵ 
		  para_B=PID_Calc_B(Encoder_B,SetPointB);	  //B����������õ�����ʽPID��������ֵ 
			para_C=PID_Calc_C(Encoder_C,SetPointC);	  //C����������õ�����ʽPID��������ֵ 
		  para_D=PID_Calc_D(Encoder_D,SetPointD);	  //D����������õ�����ʽPID��������ֵ 
			if((para_A<-3)||(para_A>3))                     //���� PID ��������������СʱƵ�����������𵴡�
			{
				Moto_A +=para_A;  
			}   
			if((para_B<-3)||(para_B>3))                     //���� PID ��������������СʱƵ�����������𵴡�
			{
				Moto_B +=para_B;  
			}		
			if((para_C<-3)||(para_C>3))                     //���� PID ��������������СʱƵ�����������𵴡�
			{
				Moto_C +=para_C;  
			}   
			if((para_D<-3)||(para_D>3))                     //���� PID ��������������СʱƵ�����������𵴡�
			{
				Moto_D +=para_D;  
			}
       
			//PWM����޷�
			if(Moto_A > 3500) Moto_A = 3500; else if(Moto_A < 0) Moto_A = 0;
      if(Moto_B > 3500) Moto_B = 3500; else if(Moto_B < 0) Moto_B = 0;
      if(Moto_C > 3500) Moto_C = 3500; else if(Moto_C < 0) Moto_C = 0;
      if(Moto_D > 3500) Moto_D = 3500; else if(Moto_D < 0) Moto_D = 0;

			TIM8->CCR1=Moto_A;  //����pwm
			TIM8->CCR2=Moto_B; //����pwm
			TIM8->CCR3=Moto_C;  //����pwm
			TIM8->CCR4=Moto_D; //����pwm
			//��ʾpid����
			showPID();
			//��ʾ���ֺ����ֵ����ת�� ��λRPM 
  		temp1 = Encoder_A*1200/6240;
  		OLED_ShowNum(16,2,temp1,3,12);      //A��ʵ�ʼ��������ת��  ��λRPM
  		temp2 = Encoder_B*1200/6240;
			OLED_ShowNum(80,2,temp2,3,12);      //B��ʵ�ʼ��������ת��  ��λRPM
  		temp4 = Encoder_D*1200/6240;
  		OLED_ShowNum(16,3,temp4,3,12);      //C��ʵ�ʼ��������ת��  ��λRPM
			temp3 = Encoder_C*1200/6240;
			OLED_ShowNum(80,3,temp3,3,12);      //D��ʵ�ʼ��������ת��  ��λRPM
			OLED_ShowNum(48,6,SetPoint,3,12);   //��ʾ�趨�ĳ���ת�� ��λRPM
	}
	}
}
