#include "./motor/bsp_motor.h" 
#include "stm32f10x_tim.h"


	/*
	*********************电机*****************************************************
	*电机1 --> GPIOA6   GPIOA7   (GPIOB6 GPIOB7)(速度读取)
	*电机2 --> GPIOB0   GPIOB1   (GPIOA0 GPIOA1)(速度读取)
  ******************************************************************************
  */ 


/*--------------------TIM3初始化-------------------------*/
static void TIM1_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

  // 输出比较通道1 GPIO 初始化
	RCC_APB2PeriphClockCmd(MOTOR_L1_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  MOTOR_L1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(MOTOR_L1_PORT, &GPIO_InitStructure);
	
	// 输出比较通道2 GPIO 初始化
	RCC_APB2PeriphClockCmd(MOTOR_L2_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  MOTOR_L2_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(MOTOR_L2_PORT, &GPIO_InitStructure);
	
	// 输出比较通道3 GPIO 初始化
	RCC_APB2PeriphClockCmd(MOTOR_R1_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  MOTOR_R1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(MOTOR_R1_PORT, &GPIO_InitStructure);
	
	// 输出比较通道4 GPIO 初始化
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
//	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;           //设置跳变值，当计数器计数到这个值时，电平发生跳变
//	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;          //设置通道2的电平跳变值，输出另外一个占空比的PWM
//	TIM_OCInitStructure.TIM_Pulse = CCR3_Val;        //设置通道3的电平跳变值，输出另外一个占空比的PWM 
//	TIM_OCInitStructure.TIM_Pulse = CCR4_Val;        //设置通道4的电平跳变值，输出另外一个占空比的PWM  
	
	

	TIM_TimeBaseStructure.TIM_Period = GENERAL_TIM1_Period;        //当定时器从0计数到999，即为1000次，为一个定时周期  
  TIM_TimeBaseStructure.TIM_Prescaler = GENERAL_TIM1_Prescaler;             
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;       //设置时钟分频系数：不分频           
 
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;    //向上计数模式  
  TIM_TimeBaseInit(MOTOR_TIM1, &TIM_TimeBaseStructure);                   
 
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;              //配置为PWM模式1   
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;               
          
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;      //当定时器计数值小于CCR1_Val时为高电平  
  TIM_OC1Init(MOTOR_TIM1, &TIM_OCInitStructure);                 //使能通道1  
  TIM_OC1PreloadConfig(MOTOR_TIM1, TIM_OCPreload_Enable);  
 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   
	TIM_OC2Init(MOTOR_TIM1, &TIM_OCInitStructure);                 //使能通道2 
	TIM_OC2PreloadConfig(MOTOR_TIM1, TIM_OCPreload_Enable);          

	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   
	TIM_OC3Init(MOTOR_TIM1, &TIM_OCInitStructure);                 //使能通道3   
	TIM_OC3PreloadConfig(MOTOR_TIM1, TIM_OCPreload_Enable);    

	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OC4Init(MOTOR_TIM1, &TIM_OCInitStructure);                 //使能通道4 
	TIM_OC4PreloadConfig(MOTOR_TIM1, TIM_OCPreload_Enable);  
 
  TIM_ARRPreloadConfig(MOTOR_TIM1, ENABLE);                      // 使能TIM1重载寄存器ARR	
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
// 电机1正转
//------------------------------------
void Motor1_forward(u16 speed)
{

	TIM_SetCompare2(MOTOR_TIM1, 0);
	TIM_SetCompare1(MOTOR_TIM1, speed);
}
//------------------------------------

// 电机1反转
//------------------------------------
void Motor1_backward(u16 speed)
{
	TIM_SetCompare1(MOTOR_TIM1, 0);
	TIM_SetCompare2(MOTOR_TIM1, speed);
}
//------------------------------------


//------------------------------------

// 电机1停转
//------------------------------------
void Motor1_Stop(void)
{
  TIM_SetCompare1(MOTOR_TIM1, 0);
	TIM_SetCompare2(MOTOR_TIM1, 0);
}
//------------------------------------



//**************************************
// 电机2正转
//----------------------------------
void Motor2_forward(u16 speed)
{	
	TIM_SetCompare4(MOTOR_TIM1, 0);
	TIM_SetCompare3(MOTOR_TIM1, speed);
}
//----------------------------------

// 电机2反转
//----------------------------------
void Motor2_backward(u16 speed)
{
	TIM_SetCompare3(MOTOR_TIM1, 0);
	TIM_SetCompare4(MOTOR_TIM1, speed);
}
//----------------------------------

// 电机2停转
//----------------------------------
void Motor2_Stop()
{
	TIM_SetCompare3(MOTOR_TIM1, 0);
	TIM_SetCompare4(MOTOR_TIM1, 0);
}
//----------------------------------


// 小车向前(速度 = speed%)
//---------------------------------
void Car_forward(u16 speed_l,u16 speed_r)
{
	Motor1_forward(speed_l);
	Motor2_forward(speed_r);
}
//---------------------------------


// 小车向后(速度 = -speed%)
//---------------------------------
void Car_backward(u16 speed)
{
	Motor1_backward(speed);
	Motor2_backward(speed);
					
}
//---------------------------------

// 小车向后(速度 = -speed%)
//---------------------------------
void Car_Stop(void)
{
	Motor1_Stop();
	Motor2_Stop();
					
}
//---------------------------------



// 小车左转
// 左侧车轮向后转(速度 = -speed%)
// 右侧车轮向前转(速度 = speed%)
//---------------------------------
void Car_Turn_Left(u16 speed,u16 ture_speed)
{
  Motor1_forward(speed-ture_speed);
	Motor2_forward(speed+ture_speed);
}
//---------------------------------


// 小车右转
// 右侧车轮向后转(速度 = -speed%)
// 左侧车轮向前转(速度 = speed%)
//---------------------------------
void Car_Turn_Right(u16 speed,u16 ture_speed)
{
  Motor1_forward(speed+ture_speed);
	Motor2_forward(speed-ture_speed);
}
//---------------------------------


/*********************************************END OF FILE**********************/
