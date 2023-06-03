#ifndef __KEY_H
#define	__KEY_H


#include "stm32f10x.h"

////  ���Ŷ���
//#define    KEY1_GPIO_CLK     RCC_APB2Periph_GPIOA
//#define    KEY1_GPIO_PORT    GPIOA			   
//#define    KEY1_GPIO_PIN		 GPIO_Pin_0

//#define    KEY2_GPIO_CLK     RCC_APB2Periph_GPIOC
//#define    KEY2_GPIO_PORT    GPIOC		   
//#define    KEY2_GPIO_PIN		 GPIO_Pin_13


// /** �������±��ú�
//	*  ��������Ϊ�ߵ�ƽ������ KEY_ON=1�� KEY_OFF=0
//	*  ����������Ϊ�͵�ƽ���Ѻ����ó�KEY_ON=0 ��KEY_OFF=1 ����
//	*/
//#define KEY_ON	1
//#define KEY_OFF	0

//void Key_GPIO_Config(void);
//uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);


//���Ŷ���
#define KEY1_INT_GPIO_PORT         GPIOA
#define KEY1_INT_GPIO_CLK          (RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO)
#define KEY1_INT_GPIO_PIN          GPIO_Pin_0
#define KEY1_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOA
#define KEY1_INT_EXTI_PINSOURCE    GPIO_PinSource0
#define KEY1_INT_EXTI_LINE         EXTI_Line0
#define KEY1_INT_EXTI_IRQ          EXTI0_IRQn

#define KEY1_IRQHandler            EXTI0_IRQHandler


#define KEY2_INT_GPIO_PORT         GPIOC
#define KEY2_INT_GPIO_CLK          (RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO)
#define KEY2_INT_GPIO_PIN          GPIO_Pin_13
#define KEY2_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOC
#define KEY2_INT_EXTI_PINSOURCE    GPIO_PinSource13
#define KEY2_INT_EXTI_LINE         EXTI_Line13
#define KEY2_INT_EXTI_IRQ          EXTI15_10_IRQn

#define KEY2_IRQHandler            EXTI15_10_IRQHandler

void EXTI_Key_Config(void);

#endif /* __KEY_H */

