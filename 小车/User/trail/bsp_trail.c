#include "./trail/bsp_trail.h"



uint8_t Trail_State=0;



/********************************红外循迹*************************************
*Trail0 --> PB8
*Trail1 --> PB12
*Trail2 --> PB13
*Trail3 --> PB14
*Trail4 --> PB15
******************************************************************************/


// 红外寻迹初始化(将PB3、PB4、PB5初始化为上拉输入)
//----------------------------------------------------------------------------------------------
void Trail_Input_Init_JX(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	// 使能GPIOB端口时钟
	Trail_CLK_GPIO_CLK_FUNCTION(Trail_CLK, ENABLE);			// GPIOB时钟使能
	

	GPIO_InitStructure.GPIO_Pin = Trail0_GPIO_PIN|Trail1_GPIO_PIN|Trail2_GPIO_PIN|Trail3_GPIO_PIN|Trail4_GPIO_PIN;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 					// 上拉输入

	
	GPIO_Init(Trail_GPIO_PORT, &GPIO_InitStructure);							// 初始化PB3、PB4、PB5
}
//----------------------------------------------------------------------------------------------


// 黑线寻迹函数
// S_Trail_Input的低三位分别对应[PB5、PB4、PB3]的状态值
// 未碰到黑线(接收到红外光)：对应状态 = 0
// 碰到黑线(未接收到红外光)：对应状态 = 1
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





