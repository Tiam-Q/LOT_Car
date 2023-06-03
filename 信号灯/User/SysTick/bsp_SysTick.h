#ifndef __SYSTICK_H
#define __SYSTICK_H


#include "stm32f10x.h"


void delay_Init(void);
void delay_us(u32 nTimer);
void delay_ms(u32 nTimer);


#endif /* __SYSTICK_H */
