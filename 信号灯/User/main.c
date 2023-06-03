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
	
	uint8_t send_light[2] = {0xff,0x00};    //第二位0代表红灯，1代表绿灯
	uint8_t send_signal[2] = {0xfe,30};  //第二位代表速度限制值
	
	
  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  USART_Config();
	/*延时初始化*/
	delay_Init();
	
  /***************************************/
	//LCD 初始化
	ILI9341_Init ();         
  ILI9341_GramScan ( 6 );
	LCD_SetFont(&Font8x16);
	LCD_SetBackColor(BLACK);         //白色背景
	ILI9341_Clear ( 0, 0, 240, 320); //清屏	
	/***************************************/
	
	/*按键初始化*/
  EXTI_Key_Config();
	/*led初始化*/
	LED_GPIO_Config();
	
  while(1)
	{		
		delay_ms(10);
		/**************************模式0绿灯************************/
		if (mode == 0)
		{
			if(flag != 0)
			{
				ILI9341_Clear ( 0, 0, 240, 320);     //清屏
			}
			send_light[1] = 0x01;    //绿灯信息
			flag = 0;
			LED_GREEN;
			ILI9341_DispStringLine_EN(LINE(6),"GREEN");
		  Show_Led_State(GREEN);
			Usart_SendArray( DEBUG_USARTx, send_light, 2);
		}
		/**************************模式1红灯************************/
		else if (mode == 1)
		{
			if(flag != 1)
				{
					ILI9341_Clear ( 0, 0, 240, 320);     //清屏
					}
				send_light[1] = 0x00;  //红灯信息
				flag = 1;
		  	LED_RED;
				ILI9341_DispStringLine_EN(LINE(6),"RED");
		    Show_Led_State(RED);
				Usart_SendArray( DEBUG_USARTx, send_light, 2);
		}
		/**************************模式2速度限制************************/
		else if(mode == 2)
		{
			if(flag != 2)
				{
					ILI9341_Clear ( 0, 0, 240, 320);     //清屏
					}
			send_signal[1] = Speed_Limit;  //速度限制信息
			flag = 2;
			LED_YELLOW;
			sprintf((char *)string,"Speed Limit  :%d cm/s",Speed_Limit);
			ILI9341_DispStringLine_EN(LINE(10),string);
			Usart_SendArray( DEBUG_USARTx, send_signal, 2);
		}
	}	
}
/*********************************************END OF FILE**********************/
