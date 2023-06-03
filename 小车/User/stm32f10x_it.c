/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "bsp_usart.h"
#include "./led/bsp_led.h"
#include "./motor/bsp_motor.h" 


_Bool USART_STATE;
uint8_t Speed_Exp = 20;
extern uint8_t Trail_Times;
extern float Speed_L;
extern float Speed_R;
extern float distance;
uint8_t state = 0;


/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

void RES_Read(u8 res)
{
	static uint8_t   RxState = 0;	
	static uint8_t   Rx_Last = 0;
	
	if(USART_STATE && distance >= 10)
	{	
		if(RxState == 0 && (res == 0xff|res == 0xfe))              //交通灯消息
		{
			RxState = 1;
			Rx_Last = res;
		}
		else if(RxState == 1 && (Rx_Last == 0xff|Rx_Last == 0xfe))
		{			
			if(Rx_Last == 0xff)
				{
					if(res == 0x01)         //绿灯 
						{
							state = 1;
						}
						else if(res == 0x00)  //红灯
							{
								if(Trail_Times == 1)
								{
									state = 2;
								}
								else
								{
									state = 1;
								}
							}
				}
				else if(Rx_Last == 0xfe)//限速
				{
					state = 1;
					Speed_Exp = res;
				}
				
				Rx_Last = 0;
				RxState = 0;
				
		}
	}
}
// 串口中断服务函数 
void DEBUG_USART_IRQHandler(void)
{
    u8 Res;
    if(USART_GetITStatus(DEBUG_USARTx,USART_IT_RXNE)!=RESET) 
		{			
			USART_ClearITPendingBit(DEBUG_USARTx,USART_IT_RXNE);
		  Res=USART_ReceiveData(DEBUG_USARTx);	                         //读取接收到的数据
//			USART_SendData(DEBUG_USARTx,Res);                              //回传接收到的数据		
//			res=Res;
      USART_STATE	=1;		
//			while(USART_GetFlagStatus(DEBUG_USARTx,USART_FLAG_TC)!=SET);   //等待发送完毕
			RES_Read(Res);				
     }
		USART_STATE=0;
}

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
