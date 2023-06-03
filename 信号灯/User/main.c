/**
  ******************************************************************************
  *TX --> GPIOA3
	*RX --> GPIOA2
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "./SysTick/bsp_SysTick.h"
#include "./LCD/bsp_ili9341_lcd.h"
#include "./Key/bsp_key.h"
#include "./led/bsp_led.h"  


int mode = 0;
uint8_t Speed_Limit=20;


void Show_Led_State (uint16_t Color)
{
	LCD_SetTextColor(Color);
	ILI9341_DrawCircle ( 120, 160, 50, 1);
}


int main(void)
{	
	int flag = 0;
	char string[70] = {0};
	
	uint8_t send_light[2] = {0xff,0x00};    //�ڶ�λ0�����ƣ�1�����̵�
	uint8_t send_signal[2] = {0xfe,30};  //�ڶ�λ�����ٶ�����ֵ
	
	
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  USART_Config();
	/*��ʱ��ʼ��*/
	delay_Init();
	
  /***************************************/
	//LCD ��ʼ��
	ILI9341_Init ();         
  ILI9341_GramScan ( 6 );
	LCD_SetFont(&Font8x16);
	LCD_SetBackColor(BLACK);         //��ɫ����
	ILI9341_Clear ( 0, 0, 240, 320); //����	
	/***************************************/
	
	/*������ʼ��*/
  EXTI_Key_Config();
	/*led��ʼ��*/
	LED_GPIO_Config();
	
  while(1)
	{		
		delay_ms(10);
		/**************************ģʽ0�̵�************************/
		if (mode == 0)
		{
			if(flag != 0)
			{
				ILI9341_Clear ( 0, 0, 240, 320);     //����
			}
			send_light[1] = 0x01;    //�̵���Ϣ
			flag = 0;
			LED_GREEN;
			ILI9341_DispStringLine_EN(LINE(6),"GREEN");
		  Show_Led_State(GREEN);
			Usart_SendArray( DEBUG_USARTx, send_light, 2);
		}
		/**************************ģʽ1���************************/
		else if (mode == 1)
		{
			if(flag != 1)
				{
					ILI9341_Clear ( 0, 0, 240, 320);     //����
					}
				send_light[1] = 0x00;  //�����Ϣ
				flag = 1;
		  	LED_RED;
				ILI9341_DispStringLine_EN(LINE(6),"RED");
		    Show_Led_State(RED);
				Usart_SendArray( DEBUG_USARTx, send_light, 2);
		}
		/**************************ģʽ2�ٶ�����************************/
		else if(mode == 2)
		{
			if(flag != 2)
				{
					ILI9341_Clear ( 0, 0, 240, 320);     //����
					}
			send_signal[1] = Speed_Limit;  //�ٶ�������Ϣ
			flag = 2;
			LED_YELLOW;
			sprintf((char *)string,"Speed Limit  :%d cm/s",Speed_Limit);
			ILI9341_DispStringLine_EN(LINE(10),string);
			Usart_SendArray( DEBUG_USARTx, send_signal, 2);
		}
	}	
}
/*********************************************END OF FILE**********************/
