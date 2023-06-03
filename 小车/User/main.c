/**
  **********************************����***************************************
  *TX --> GPIOA3
	*RX --> GPIOA2
	**********************************���***************************************
	*���1 --> GPIOA8   GPIOA9   (GPIOB6 GPIOB7)(TIM4�ٶȶ�ȡ)
	*���2 --> GPIOA10  GPIOA11  (GPIOA0 GPIOA1)(TIM2�ٶȶ�ȡ)
  **********************************OLED***************************************
	*PB10 --> SCL; 
	*PB11 --> SDA 
  *********************************������**************************************
	*PB1 --> TRIG; 
	*PB0 --> ECHO
	********************************����ѭ��*************************************
	*���������
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
float Speed_L = 0;              //�����ٶȼ���ֵ
float Speed_R = 0;              //�����ٶȼ���ֵ
float distance = 0;             //����


uint8_t Trail_Times = 0;        //�������ߵĴ���
extern uint8_t Speed_Exp;       //�����ٶ�
extern uint8_t state;           //״̬


int main(void)
{	
	float Speed_L_Act = 0;  //�����ٶ�ʵ��ֵ
	float Speed_R_Act = 0;  //�����ٶ�ʵ��ֵ
	char buf[16];
	uint8_t Trail_Before = Not_Find_Black_Line;   //ѭ��ģ��ǰһ��״̬
	uint8_t Trail_Now = Not_Find_Black_Line;      //ѭ��ģ��ǰһ��״̬
	
	
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  USART_Config();
	
	LED_GPIO_Config();      //LED��ʼ��
	
	Motor_Init();           //�����ʼ��
	Encoder_TIM2_Init();    //��������ʼ��
	Encoder_TIM4_Init();    //��������ʼ��
	
	I2C_Configuration();    //OLED��ʾ��IICͨ�ų�ʼ��
	OLED_Init();            //OLED��ʼ��
	
  delay_Init();           //ϵͳʱ�ӳ�ʼ��
	
	HCSR04_Init();          //��������ʼ��
	
	Trail_Input_Init_JX();  //����ѭ����ʼ��		
	
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
    //��ʾ����
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
		//��ʾ�ٶ�
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
