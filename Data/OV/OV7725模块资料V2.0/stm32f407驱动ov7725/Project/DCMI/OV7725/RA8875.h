/**
  ******************************************************************************
  * @file    stm322xg_eval_fsmc_sram.h
  * @author  MCD Application Team
  * @version V4.6.1
  * @date    18-April-2011
  * @brief   This file contains all the functions prototypes for the 
  *          stm322xg_eval_fsmc_sram.c driver.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/


#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
	 
typedef struct
{
  __IO uint16_t LCD_RAM;
	__IO uint16_t LCD_REG;
} LCD_TypeDef;
     
#define Bank1_SRAM1_ADDR  ((uint32_t)0x60000000)
#define Bank1_SRAM2_ADDR  ((uint32_t)0x64000000) 
#define Bank1_SRAM3_ADDR  ((uint32_t)0x68000000)
#define Bank1_SRAM4_ADDR  ((uint32_t)0x6C000000)

#define LCD_BASE           Bank1_SRAM3_ADDR
#define LCD                ((LCD_TypeDef *) LCD_BASE)
	 
#define RA8755_CMD_ADDR	(volatile uint16_t *)(Bank1_SRAM3_ADDR | 2)
#define RA8755_DATA_ADDR	(volatile uint16_t *)(Bank1_SRAM3_ADDR | 0)
	 


void LCD_Mode8080(void);
void LCD_Reset(void);
void FSMC_Init(void);
void LCD_DataWrite(uint16_t reg, uint16_t data);
void LCD_DDRAMWrite(uint32_t count, const uint16_t *data);
uint16_t LCD_DataRead(uint16_t reg);
void LCD_Init(void);
void Active_Window(uint16_t XL,uint16_t XR ,uint16_t YT ,uint16_t YB);
void Set_CursPositon(uint16_t X, uint16_t Y);
void Display_ON(void);





//////////////////////////////////////////////////////////////////////////////////	 
void NOR_Init(void);
uint32_t NORFLASHCheckID( void );
void NORFLASHErase( void );
uint32_t NORFLASHWriteWord( uint32_t Addr, uint16_t Data );

#ifdef __cplusplus
}
#endif




/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
