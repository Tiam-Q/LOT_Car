#ifndef __BSP_MOTOR_H
#define __BSP_MOTOR_H


#include "stm32f10x.h"


/************通用定时器TIM参数定义，只限TIM2、3、4、5************/
//#define            GENERAL_TIM1                   TIM1
//#define            GENERAL_TIM1_APBxClock_FUN     RCC_APB2PeriphClockCmd
//#define            GENERAL_TIM1_CLK               RCC_APB2Periph_TIM1
//#define            GENERAL_TIM1_Period            99
//#define            GENERAL_TIM1_Prescaler         719



///*******************************左前引脚*******************************/
//// TIM1 输出比较通道1        
//#define            MOTOR_LF1_GPIO_CLK             RCC_APB2Periph_GPIOA
//#define            MOTOR_LF1_PORT                 GPIOA
//#define            MOTOR_LF1_PIN                  GPIO_Pin_8
//// TIM1 输出比较通道2                                           
//#define            MOTOR_LF2_GPIO_CLK             RCC_APB2Periph_GPIOA
//#define            MOTOR_LF2_PORT                 GPIOA
//#define            MOTOR_LF2_PIN                  GPIO_Pin_9       
///*******************************左前引脚*******************************/



///*******************************右前引脚*******************************/
//// TIM1 输出比较通道3  
//#define            MOTOR_RF1_GPIO_CLK             RCC_APB2Periph_GPIOA
//#define            MOTOR_RF1_PORT                 GPIOA
//#define            MOTOR_RF1_PIN                  GPIO_Pin_10
//// TIM1 输出比较通道4
//#define            MOTOR_RF2_GPIO_CLK             RCC_APB2Periph_GPIOA
//#define            MOTOR_RF2_PORT                 GPIOA
//#define            MOTOR_RF2_PIN                  GPIO_Pin_11
///*******************************右前引脚*******************************/




#define            MOTOR_TIM1                     TIM1
#define            MOTOR_TIM1_APBxClock_FUN       RCC_APB2PeriphClockCmd
#define            MOTOR_TIM1_CLK                 RCC_APB2Periph_TIM1
#define            GENERAL_TIM1_Period            999
#define            GENERAL_TIM1_Prescaler         71
/*******************************motor1*******************************/
// TIM3 输出比较通道1
#define            MOTOR_L1_GPIO_CLK              RCC_APB2Periph_GPIOA
#define            MOTOR_L1_PORT                  GPIOA
#define            MOTOR_L1_PIN                   GPIO_Pin_8
// TIM3 输出比较通道2
#define            MOTOR_L2_GPIO_CLK              RCC_APB2Periph_GPIOA
#define            MOTOR_L2_PORT                  GPIOA
#define            MOTOR_L2_PIN                   GPIO_Pin_9
/*******************************motor1*******************************/


/*******************************motor2*******************************/
// TIM3 输出比较通道3
#define            MOTOR_R1_GPIO_CLK              RCC_APB2Periph_GPIOA
#define            MOTOR_R1_PORT                  GPIOA
#define            MOTOR_R1_PIN                   GPIO_Pin_10

// TIM3 输出比较通道4
#define            MOTOR_R2_GPIO_CLK              RCC_APB2Periph_GPIOA
#define            MOTOR_R2_PORT                  GPIOA
#define            MOTOR_R2_PIN                   GPIO_Pin_11
/*******************************motor2*******************************/



/****************************************************************************/
void Motor_Init(void);
void Car_forward(u16 speed_l,u16 speed_r);
void Car_backward(u16 speed);
void Car_Stop(void);
void Car_Turn_Left(u16 speed,u16 ture_speed);
void Car_Turn_Right(u16 speed,u16 ture_speed);
/****************************************************************************/



#endif	/* __BSP_MOTOR_H */


