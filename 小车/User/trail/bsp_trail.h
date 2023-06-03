#ifndef	__BSP_TRAIL_H
#define __BSP_TRAIL_H

#include "stm32f10x.h"


#define Trail_CLK                         RCC_APB2Periph_GPIOB
#define Trail_CLK_GPIO_CLK_FUNCTION       RCC_APB2PeriphClockCmd
#define Trail_GPIO_PORT                   GPIOB
#define Trail0_GPIO_PIN                   GPIO_Pin_8
#define Trail1_GPIO_PIN                   GPIO_Pin_12
#define Trail2_GPIO_PIN                   GPIO_Pin_13
#define Trail3_GPIO_PIN                   GPIO_Pin_14
#define Trail4_GPIO_PIN                   GPIO_Pin_15



// S_Trail_Input�ĵ���λ�ֱ��Ӧ[PB5��PB4��PB3]��״ֵ̬
// δ��������(���յ������)����Ӧ״̬ = 0
// ��������(δ���յ������)����Ӧ״̬ = 1
//-----------------------------------------------------


// ����Ѱ�����
//---------------------------------------------------------------------
#define		Not_Find_Black_Line			    	0x00	// ȫ��
#define		Middle_Find_Black_Line			  0x20	// �м䷢�ֺ���
#define		Left_Find_Black_Line		    	0x80	// ����෢�ֺ���
#define		Left_Middle_Find_Black_Line		0x40	// ���в෢�ֺ���
#define		Right_Find_Black_Line			    0x01	// ���Ҳ෢�ֺ���
#define		Right_Middle_Find_Black_Line	0x10	// ���в෢�ֺ���
#define		All_Find_Black_Line				    0xf1	// ȫ�����ֺ���

//#define		Not_Find_Black_Line			    	0x00	// δ���ֺ���
//#define		Middle_Find_Black_Line			  0x04	// �м䷢�ֺ���
//#define		Left_Find_Black_Line		    	0x10	// ����෢�ֺ���
//#define		Left_Middle_Find_Black_Line		0x08	// ���в෢�ֺ���
//#define		Right_Find_Black_Line			    0x01	// ���Ҳ෢�ֺ���
//#define		Right_Middle_Find_Black_Line	0x02	// ���в෢�ֺ���
//#define		All_Find_Black_Line				    0x1f	// ȫ�����ֺ���
//---------------------------------------------------------------------


void Trail_Input_Init_JX(void);		// ����Ѱ����ʼ��
u8 Trail_black_line(void);


#endif	/* __BSP_TRAIL_H */

