/**
  **********************************蓝牙***************************************
  *TX --> GPIOA3
	*RX --> GPIOA2
	**********************************电机***************************************
	*电机1 --> GPIOA8   GPIOA9   (GPIOB6 GPIOB7)(TIM4速度读取)
	*电机2 --> GPIOA10  GPIOA11  (GPIOA0 GPIOA1)(TIM2速度读取)
  **********************************OLED***************************************
	*PB10 --> SCL; 
	*PB11 --> SDA 
  *********************************超声波**************************************
	*PB1 --> TRIG; 
	*PB0 --> ECHO
	********************************红外循迹*************************************
	*从右向左边
	*Trail0 --> PB8
	*Trail1 --> PB12
	*Trail2 --> PB13
	*Trail3 --> PB14
	*Trail4 --> PB15
**/ 


#include "stm32f10x.h"
#include "bsp_usart.h"
#include "./led/bsp_led.h"
#include "./motor/bsp_motor.h" 
#include "./motor/encoder.h"
#include "./SysTick/bsp_SysTick.h"
#include "./OLED/OLED_I2C.h"
#include "./HC-SR04/bsp_hc_sr04.h"
#include "./trail/bsp_trail.h"
#include "./pid/pid.h"


Pid_Module MotorL_Pid;
Pid_Module MotorR_Pid;
float Speed_L = 0;              //左轮速度计算值
float Speed_R = 0;              //右轮速度计算值
float distance = 0;             //距离


uint8_t Trail_Times = 0;        //经过黑线的次数
extern uint8_t Speed_Exp;       //期望速度
extern uint8_t state;           //状态


int main(void)
{	
	float Speed_L_Act = 0;  //左轮速度实际值
	float Speed_R_Act = 0;  //右轮速度实际值
	char buf[16];
	uint8_t Trail_Before = Not_Find_Black_Line;   //循迹模块前一个状态
	uint8_t Trail_Now = Not_Find_Black_Line;      //循迹模块前一个状态
	
	
  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  USART_Config();
	
	LED_GPIO_Config();      //LED初始化
	
	Motor_Init();           //电机初始化
	Encoder_TIM2_Init();    //编码器初始化
	Encoder_TIM4_Init();    //编码器初始化
	
	I2C_Configuration();    //OLED显示屏IIC通信初始化
	OLED_Init();            //OLED初始化
	
  delay_Init();           //系统时钟初始化
	
	HCSR04_Init();          //超声波初始化
	
	Trail_Input_Init_JX();  //红外循迹初始化		
	
	PID_Init(&MotorL_Pid);
	PID_Init(&MotorR_Pid);
	PID_Set_Kpid(&MotorL_Pid, 15, 5.5, 0);
	PID_Set_Kpid(&MotorR_Pid, 15, 5.5, 0);
	PID_Set_limit(&MotorL_Pid, 100,  1000);
	PID_Set_limit(&MotorR_Pid, 100,  1000);
	
	OLED_ShowStr(0, 0, (unsigned char*)"distance:", 2);
	OLED_ShowStr(80, 2, (unsigned char*)"cm", 2);
  OLED_ShowStr(0, 4, (unsigned char*)"spead:", 2);
	OLED_ShowStr(80, 6, (unsigned char*)"cm/s", 2);
	

  while(1)
	{	
		distance = HCSR04GetLength();			
		
		if(distance < 20)
		{
			Car_Stop();
		}
    //显示距离
		sprintf(buf,"%.1f",distance);
    OLED_ShowStr(20, 2, (unsigned char*)buf, 2);
		

		
		if(state == 1)
		{
			Speed_L_Act = Read_Speed(4);
	  	Speed_L = (u16)Pos_PID_CAL_OUT(&MotorL_Pid, (float)(Speed_Exp-Speed_L_Act));
	  	Speed_R_Act = Read_Speed(2);
	  	Speed_R = (u16)Pos_PID_CAL_OUT(&MotorR_Pid, (float)(Speed_Exp-Speed_R_Act));
			Car_forward(Speed_L,Speed_R);
		}
		else if(state == 2)
		{
			Car_Stop();
			PID_Clear(&MotorL_Pid);
			PID_Clear(&MotorR_Pid);
			Speed_L_Act = 0;
			Speed_R_Act = 0;
		}
		//显示速度
		sprintf(buf,"%.1f", (Speed_L_Act+Speed_R_Act)/2.0 );
//		sprintf(buf,"%.1f", Speed_L_Act );
    OLED_ShowStr(20, 6, (unsigned char*)buf, 2);	
		
		Trail_Now = Trail_black_line();
		if(Trail_Now == All_Find_Black_Line && Trail_Before != All_Find_Black_Line)
		{
			Trail_Times++;
		}
		Trail_Before = Trail_Now;
	}	
}
/*********************************************END OF FILE**********************/
