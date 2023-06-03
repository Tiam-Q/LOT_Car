#include "./motor/bsp_motor.h" 
#include "stm32f10x_tim.h"


	/*
	*********************���*****************************************************
	*���1 --> GPIOA6   GPIOA7   (GPIOB6 GPIOB7)(�ٶȶ�ȡ)
	*���2 --> GPIOB0   GPIOB1   (GPIOA0 GPIOA1)(�ٶȶ�ȡ)
  ******************************************************************************
  */ 


/*--------------------TIM3��ʼ��-------------------------*/
static void TIM1_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

  // ����Ƚ�ͨ��1 GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(MOTOR_L1_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  MOTOR_L1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(MOTOR_L1_PORT, &GPIO_InitStructure);
	
	// ����Ƚ�ͨ��2 GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(MOTOR_L2_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  MOTOR_L2_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(MOTOR_L2_PORT, &GPIO_InitStructure);
	
	// ����Ƚ�ͨ��3 GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(MOTOR_R1_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  MOTOR_R1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(MOTOR_R1_PORT, &GPIO_InitStructure);
	
	// ����Ƚ�ͨ��4 GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(MOTOR_R2_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  MOTOR_R2_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(MOTOR_R2_PORT, &GPIO_InitStructure);
}

static void TIM1_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;        
  TIM_OCInitTypeDef        TIM_OCInitStructure;

	MOTOR_TIM1_APBxClock_FUN(MOTOR_TIM1_CLK,ENABLE);
	
	

//	u16 CCR1_Val = 500;                
//	u16 CCR2_Val = 500;       
//	u16 CCR3_Val = 500;        
//	u16 CCR4_Val = 500; 
//	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;           //��������ֵ�������������������ֵʱ����ƽ��������
//	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;          //����ͨ��2�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
//	TIM_OCInitStructure.TIM_Pulse = CCR3_Val;        //����ͨ��3�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM 
//	TIM_OCInitStructure.TIM_Pulse = CCR4_Val;        //����ͨ��4�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM  
	
	

	TIM_TimeBaseStructure.TIM_Period = GENERAL_TIM1_Period;        //����ʱ����0������999����Ϊ1000�Σ�Ϊһ����ʱ����  
  TIM_TimeBaseStructure.TIM_Prescaler = GENERAL_TIM1_Prescaler;             
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;       //����ʱ�ӷ�Ƶϵ��������Ƶ           
 
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;    //���ϼ���ģʽ  
  TIM_TimeBaseInit(MOTOR_TIM1, &TIM_TimeBaseStructure);                   
 
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;              //����ΪPWMģʽ1   
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;               
          
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;      //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ  
  TIM_OC1Init(MOTOR_TIM1, &TIM_OCInitStructure);                 //ʹ��ͨ��1  
  TIM_OC1PreloadConfig(MOTOR_TIM1, TIM_OCPreload_Enable);  
 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   
	TIM_OC2Init(MOTOR_TIM1, &TIM_OCInitStructure);                 //ʹ��ͨ��2 
	TIM_OC2PreloadConfig(MOTOR_TIM1, TIM_OCPreload_Enable);          

	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   
	TIM_OC3Init(MOTOR_TIM1, &TIM_OCInitStructure);                 //ʹ��ͨ��3   
	TIM_OC3PreloadConfig(MOTOR_TIM1, TIM_OCPreload_Enable);    

	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OC4Init(MOTOR_TIM1, &TIM_OCInitStructure);                 //ʹ��ͨ��4 
	TIM_OC4PreloadConfig(MOTOR_TIM1, TIM_OCPreload_Enable);  
 
  TIM_ARRPreloadConfig(MOTOR_TIM1, ENABLE);                      // ʹ��TIM1���ؼĴ���ARR	
	TIM_CtrlPWMOutputs(MOTOR_TIM1, ENABLE);      
	TIM_Cmd(MOTOR_TIM1, ENABLE); 
}
/*-------------------------------------------------------*/


/*-------------------------------------------------------*/
void Motor_Init(void)
{
	TIM1_GPIO_Config();
	TIM1_Mode_Config();
}
/*-------------------------------------------------------*/



/*-------------------------------------------------------*/


//**************************************
// ���1��ת
//------------------------------------
void Motor1_forward(u16 speed)
{

	TIM_SetCompare2(MOTOR_TIM1, 0);
	TIM_SetCompare1(MOTOR_TIM1, speed);
}
//------------------------------------

// ���1��ת
//------------------------------------
void Motor1_backward(u16 speed)
{
	TIM_SetCompare1(MOTOR_TIM1, 0);
	TIM_SetCompare2(MOTOR_TIM1, speed);
}
//------------------------------------


//------------------------------------

// ���1ͣת
//------------------------------------
void Motor1_Stop(void)
{
  TIM_SetCompare1(MOTOR_TIM1, 0);
	TIM_SetCompare2(MOTOR_TIM1, 0);
}
//------------------------------------



//**************************************
// ���2��ת
//----------------------------------
void Motor2_forward(u16 speed)
{	
	TIM_SetCompare4(MOTOR_TIM1, 0);
	TIM_SetCompare3(MOTOR_TIM1, speed);
}
//----------------------------------

// ���2��ת
//----------------------------------
void Motor2_backward(u16 speed)
{
	TIM_SetCompare3(MOTOR_TIM1, 0);
	TIM_SetCompare4(MOTOR_TIM1, speed);
}
//----------------------------------

// ���2ͣת
//----------------------------------
void Motor2_Stop()
{
	TIM_SetCompare3(MOTOR_TIM1, 0);
	TIM_SetCompare4(MOTOR_TIM1, 0);
}
//----------------------------------


// С����ǰ(�ٶ� = speed%)
//---------------------------------
void Car_forward(u16 speed_l,u16 speed_r)
{
	Motor1_forward(speed_l);
	Motor2_forward(speed_r);
}
//---------------------------------


// С�����(�ٶ� = -speed%)
//---------------------------------
void Car_backward(u16 speed)
{
	Motor1_backward(speed);
	Motor2_backward(speed);
					
}
//---------------------------------

// С�����(�ٶ� = -speed%)
//---------------------------------
void Car_Stop(void)
{
	Motor1_Stop();
	Motor2_Stop();
					
}
//---------------------------------



// С����ת
// ��೵�����ת(�ٶ� = -speed%)
// �Ҳ೵����ǰת(�ٶ� = speed%)
//---------------------------------
void Car_Turn_Left(u16 speed,u16 ture_speed)
{
  Motor1_forward(speed-ture_speed);
	Motor2_forward(speed+ture_speed);
}
//---------------------------------


// С����ת
// �Ҳ೵�����ת(�ٶ� = -speed%)
// ��೵����ǰת(�ٶ� = speed%)
//---------------------------------
void Car_Turn_Right(u16 speed,u16 ture_speed)
{
  Motor1_forward(speed+ture_speed);
	Motor2_forward(speed-ture_speed);
}
//---------------------------------


/*********************************************END OF FILE**********************/
