#include "./trail/bsp_trail.h"



uint8_t Trail_State=0;



/********************************����ѭ��*************************************
*Trail0 --> PB8
*Trail1 --> PB12
*Trail2 --> PB13
*Trail3 --> PB14
*Trail4 --> PB15
******************************************************************************/


// ����Ѱ����ʼ��(��PB3��PB4��PB5��ʼ��Ϊ��������)
//----------------------------------------------------------------------------------------------
void Trail_Input_Init_JX(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	// ʹ��GPIOB�˿�ʱ��
	Trail_CLK_GPIO_CLK_FUNCTION(Trail_CLK, ENABLE);			// GPIOBʱ��ʹ��
	

	GPIO_InitStructure.GPIO_Pin = Trail0_GPIO_PIN|Trail1_GPIO_PIN|Trail2_GPIO_PIN|Trail3_GPIO_PIN|Trail4_GPIO_PIN;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 					// ��������

	
	GPIO_Init(Trail_GPIO_PORT, &GPIO_InitStructure);							// ��ʼ��PB3��PB4��PB5
}
//----------------------------------------------------------------------------------------------


// ����Ѱ������
// S_Trail_Input�ĵ���λ�ֱ��Ӧ[PB5��PB4��PB3]��״ֵ̬
// δ��������(���յ������)����Ӧ״̬ = 0
// ��������(δ���յ������)����Ӧ״̬ = 1
//----------------------------------------------------
u8 Trail_black_line(void) 
{
	u8 S_Trail_Input = 0;
	
	
	S_Trail_Input = (((u16)Trail_GPIO_PORT->IDR) & 0xf100)>>8;
	
	return S_Trail_Input;
	
//	if(GPIO_ReadInputDataBit(Trail_GPIO_PORT,Trail0_GPIO_PIN) == 1)
//	{
//		S_Trail_Input |= 0x01;
//	}
//	else
//	{
//		S_Trail_Input &= 0x3e;
//	}
//	if(GPIO_ReadInputDataBit(Trail_GPIO_PORT,Trail1_GPIO_PIN) == 1)
//	{
//		S_Trail_Input |= 0x02;
//	}
//	else
//	{
//		S_Trail_Input &= 0x1d;
//	}
//	if(GPIO_ReadInputDataBit(Trail_GPIO_PORT,Trail2_GPIO_PIN) == 1)
//	{
//		S_Trail_Input |= 0x04;
//	}
//	else
//	{
//		S_Trail_Input &= 0x1b;
//	}
//	if(GPIO_ReadInputDataBit(Trail_GPIO_PORT,Trail3_GPIO_PIN) == 1)
//	{
//		S_Trail_Input |= 0x08;
//	}
//	else
//	{
//		S_Trail_Input &= 0x17;
//	}
//	if(GPIO_ReadInputDataBit(Trail_GPIO_PORT,Trail4_GPIO_PIN) == 1)
//	{
//		S_Trail_Input |= 0x10;
//	}
//	else
//	{
//		S_Trail_Input &= 0x0f;
//	}
//	
//	return S_Trail_Input;
}
//----------------------------------------------------





