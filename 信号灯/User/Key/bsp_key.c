/**
  ******************************************************************************
  * @file    bsp_key.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   ����Ӧ��bsp��ɨ��ģʽ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
  
#include "./Key/bsp_key.h"  
#include "stm32f10x_exti.h"
///**
//  * @brief  ���ð����õ���I/O��
//  * @param  ��
//  * @retval ��
//  */
//void Key_GPIO_Config(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	
//	/*���������˿ڵ�ʱ��*/
//	RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK|KEY2_GPIO_CLK,ENABLE);
//	
//	//ѡ�񰴼�������
//	GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN; 
//	// ���ð���������Ϊ��������
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
//	//ʹ�ýṹ���ʼ������
//	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);
//	
//	//ѡ�񰴼�������
//	GPIO_InitStructure.GPIO_Pin = KEY2_GPIO_PIN; 
//	//���ð���������Ϊ��������
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
//	//ʹ�ýṹ���ʼ������
//	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);	
//}

// /*
// * ��������Key_Scan
// * ����  ������Ƿ��а�������
// * ����  ��GPIOx��x ������ A��B��C��D���� E
// *		     GPIO_Pin������ȡ�Ķ˿�λ 	
// * ���  ��KEY_OFF(û���°���)��KEY_ON�����°�����
// */
//uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
//{			
//	/*����Ƿ��а������� */
//	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
//	{	 
//		/*�ȴ������ͷ� */
//		while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);   
//		return 	KEY_ON;	 
//	}
//	else
//		return KEY_OFF;
//}

 /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* ����NVICΪ���ȼ���1 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* �����ж�Դ������1 */
  NVIC_InitStructure.NVIC_IRQChannel = KEY1_INT_EXTI_IRQ;
  /* ������ռ���ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* ���������ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  /* ʹ���ж�ͨ�� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* �����ж�Դ������2������ʹ������������� */  
  NVIC_InitStructure.NVIC_IRQChannel = KEY2_INT_EXTI_IRQ;
  NVIC_Init(&NVIC_InitStructure);
}

 /**
  * @brief  ���� IOΪEXTI�жϿڣ��������ж����ȼ�
  * @param  ��
  * @retval ��
  */
void EXTI_Key_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;

	/*��������GPIO�ڵ�ʱ��*/
	RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK,ENABLE);
  RCC_APB2PeriphClockCmd(KEY2_INT_GPIO_CLK,ENABLE);
												
	/* ���� NVIC �ж�*/
	NVIC_Configuration();
	
/*--------------------------KEY1����-----------------------------*/
	/* ѡ�񰴼��õ���GPIO */	
  GPIO_InitStructure.GPIO_Pin = KEY1_INT_GPIO_PIN;
  /* ����Ϊ�������� */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStructure);

	/* ѡ��EXTI���ź�Դ */
  GPIO_EXTILineConfig(KEY1_INT_EXTI_PORTSOURCE, KEY1_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = KEY1_INT_EXTI_LINE;
	
	/* EXTIΪ�ж�ģʽ */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* �������ж� */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  /* ʹ���ж� */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	
  /*--------------------------KEY2����-----------------------------*/
	/* ѡ�񰴼��õ���GPIO */	
  GPIO_InitStructure.GPIO_Pin = KEY2_INT_GPIO_PIN;
  /* ����Ϊ�������� */	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(KEY2_INT_GPIO_PORT, &GPIO_InitStructure);

	/* ѡ��EXTI���ź�Դ */
  GPIO_EXTILineConfig(KEY2_INT_EXTI_PORTSOURCE, KEY2_INT_EXTI_PINSOURCE); 
  EXTI_InitStructure.EXTI_Line = KEY2_INT_EXTI_LINE;
	
	/* EXTIΪ�ж�ģʽ */
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	/* �½����ж� */
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  /* ʹ���ж� */	
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}


/*********************************************END OF FILE**********************/
