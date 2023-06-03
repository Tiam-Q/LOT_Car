#ifndef  _ENCODER_H
#define  _ENCODER_H

#include "stm32f10x.h" 


#define L_Round           21.0486     //��̥�ܳ�
#define Num_Round         2340        //תһȦ��������


void TIM2_IRQHandler(void);
void TIM4_IRQHandler(void);
float Read_Speed(int TIMx);
void Encoder_TIM2_Init(void);
void Encoder_TIM4_Init(void);


#endif


