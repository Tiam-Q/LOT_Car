/**
  ******************************************************************************
  * @file    bsp_SysTick.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   SysTick 系统滴答时钟10us中断函数库,中断时间可自由配置，
  *          常用的有 1us 10us 1ms 中断。     
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火 F103-指南者-MINI STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./SysTick/bsp_SysTick.h"

uint8_t    D_us=0;			//微秒系数
uint16_t   D_ms=0;			//毫秒系数

/***************************************************************************************
* 函  数: void Delay_Init(void)
* 功  能: 延时函数初始化
* 参  数: 无
* 返回值：无
* 备  注: T(s) = 1/F(Hz) //赫兹时间转换公式
*****************************************************************************************/
void delay_Init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	
	D_us = SystemCoreClock/1000000;// 1us
	D_ms = (uint16_t)D_us * 1000;
	
}

/***************************************************************************************
* 函  数: void Delay_us(uint32_t nus)
* 功  能: 微秒级延时
* 参  数: nus 传入微秒参数
* 返回值：无
* 备  注: LOAD为24位寄存器，nus 的最大传入值为 2的24次方(0xFFFFFF*72) / SYSCLK = 16777216 us
*****************************************************************************************/
void delay_us(uint32_t nus)
{
	uint32_t temp;
	SysTick->CTRL = 0x00;			//关闭SysTick定时器
	SysTick->LOAD = nus*72; 		//延时重装载值	  		 
	SysTick->VAL  = 0x00;        	//清空计数器
	SysTick->CTRL |= 0x01 ;			//启动SysTick定时器  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	  	//等待延时结束  
	SysTick->CTRL = 0x00;						//关闭SysTick定时器
	SysTick->VAL  = 0X00;      					//清空计数器
}

/***************************************************************************************
* 函  数: void Delay_ms(uint32_t nms)
* 功  能: 毫秒级延时
* 参  数: nms 传入微秒参数
* 返回值：无
* 备  注: LOAD为24位寄存器，nms 的最大传入值为 2的24次方(0xFFFFFF*72*1000) / SYSCLK = 16777 ms
*****************************************************************************************/
void delay_ms(uint32_t nms)
{
	uint32_t temp;
	SysTick->CTRL = 0x00;					//关闭SysTick定时器
	SysTick->LOAD = nms*72000; 				//延时重装载值	  		 
	SysTick->VAL  = 0x00;        			//清空计数器
	SysTick->CTRL |= 0x01 ;					//启动SysTick定时器  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	 	 				//等待延时结束  
	SysTick->CTRL = 0x00;										//关闭SysTick定时器
	SysTick->VAL  = 0X00;      									//清空计数器	
}


/*********************************************END OF FILE**********************/
