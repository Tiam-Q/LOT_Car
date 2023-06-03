#include "./motor/encoder.h"
#include "stm32f10x_tim.h"
#include "./SysTick/bsp_SysTick.h"


/*************************************************
*减速比1：45
*电机单圈十三个脉冲
*转动一圈产生13*45 = 585个脉冲
*四倍频电机转动一圈产生585*4 = 2340个脉冲
*轮子直径大约6.7cm 转动一周大约行驶21.048670779cm
*************************************************/



void Encoder_TIM2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);    //开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;        //初始化GPIO--PA0、PA1
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0 |GPIO_Pin_1;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);        //初始化定时器。
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=65535;                //ARR
	TIM_TimeBaseInitStruct.TIM_Prescaler=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);//配置编码器模式
	
	TIM_ICStructInit(&TIM_ICInitStruct);                    //初始化输入捕获
	TIM_ICInitStruct.TIM_ICFilter=10;                       //滤波器
	TIM_ICInit(TIM2,&TIM_ICInitStruct);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);                //配置溢出更新中断标志位
	
	TIM_SetCounter(TIM2,0);                                 //清零定时器计数值
	
	TIM_Cmd(TIM2,ENABLE);                                   //开启定时器
}


void Encoder_TIM4_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6 |GPIO_Pin_7;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=65535;
	TIM_TimeBaseInitStruct.TIM_Prescaler=0;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);
	
	// 编码器配置函数: 定时器4，模式3（在T1T2的所有边沿均计数 即四倍频），上升沿
	TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	
	TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_ICFilter=10;
	TIM_ICInit(TIM4,&TIM_ICInitStruct);
	
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	
	TIM_SetCounter(TIM4,0);

	TIM_Cmd(TIM4,ENABLE);
}


/**********************
编码器
速度读取函数
入口参数：定时器
**********************/
float Read_Speed(int TIMx)
{
	u16 value_1;
	float speed=0;
	switch(TIMx)
	{
		case 2:TIM_SetCounter(TIM2,0);
		       delay_ms(1);
			     value_1=(short)TIM_GetCounter(TIM2);
		       speed = (L_Round * ( (float)value_1 / Num_Round)*100 );
		       TIM_SetCounter(TIM2,0);
				break;
		//IF是定时器2，1.采集编码器的计数值并保存。2.将定时器的计数值清零。
		case 4:TIM_SetCounter(TIM4,0);
	         delay_ms(1);
			     value_1=(short)TIM_GetCounter(TIM4);
		       speed = (L_Round * ( (float)value_1 / Num_Round)*100 );
				   TIM_SetCounter(TIM4,0);
				break;
		default:speed=0;
	}
	return speed;
//	return value_1;
}

//float speed_count (int value)
//{
//	float speed;
//	speed = (L_Round * (value / Num_Round))*1000;
//}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=0)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);	
	}
}
	
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=0)
	{
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	}
}

