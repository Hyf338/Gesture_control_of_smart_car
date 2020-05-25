/*******************************************************************************
*  Copyright (C) 2010 - All Rights Reserved
*		
* 软件作者:	骑飞家族
* 版权所有: 骑飞电子	
* 创建日期:	2012年8月18日 
* 软件历史:	2012年8月18日首版
* Version:  1.0 
* Demo 淘宝地址：http://store.taobao.com/shop/view_shop.htm?asker=wangwang&shop_nick=qifeidianzi
**********************************************************************************************************************************************
懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒
懒懒懒懒懒懒懒懒懒懒懒一懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒困一懒懒懒懒懒懒懒懒懒懒懒懒懒懒一一一一一一一懒懒懒懒懒懒懒
懒懒困一一一一懒一一一一一一二懒懒懒懒困一一一一一一一一懒懒懒懒懒懒懒懒懒四厲懒懒一一懒懒懒一懒懒懒懒懒懒懒懒懒一一一一四四一一一懒懒懒懒懒懒
懒懒懒懒懒懒一懒懒懒一二一懒懒懒懒懒懒一一一一四厲二一四懒一一懒懒懒懒懒四一一一一一一一一一一一懒懒懒懒懒懒懒懒四懒懒四一一一一厲懒懒懒懒懒懒
懒懒懒四厲厲一懒懒厲懒懒懒四懒懒懒懒懒懒懒懒懒懒懒困一懒一一懒懒懒懒懒懒懒一一厲厲一一厲厲厲一一懒懒懒懒懒懒厲厲厲厲厲厲一一厲厲厲懒懒懒懒懒懒
懒懒懒一懒二一一一一一一一一一一一懒懒懒懒懒懒懒懒二一一困懒懒懒懒懒懒懒懒一一一一一一一一一一四懒懒懒懒懒一一一一一一一一一一一一一一一懒懒懒
懒懒懒一一一一一厲二一一厲一懒厲懒懒懒懒懒懒懒懒懒一一一一一懒懒懒懒懒懒懒一一懒懒一一懒懒懒一困懒懒懒懒懒一一四懒懒懒懒一一懒懒困一一四懒懒懒
懒懒懒懒懒懒懒一困一懒一厲一懒懒懒懒懒懒懒懒懒懒懒困一懒懒一一懒懒懒懒懒懒一一一一一一一一一一厲懒懒懒懒懒懒懒懒懒懒懒懒一一厲懒懒懒懒懒懒懒懒
懒二一一一懒四困厲一一一厲一懒懒懒懒懒懒懒懒懒懒懒懒一一懒懒懒懒懒懒懒懒懒懒懒懒懒四一厲懒懒懒懒懒懒一懒懒懒懒懒懒懒懒懒一一厲懒懒懒懒懒懒懒懒
懒懒懒懒懒懒一懒懒懒懒懒一一懒懒懒懒懒懒懒懒懒懒懒懒厲一一一一一一困懒懒懒懒懒懒懒懒一一一一一一一一一懒懒懒懒懒困懒懒厲一一懒懒懒懒懒懒懒懒懒
懒懒懒懒一一一懒懒困一一一一懒懒懒懒懒懒懒懒懒懒懒懒懒懒一一一一一懒懒懒懒懒懒懒懒懒懒一一一一一一一懒懒懒懒懒懒懒一一一一四懒懒懒懒懒懒懒懒懒
懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒懒
**********************************************************************************************************************************************/

#ifndef USART_H_H_
#define USART_H_H_

#include "stm32f10x.h"	 
#define COMn                             2

//抢占优先级
#define USART_NVIC_PREE_PRI				0	
/**
 * @brief Definition for COM port1, connected to USART1
 */ 
#define USART_COM1                        USART1
#define USART_COM1_CLK                    RCC_APB2Periph_USART1
#define USART_COM1_TX_PIN                 GPIO_Pin_9
#define USART_COM1_TX_GPIO_PORT           GPIOA
#define USART_COM1_TX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define USART_COM1_RX_PIN                 GPIO_Pin_10
#define USART_COM1_RX_GPIO_PORT           GPIOA
#define USART_COM1_RX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define USART_COM1_IRQn                   USART1_IRQn
#define USART_COM1_IRQHandler 			  USART1_IRQHandler
#define USART_COM1_Prio					   0

/**
 * @brief Definition for COM port2, connected to USART2
 */ 
#define USART_COM2                        USART2
#define USART_COM2_CLK                    RCC_APB1Periph_USART2
#define USART_COM2_TX_PIN                 GPIO_Pin_2
#define USART_COM2_TX_GPIO_PORT           GPIOA
#define USART_COM2_TX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define USART_COM2_RX_PIN                 GPIO_Pin_3
#define USART_COM2_RX_GPIO_PORT           GPIOA
#define USART_COM2_RX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define USART_COM2_IRQn                   USART2_IRQn
#define USART_COM2_IRQHandler 			  USART2_IRQHandler
#define  USART_COM2_Prio					   1

typedef enum 
{
  	COM1 = 0,
  	COM2 = 1
}
COM_TypeDef;   

#define USART_Transmit(n)		USART1_Transmit(n)

void USART1_Init(u32 baud_rate);
void USART2_Init(u32 baud_rate);

void USART1_Transmit(u8 ch_data);
void USART2_Transmit(u8 ch_data);

void USART1_RxIntHandler(void);
void USART2_RxIntHandler(void);

void USART_Debug(u8 debug_data);
void USART_SendLine(s32 Data ,
					u8 Is_H, 
				    u8 Line_ID);
void USART_SendString(unsigned char *p_STR);

u8 USART_GetChar(u8* p_array, u8 frame_len);
u8 USART_GetRate(s32* p_rate);

///////////////////////////////
//调试用串口打印函数
void Prints(const u8 * pd);
void PrintLongInt(u32 x);
void PrintShortIntHex(u16 x);
void PrintHex(u8 x);

///////////////////////////////
#endif
