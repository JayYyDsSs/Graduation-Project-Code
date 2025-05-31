#include "find.h"
#include "bsp_timer.h"
#include "bsp_sys.h"
#include "delay.h"

//Ѱ�����������ҵ����Դ�O1 O2 O3 O4 
//Ӳ������:O1-PA4��O2-PA5��O3-PA6��O4-PA7.
//Ҫ��ʼ��Ϊ����ģʽ
void Find_IO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	//����GPIOʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5| GPIO_Pin_6 | GPIO_Pin_7;//ѡ��IO�˿�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;//����Ϊ��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//����GPIO_InitStructure��ָ���Ĳ�����ʼ������GPIOD�Ĵ���

} 

//ѭ��ģ��:��������ߵ�ƽ1�����ߵ͵�ƽ0��
//ѭ��·�棺��ɫ·���ɫ�����ߣ���Ѱ���ߡ�
void Find(void)
{
	//O4 ��ɫ��O3 ��ɫ��O2 ��ɫ��O1 ��ɫ����ѭ���������м��ں����ϣ�ǰ��
	if((Find_O4 == 0)&&(Find_O3 == 1)&&(Find_O2 == 1)&&(Find_O1 == 0))
	{
			MOTOR_PWM_Out(3000,3000,3000,3000);
			Car_Go();
	}
	//O4 ��ɫ��O3 ��ɫ��O2 ��ɫ��O1 ��ɫ����ѭ��������ȫ�����ϣ�ǰ��
	else if((Find_O4 == 0)&&(Find_O3 == 	0)&&(Find_O2 == 0)&&(Find_O1 == 0))
	{	MOTOR_PWM_Out(3000,3000,3000,3000);
			Car_Go();
	}
	//O4 ��ɫ��O3 ��ɫ��O2 ��ɫ��O1 ��ɫ��С��ƫ��
	//Ӧ����ת������ǰ������	�������ּ������ּ���
	else if((Find_O4 == 0)&&(Find_O3 == 0)&&(Find_O2 == 1)&&(Find_O1 == 0))// O2Ѱ������
	{
			MOTOR_PWM_Out(3000,0,0,3000);
			Car_Go();
			//Car_Turn_Right();
	}
	//O4 ��ɫ��O3 ��ɫ��O2 ��ɫ��O1 ��ɫ��С��ƫƫ��
	//Ӧ����ת������ǰ������	�������ּ������ּ���
	else if((Find_O4 == 0)&&(Find_O3 == 0)&&(Find_O2 == 1)&&(Find_O1 == 1))// O2 O1Ѱ������
	{
			MOTOR_PWM_Out(3000,3000,3000,3000);
			Car_Turn_Right();
			Delay_ms(200);
			while(Find_O3 != 1);//�ȴ�С��ת����
			Car_Go();
			Delay_ms(50);
	}
	//O4 ��ɫ��O3 �ڣ�O2 ��ɫ��O1 ��ɫ��С��ƫƫ��L��·����
	//Ӧ����ת������ǰ������	�������ּ������ּ���
	else if((Find_O4 == 0)&&(Find_O3 == 1)&&(Find_O2 == 1)&&(Find_O1 == 1))
	{	
			MOTOR_PWM_Out(3000,3000,3000,3000);
			Car_Turn_Right();
			Delay_ms(50);
			while(Find_O3 != 1);//�ȴ�С��ת����
			Car_Go();
			Delay_ms(50);
	}
	//O4 ��ɫ��O3 ��ɫ��O2 ��ɫ��O1 ��ɫ��С��ƫƫƫ��
	//Ӧ����ת������ǰ������	�������ּ������ּ���
	else if((Find_O4 == 0)&&(Find_O3 == 0)&&(Find_O2 == 0)&&(Find_O1 == 1))
	{		
			MOTOR_PWM_Out(3000,3000,3000,3000);
			Car_Turn_Right();
			while(Find_O3 != 1);//�ȴ�С��ת����
			Car_Go();
			Delay_ms(50);
	}
	//O4 ��ɫ��O3 ��ɫ��O2 ��ɫ��O1 ��ɫ��С��ƫ��
	//Ӧ����ת������ǰ������	�������ּ������ּ���
	else if((Find_O4 == 0)&&(Find_O3 == 1)&&(Find_O2 == 0)&&(Find_O1 == 0))
	{
		MOTOR_PWM_Out(3000,0,0,3000);
		Car_Go();
	}
	//O4 ��ɫ��O3 ��ɫ��O2 ��ɫ��O1 ��ɫ��С��ƫƫ��
	//Ӧ����ת������ǰ������	�������ּ������ּ���
	else if((Find_O4 == 1)&&(Find_O3 == 1)&&(Find_O2 == 0)&&(Find_O1 == 0))// O4Ѱ������
	{
		MOTOR_PWM_Out(3000,3000,3000,3000);
		Car_Turn_Left();
			Delay_ms(200);
			while(Find_O2 != 1);//�ȴ�С��ת����
			Car_Go();
			Delay_ms(50);	
	}
	//O4 ��ɫ��O3 ��ɫ��O2 �ڣ�O1 ��ɫ��С��ƫƫ�ң�L��·����
	//Ӧ����ת������ǰ������	�������ּ������ּ���
	else if((Find_O4 == 1)&&(Find_O3 == 1)&&(Find_O2 == 1)&&(Find_O1 == 0))
	{
		MOTOR_PWM_Out(3000,3000,3000,3000);
		Car_Turn_Left();
			Delay_ms(50);
			while(Find_O2 != 1);//�ȴ�С��ת����
			Car_Go();
			Delay_ms(50);
	}
	//O4 ��ɫ��O3 ��ɫ��O2 ��ɫ��O1 ��ɫ��С��ƫƫ��
	//Ӧ����ת������ǰ������	�������ּ������ּ���
		else if((Find_O4 == 1)&&(Find_O3 == 0)&&(Find_O2 == 0)&&(Find_O1 == 0))
	{
		MOTOR_PWM_Out(3000,3000,3000,3000);
			Car_Turn_Left();
			while(Find_O2 != 1);//�ȴ�С��ת����
			Car_Go();
			Delay_ms(50);
	}
/*ͣ��
			else if((Find_O4 == 0)&&(Find_O3 == 0)&&(Find_O2 == 0)&&(Find_O1 == 0))
	{
		MOTOR_PWM_Out(3000,3000,3000,3000);
		Car_Stop();
	}
*/
}
