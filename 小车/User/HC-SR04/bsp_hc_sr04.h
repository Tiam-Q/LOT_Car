#ifndef __ULTRASONIC_H
#define __ULTRASONIC_H

#include "stm32f10x.h"

//端口宏定义
#define HCSR04_PORT                       GPIOB
#define HCSR04_CLK                        RCC_APB2Periph_GPIOB
#define HCSR04_CLK_GPIO_CLK_FUNCTION      RCC_APB2PeriphClockCmd


#define UL_TIM                    TIM3
#define UL_TIM_CLK                RCC_APB1Periph_TIM3
#define UL_TIM_CLK_FUNCTION       RCC_APB1PeriphClockCmd

#define HCSR04_TRIG               GPIO_Pin_1
#define HCSR04_ECHO               GPIO_Pin_0

#define TRIG_SET                  GPIO_SetBits(HCSR04_PORT, HCSR04_TRIG);
#define TRIG_RESET                GPIO_ResetBits(HCSR04_PORT, HCSR04_TRIG);

#define ECHO_RECEIVE              GPIO_ReadInputDataBit(HCSR04_PORT,HCSR04_ECHO)


#define UL_TIM_MAX_COUNT          14000 //最大测量距离对应的定时器计数  //cnt = 255cm * 2 /(340 * 100) * 100000


void HCSR04_Init(void);

void ultrasonic_startMeasure(void);
float HCSR04GetLength(void);

#endif /* __ULTRASONIC_H*/


