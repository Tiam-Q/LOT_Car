#ifndef __SYSTICK_H
#define __SYSTICK_H


#include "stm32f10x.h"


//void SysTick_Init(void);
//void Delay_us(__IO u32 nTime);         // ��λ1us
//#define Delay_ms(x) Delay_us(1000*x)	 //��λms

void delay_Init(void);
void delay_us(u32 nTimer);
void delay_ms(u32 nTimer);


#endif /* __SYSTICK_H */
