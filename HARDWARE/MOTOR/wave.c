//���pwmͨ�� timer1 ������timer2�������������ز�����ʱ�䡣wave���������������ز�
//Ӳ�����ӣ�PB9----Echo���ջز�,PB8----Trig����������.

#include "bsp_sys.h"
#include "wave.h"
#include "delay.h"
u16 Distance=0;
u8 OB_L =0,OB_M=0,OB_R=0;//�ϰ���λ�ñ��

void TIM7_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  													
    NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*TIM_Period--1000   TIM_Prescaler--71 -->�ж�����Ϊ1ms*/
void TIM7_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7 , ENABLE);
    TIM_DeInit(TIM7);
    TIM_TimeBaseStructure.TIM_Period=65535;		 								/* �Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) */
    /* �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж� */
    TIM_TimeBaseStructure.TIM_Prescaler= (360 - 1);				                /* ʱ��Ԥ��Ƶ�� 72M/360 */
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 		                /* ������Ƶ */
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;                   /* ���ϼ���ģʽ */
    TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM7, TIM_FLAG_Update);							    		/* �������жϱ�־ */
    //TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);
    //TIM_Cmd(TIM7, ENABLE);																		/* ����ʱ�� */
    //RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7 , DISABLE);		/*�ȹرյȴ�ʹ��*/    
}
//�������˿ڳ�ʼ��
void Wave_IO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	       
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;					       //PB8��TRIG
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     //��Ϊ�������ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
	GPIO_Init(GPIOB, &GPIO_InitStructure);	                 //��ʼ������GPIO 	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				         //PB9��ECH0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		 //��Ϊ����
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	TIM7_NVIC_Configuration();//��ʱ����ʼ��
	TIM7_Configuration();			
}
//��ʼ��࣬����һ��>10us�����壬Ȼ��������صĸߵ�ƽʱ��
u16 Wave_Start(void)
{
	u16  Distance;
  Wave_ON();  		  //��>10US�ĸߵ�ƽ
  Delay_us(20);		                      //��ʱ20US
  Wave_OFF();
  while(!Wave_State());	             //�ȴ��ߵ�ƽ
  TIM_Cmd(TIM7, ENABLE);             //����ʱ��
  while(Wave_State());	             //�ȴ��͵�ƽ
  TIM_Cmd(TIM7, DISABLE);			                             //��ʱ��2ʧ��
  Distance=TIM_GetCounter(TIM7)*5*34/2000;								 //�������	����cm
  TIM_SetCounter(TIM7,0);	
  return Distance;
}
//�趨���Ͼ���25cm
void Wave_BZ(void)
{
		 Distance = Wave_Start(); 
	   if((Distance < 15) && (Distance != 0))//�趨���Ͼ���25cm
	   {
			Car_Stop();//ͣ��
			OB_M=1;//����м����ϰ���
			TIM_SetCompare1(TIM1,45);//���ת���Ҷ�
			Duoji_Control(ON);
			Delay_ms(500);//
			Delay_ms(500);//
			Duoji_Control(OFF);

			Distance = Wave_Start();//�����Ҷ��Ƿ����ϰ���
			if((Distance < 15) && (Distance != 0))//�����
			{
				Car_Stop();//ͣ��
				OB_R=1;//����Ҷ����ϰ���
			}
			else
			{
				OB_R=0;//����Ҷ�û���ϰ���
			}
			TIM_SetCompare1(TIM1,115);//���ת�����
			Duoji_Control(ON);
			Delay_ms(500);//
			Delay_ms(500);//
			Duoji_Control(OFF);

			Distance = Wave_Start();//��������Ƿ����ϰ���
			if((Distance < 15) && (Distance != 0))//�����
			{
				Car_Stop();//ͣ��
				OB_L=1;    //���������ϰ���
			}
			else
			{
				OB_L=0;
			}

			TIM_SetCompare1(TIM1,81);//ռ�ձ�5%��90��;//���ת���м�
			Duoji_Control(ON);
			Delay_ms(500);//
			Delay_ms(500);//
			Duoji_Control  (OFF);
	   }
	   else 
	   {
	   	Car_Go();
	   }
	   
	   if((OB_L==0)&&(OB_M==0)&&(OB_R==0))//û���ϰ���
	   {
	   		Car_Go();OB_L=0; OB_M=0; OB_R=0;

	   }
	   if((OB_L==0)&&(OB_M==1)&&(OB_R==0))//�м��ϰ���
	   {	
	   		OB_L=0; OB_M=0; OB_R=0;
				
	   		Car_Turn_Right();//���Һ�����
		    Delay_ms(500);
			  Delay_ms(200);//����1s����Ϊǰ��
				Car_Go();
	   }
	   if((OB_L==0)&&(OB_M==1)&&(OB_R==1))//�м���ұ��ϰ���
	   {
				OB_L=0; OB_M=0; OB_R=0;
				Car_Turn_Left();
				Delay_ms(500);
				Car_Go();
	   }
	   if((OB_L==1)&&(OB_M==1)&&(OB_R==0))//�м������ϰ���
	   {
				OB_L=0; OB_M=0; OB_R=0;
				Car_Turn_Right();
				Delay_ms(500);
				Car_Go();
	   }
	   if((OB_L==1)&&(OB_M==1)&&(OB_R==1))//�м������ұ߶����ϰ���
	   {
	   		OB_L=0; OB_M=0; OB_R=0;
				Car_Back();
				Delay_ms(500);
	   		Car_Turn_Right();
			  Delay_ms(500);
			  Delay_ms(500);//ת180�ȣ�����,��ȷ�������ʱ
			  Car_Go();
	   }
}
