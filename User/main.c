#include "bsp_sys.h"
#include "stdio.h"

unsigned char BLE_RX[64];
extern int SetPoint;
extern u8 wave_flag;
char xj_flag=0;
u8 juli_r;//�ұ߾���
u8 juli_l;
u8 juli_m;
extern int Moto_A,Moto_B,Moto_C,Moto_D;//PWM 
extern int para_A,para_B,para_C,para_D;//����
extern u16 Distance;

int main(void)
{	
	STM32_System_Init();//����ϵͳ������������������
	
	while (1)
	{
		
		USART2_Receive(BLE_RX, 6);//�������յ�������
		Delay_ms(20);
		//USART2_Send(BLE_RX, 6);//���������յ���������ͨ��JDY--33���ͳ����۲죬����Ҫ����ע��
		//Delay_ms(500);

		if((BLE_RX[3] == 0xBA)&&(BLE_RX[4]==0xBE))//ѭ��ģ��
		{
			xj_flag =1;
			TIM_Cmd(TIM6, ENABLE);//������ʱ��
			MOTOR_PWM_Out(2500,2500,2500,2500);
			Find();
		}
			if((BLE_RX[3] == 0xBB)&&(BLE_RX[4]==0xBF))//����ģ��
		{	
			xj_flag=0;
			Car_Go();
			Distance = Wave_Start();//��ȡһ�β��
		if(Distance <=25)//����С��15cm�ı��Ͼ���
		{
			wave_flag = 1;
		}
		
			if(wave_flag == 1)
		{
			wave_flag = 0;//�����־λ
			Car_Stop();//ͣ��
			TIM_Cmd(TIM6, DISABLE);//�رն�ʱ��
			Moto_A=0;Moto_B=0;Moto_C=0;Moto_D=0;
			para_A=0;para_B=0;para_C=0;para_D=0;
			
			//�����ҳ��ϰ���λ��
			TIM_SetCompare1(TIM1,45);//���ת���Ҷ�
			Duoji_Control(ON);
			Delay_ms(500);//
			Delay_ms(500);//
			Duoji_Control(OFF);
			juli_r=Wave_Start();//���
			
			TIM_SetCompare1(TIM1,115);//���ת�����
			Duoji_Control(ON);
			Delay_ms(500);//
			Delay_ms(500);//
			Duoji_Control(OFF);			
			juli_l=Wave_Start();//���
			
			TIM_SetCompare1(TIM1,75);//���ת���м�
			Duoji_Control(ON);
			Delay_ms(500);//
			Delay_ms(500);//
			Duoji_Control(OFF);			
			juli_m=Wave_Start();//���
			
			if((juli_l<=25)&&(juli_m>25)&&(juli_r>25))//�ϰ��������
			{
				MOTOR_PWM_Out(2700,2700,2700,2700);
				Car_Turn_Right();
				Delay_ms(700);//תԼ90��
				Delay_ms(700);
				Car_Go();//
				Moto_A=0;Moto_B=0;Moto_C=0;Moto_D=0;
				para_A=0;para_B=0;para_C=0;para_D=0;
				TIM2 -> CNT=30000;
				TIM3 -> CNT=30000;
				TIM4 -> CNT=30000;
				TIM5 -> CNT=30000;
				TIM_Cmd(TIM6, ENABLE);//������ʱ��
			}
			else if((juli_l<=25)&&(juli_m<25)&&(juli_r>25))//�ϰ�������ߺ��м�
			{
				MOTOR_PWM_Out(2700,2700,2700,2700);
				Car_Turn_Right();
				Delay_ms(700);//תԼ90��
				Delay_ms(700);//תԼ90��
				Car_Go();//
				Moto_A=0;Moto_B=0;Moto_C=0;Moto_D=0;
				para_A=0;para_B=0;para_C=0;para_D=0;
				TIM2 -> CNT=30000;
				TIM3 -> CNT=30000;
				TIM4 -> CNT=30000;
				TIM5 -> CNT=30000;
				TIM_Cmd(TIM6, ENABLE);//������ʱ��
			}
			else if((juli_l<=25)&&(juli_m<=25)&&(juli_r<=25))//�ϰ�������ߺ��м���ұ�
			{
				MOTOR_PWM_Out(2700,2700,2700,2700);
				Car_Back();
				Delay_ms(700);//תԼ90��
				Car_Turn_Right();
				Delay_ms(700);//תԼ90��
				Delay_ms(700);
				Car_Go();//
				Moto_A=0;Moto_B=0;Moto_C=0;Moto_D=0;
				para_A=0;para_B=0;para_C=0;para_D=0;
				TIM2 -> CNT=30000;
				TIM3 -> CNT=30000;
				TIM4 -> CNT=30000;
				TIM5 -> CNT=30000;
				TIM_Cmd(TIM6, ENABLE);//������ʱ��
			}
			else if((juli_l>25)&&(juli_m<=25)&&(juli_r>25))//�ϰ������м�
			{
				MOTOR_PWM_Out(2700,2700,2700,2700);
				Car_Turn_Right();
				Delay_ms(700);//תԼ90��
				Delay_ms(700);
				Car_Go();//
				Moto_A=0;Moto_B=0;Moto_C=0;Moto_D=0;
				para_A=0;para_B=0;para_C=0;para_D=0;
				TIM2 -> CNT=30000;
				TIM3 -> CNT=30000;
				TIM4 -> CNT=30000;
				TIM5 -> CNT=30000;
				TIM_Cmd(TIM6, ENABLE);//������ʱ��
			}
			else if((juli_l>25)&&(juli_m<=25)&&(juli_r<=25))//�ϰ������м���Ҷ�
			{
				MOTOR_PWM_Out(2700,2700,2700,2700);
				Car_Turn_Left();
				Delay_ms(700);//תԼ90��
				Delay_ms(700);
				Car_Go();//
				Moto_A=0;Moto_B=0;Moto_C=0;Moto_D=0;
				para_A=0;para_B=0;para_C=0;para_D=0;
				TIM2 -> CNT=30000;
				TIM3 -> CNT=30000;
				TIM4 -> CNT=30000;
				TIM5 -> CNT=30000;
				TIM_Cmd(TIM6, ENABLE);//������ʱ��
			}
			else if((juli_l>25)&&(juli_m>25)&&(juli_r<=25))//�ϰ������Ҷ�
			{
				MOTOR_PWM_Out(2700,2700,2700,2700);
				Car_Turn_Left();
				Delay_ms(700);//תԼ90��
				Delay_ms(700);//תԼ90��
				Car_Go();//
				Moto_A=0;Moto_B=0;Moto_C=0;Moto_D=0;
			  para_A=0;para_B=0;para_C=0;para_D=0;
				TIM2 -> CNT=30000;
				TIM3 -> CNT=30000;
				TIM4 -> CNT=30000;
				TIM5 -> CNT=30000;
				TIM_Cmd(TIM6, ENABLE);//������ʱ��
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
			TIM_Cmd(TIM6, ENABLE);//������ʱ��
		}			
		}
		}
		if((BLE_RX[3] == 0xB1)&&(BLE_RX[4]==0xB5))//����
		{
			xj_flag=0;
			TIM_Cmd(TIM6, ENABLE);//������ʱ��
			SetPoint = SetPoint + 10;
			BLE_RX[3] = 0x00;//�建��
		}
		if((BLE_RX[3] == 0xB3)&&(BLE_RX[4]==0xB7))//����
		{
			xj_flag=0;
			TIM_Cmd(TIM6, ENABLE);//������ʱ��
			SetPoint = SetPoint - 10;
			BLE_RX[3] = 0x00;//�建��
		}
		if((BLE_RX[3] == 0xB2)&&(BLE_RX[4]==0xB6))//ǰ��
		{
			xj_flag=0;
			TIM_Cmd(TIM6, ENABLE);//������ʱ��
			Moto_A=0;Moto_B=0;Moto_C=0;Moto_D=0;
			para_A=0;para_B=0;para_C=0;para_D=0;
			TIM2 -> CNT=30000;
			TIM3 -> CNT=30000;
			TIM4 -> CNT=30000;
			TIM5 -> CNT=30000;
			Car_Go();BLE_RX[3] = 0x00;//�建��
		}
		if((BLE_RX[3] == 0xB4)&&(BLE_RX[4]==0xB8))//��תȦ
		{
			xj_flag=0;
			TIM_Cmd(TIM6, ENABLE);//������ʱ��
			Moto_A=0;Moto_B=0;Moto_C=0;Moto_D=0;
			para_A=0;para_B=0;para_C=0;para_D=0;
			TIM2 -> CNT=30000;
			TIM3 -> CNT=30000;
			TIM4 -> CNT=30000;
			TIM5 -> CNT=30000;
			Car_Turn_Left();
//		Delay_ms(700);//���޽Ƕȴ������������ڳ��ٲ�ͬ��������ʱ����ʵ�ִ�ŵ�ת�� 90�ȡ�
//		Delay_ms(700);
//		Car_Go();
			BLE_RX[3] = 0x00;//�建��
		}
		if((BLE_RX[3] == 0xB5)&&(BLE_RX[4]==0xB9))//ͣ��
		{
			xj_flag=0;
			TIM_Cmd(TIM6, ENABLE);//������ʱ��
			Moto_A=0;Moto_B=0;Moto_C=0;Moto_D=0;
			para_A=0;para_B=0;para_C=0;para_D=0;
			TIM2 -> CNT=30000;
			TIM3 -> CNT=30000;
			TIM4 -> CNT=30000;
			TIM5 -> CNT=30000;
			Car_Stop();BLE_RX[3] = 0x00;//�建��
		}
		if((BLE_RX[3] == 0xB6)&&(BLE_RX[4]==0xBA))//��תȦ
		{		xj_flag=0;
				TIM_Cmd(TIM6, ENABLE);//������ʱ��
				Moto_A=0;Moto_B=0;Moto_C=0;Moto_D=0;
				para_A=0;para_B=0;para_C=0;para_D=0;
				TIM2 -> CNT=30000;
				TIM3 -> CNT=30000;
				TIM4 -> CNT=30000;
				TIM5 -> CNT=30000;
				Car_Turn_Right();

				BLE_RX[3] = 0x00;//�建��
		}
		if((BLE_RX[3] == 0xB8)&&(BLE_RX[4]==0xBC))//����
		{
				xj_flag=0;
				TIM_Cmd(TIM6, ENABLE);//������ʱ��
				Moto_A=0;Moto_B=0;Moto_C=0;Moto_D=0;
				para_A=0;para_B=0;para_C=0;para_D=0;
				TIM2 -> CNT=30000;
				TIM3 -> CNT=30000;
				TIM4 -> CNT=30000;
				TIM5 -> CNT=30000;
				Car_Back();
				BLE_RX[3] = 0x00;//�建��
		} 
	}	
}
