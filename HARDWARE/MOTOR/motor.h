#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f10x.h"

#define GO    0//定义电机状态 前进
#define BACK  1//后退
#define STOP  2//停车

//配置前部电机驱动的四个引脚
#define MOTOR_CLK      RCC_APB2Periph_GPIOC
#define MOTOR_PORT     GPIOC
#define MOTOR_A1       GPIO_Pin_0  //A轮
#define MOTOR_A2       GPIO_Pin_1  
#define MOTOR_B1       GPIO_Pin_2  //B轮
#define MOTOR_B2       GPIO_Pin_3
#define MOTOR_C1       GPIO_Pin_11 //C轮
#define MOTOR_C2       GPIO_Pin_10
#define MOTOR_D1       GPIO_Pin_12 //D轮

//配置后部电机驱动的四个引脚
#define MOTOR_CLK2     RCC_APB2Periph_GPIOD
#define MOTOR_PORT2    GPIOD
#define MOTOR_D2       GPIO_Pin_2   //PD2是D轮第二个控制口

void MOTOR_GPIO_Init(void);
void MOTOR_A(char state);
void MOTOR_B(char state);
void MOTOR_C(char state);
void MOTOR_D(char state);

void Car_Go(void);
void Car_Back(void);									
void Car_Turn_Right(void);
void Car_Turn_Left(void);
void Car_Stop(void);
void Car_Left(void);
void Car_Right(void);

#endif
