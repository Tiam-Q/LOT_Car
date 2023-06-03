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



// S_Trail_Input的低三位分别对应[PB5、PB4、PB3]的状态值
// 未碰到黑线(接收到红外光)：对应状态 = 0
// 碰到黑线(未接收到红外光)：对应状态 = 1
//-----------------------------------------------------


// 黑线寻迹情况
//---------------------------------------------------------------------
#define		Not_Find_Black_Line			    	0x00	// 全白
#define		Middle_Find_Black_Line			  0x20	// 中间发现黑线
#define		Left_Find_Black_Line		    	0x80	// 最左侧发现黑线
#define		Left_Middle_Find_Black_Line		0x40	// 左中侧发现黑线
#define		Right_Find_Black_Line			    0x01	// 最右侧发现黑线
#define		Right_Middle_Find_Black_Line	0x10	// 右中侧发现黑线
#define		All_Find_Black_Line				    0xf1	// 全部发现黑线

//#define		Not_Find_Black_Line			    	0x00	// 未发现黑线
//#define		Middle_Find_Black_Line			  0x04	// 中间发现黑线
//#define		Left_Find_Black_Line		    	0x10	// 最左侧发现黑线
//#define		Left_Middle_Find_Black_Line		0x08	// 左中侧发现黑线
//#define		Right_Find_Black_Line			    0x01	// 最右侧发现黑线
//#define		Right_Middle_Find_Black_Line	0x02	// 右中侧发现黑线
//#define		All_Find_Black_Line				    0x1f	// 全部发现黑线
//---------------------------------------------------------------------


void Trail_Input_Init_JX(void);		// 红外寻迹初始化
u8 Trail_black_line(void);


#endif	/* __BSP_TRAIL_H */

