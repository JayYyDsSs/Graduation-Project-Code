#ifndef __SERVO_H
#define __SERVO_H

#include "stm32f10x.h"

#define ON 0
#define OFF 1
void TIM1_PWM_Init(u16 arr,u16 psc);
void Duoji_Control(char state);
void Duoji_PWM(u16 ch1_val);

#endif
