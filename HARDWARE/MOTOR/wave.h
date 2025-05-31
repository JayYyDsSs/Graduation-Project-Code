#ifndef __WAVE_H
#define __WAVE_H

#include "bsp_sys.h"
#include "stm32f10x.h"
#define Wave_ON()  GPIO_SetBits(GPIOB,GPIO_Pin_8)
#define Wave_OFF() GPIO_ResetBits(GPIOB,GPIO_Pin_8)
#define Wave_State()  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)

void Wave_IO_Init(void);
u16 Wave_Start(void);
void Wave_BZ(void);;

#endif
