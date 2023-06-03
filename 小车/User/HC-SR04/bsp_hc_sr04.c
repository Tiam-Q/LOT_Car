#include "./HC-SR04/bsp_hc_sr04.h"
#include "./SysTick/bsp_SysTick.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_exti.h"
#include "./filter/filter.h"


uint16_t msHcCount = 0;
/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * �ļ���  : UltrasonicWave.c
 * ����    �����������ģ�飬UltrasonicWave_Configuration��������
             ��ʼ������ģ�飬UltrasonicWave_StartMeasure��������
			 ������࣬������õ�����ͨ������1��ӡ����         
 * ʵ��ƽ̨��Ұ��STM32������
 * Ӳ�����ӣ�------------------
 *          | PB1  - TRIG      |
 *          | PB0  - ECHO      |
 *           ------------------
 * ��汾  ��ST3.5.0
 *
 * ����    ��wildfire team 
 * ��̳    ��http://www.amobbs.com/forum-1008-1.html
 * �Ա�    ��http://firestm32.taobao.com
*********************************************************************************/
void HCSR04_Init(void)
{  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;     //���嶨ʱ���ṹ��
	GPIO_InitTypeDef GPIO_InitStructure;
	HCSR04_CLK_GPIO_CLK_FUNCTION(HCSR04_CLK, ENABLE);
	 
	//IO ��ʼ��
	GPIO_InitStructure.GPIO_Pin = HCSR04_TRIG;       	//���͸ߵ�ƽ����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//�������
	GPIO_Init(HCSR04_PORT, &GPIO_InitStructure);
	GPIO_ResetBits(HCSR04_PORT,HCSR04_TRIG);
	 
	GPIO_InitStructure.GPIO_Pin = HCSR04_ECHO;    	 //���ص�ƽ����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	
	GPIO_Init(HCSR04_PORT, &GPIO_InitStructure);  
	GPIO_ResetBits(HCSR04_PORT,HCSR04_ECHO);	
	 
	//��ʱ����ʼ��ʹ�û�����ʱ��3
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);   //��TIM3��ʱ��ʱ��

	TIM_DeInit(TIM3);
	TIM_TimeBaseStructure.TIM_Period = 65535; //(1000-1); //��������һ������ʱ��װ�����Զ���װ�ؼĴ������ڵ�ֵ         ������1000Ϊ1ms
	TIM_TimeBaseStructure.TIM_Prescaler =(72-1); //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶ  1M�ļ�ʱƵ�� 1US����
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;	//����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ	 
		
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);   	//��������жϱ����������������ж�
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);    //���ü�ʱ�������ж�

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;            	//�����жϷ���
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  	//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;         	//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;        		//�����ж�
	NVIC_Init(&NVIC_InitStructure);
	
  TIM_Cmd(TIM3,DISABLE);     
}

//��ʱ���жϷ������
void TIM3_IRQHandler(void)   //TIM3�Д�
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //���TIM�����ж��Ƿ���
    {
         TIM_ClearITPendingBit(TIM3, TIM_IT_Update);  //���TIM�����жϱ�־λ
         msHcCount++;
    }
}

//��ʼ����
static void StartTimer()        //�򿪶�ʱ��
{
    TIM_SetCounter(TIM3,0);	//�������
    msHcCount = 0;
    TIM_Cmd(TIM3, ENABLE);  //����TIM3����
}
 
static void StopTimer() 	//�رն�ʱ������
{
    TIM_Cmd(TIM3, DISABLE); //�ر�TIM��ʱ������
}
 
//��ȡ��ʱ��ʱ��
float GetEchoTimer(void)
{
    u32 t = 0;
    t = msHcCount*1000;			//�õ�ms
    t += TIM_GetCounter(TIM3);	//�õ�us
  	TIM3->CNT = 0;  			//��TIM3��ʱ�������ļĴ�������
	  delay_us(50);
    return t;
}


//ȡ�������ƽ��ֵ��Ϊ��ʹ������õ���ֵ���Ӿ�ȷ�ɲ�ȡ��β���ƽ��ֵ��ʹ��Ӧ����
float HCSR04GetLength(void)
{
	u32 t = 0;
	int i = 0;
	float lengthTemp = 0;  
	float sum = 0; 	
	float distance;

	for(i=0;i<5;i++){		
		
		TRIG_SET;      //���͸ߵ�ƽ���
		delay_us(20);
		TRIG_RESET;
			
		while(ECHO_RECEIVE == 0); 	//�ȴ����ոߵ�ƽ���
		StartTimer();        	//�򿪼�ʱ��

		while(ECHO_RECEIVE == 1)
		{
			if(TIM_GetCounter(TIM3) >= UL_TIM_MAX_COUNT) // cnt = 255cm * 2 /(340 * 100) * 100000
      {
        break;  //�����趨�Ĳ��������룬�����ȴ�
      }
		}
		StopTimer();        	//�رռ�ʱ��
		
		t = GetEchoTimer();     //��ȡʱ��,������Ϊ1US

		lengthTemp = ((float)t/58.2);	//cm
		sum = lengthTemp + sum ;
	}
	distance = sum/5.0;
	return distance;
}
