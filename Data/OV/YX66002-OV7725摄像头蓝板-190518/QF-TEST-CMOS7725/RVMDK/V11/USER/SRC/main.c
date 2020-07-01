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


#include <stm32f10x.h>
#include <stdio.h>
#include <usart.h>
#include <Nvic_Exit.h>
#include <delay.h>
#include <tft.h>
#include <ov7725.h>
#include<I2C.h>

typedef enum {TRUE = 0, FALSE = !TRUE} bool; 

void RCC_Configuration(void);
void CLK_generate(void);

main()
{ 
	RCC_Configuration();//系统时钟设置
	delay_init(72);		//延时初始化
	USART1_Init(115200);//串口1初始化 
	CLK_generate(); 
 	printf("QF: You are welcom!\r\n");	

	GpioInit(GPIOA, GPIO_Pin_11, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);	//CMOS_CS
	GpioInit(GPIOC, GPIO_Pin_13, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);   	//WriteControl

	GpioInit(GPIOC, GPIO_Pin_14, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);   //CMOS2 PWDN
	GpioInit(GPIOC, GPIO_Pin_15, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);	//CMOS2 RST
	Cmos_CS=1;
	WriteControl=1;
	LCD_Init();				  
	LCD_Clear(BLUE);       //清屏 
	POINT_COLOR=YELLOW;
	BACK_COLOR=BLUE;
   	LCD_ShowString(20,50,"QF Welcom");
	LCD_ShowString(20,100,"STM32 Camera");
	LCD_ShowString(20,150,"OV7725 Initing......");
	CMOS2_PWDN=0;
	CMOS2_RST=0;
	delay_ms(20);
	CMOS2_RST=1;
	InitI2C0();
	while(1!=Cmos7725_init());   //CMOS初始化	
	Exit_Init(GPIOC, GPIO_Pin_4, GPIO_Mode_IPU, EXTI_Trigger_Falling, 2, 5);	//VSYNC	
  	while(1) 
	{		  		

	}
}

/*******************************************************************************
* Function Name  : RCC_Configuration 
* Description    : RCC select(external 8MHz)
* Input          : NO
* Output         : NO
* Return         : NO
*******************************************************************************/
void RCC_Configuration(void)
{ 

  ErrorStatus HSEStartUpStatus;
  RCC_DeInit();
  RCC_HSEConfig(RCC_HSE_ON);   
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)	  
  {
  
    RCC_HCLKConfig(RCC_SYSCLK_Div1);  
    RCC_PCLK2Config(RCC_HCLK_Div1);		   
	RCC_PCLK1Config(RCC_HCLK_Div2);	 	  
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);	
    RCC_PLLCmd(ENABLE); 
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)	  
       {
       }
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); 
    while(RCC_GetSYSCLKSource() != 0x08)	  
       { 
       }
     }

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE); 
}

 void CLK_generate(void)
{
	GPIO_InitTypeDef GPIO_InitStructure1;
 	RCC_ClocksTypeDef RCC_Clocks;   	
	GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_AF_PP ; 
	GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure1);  	
	RCC_GetClocksFreq(&RCC_Clocks);  
	RCC_MCOConfig(RCC_MCO_HSE);   

}