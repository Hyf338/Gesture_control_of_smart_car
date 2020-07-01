/**
  ******************************************************************************
  * @file    I2S/Audio/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-April-2011
  * @brief   Main program body
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
  */ 

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "RA8875.h"
#include "ov.h"

uint32_t test = 0;

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{ 
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f2xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f2xx.c file
     */
  uint32_t i;
	
  OV_Reset();

  STM_EVAL_LEDInit(LED1);
  STM_EVAL_LEDInit(LED2);
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
	
	LCD_Reset();
	FSMC_Init();
	LCD_Mode8080( ); 
	LCD_Init();
	Active_Window(0, 799, 0, 479);
	Display_ON();
	LCD_DataWrite(0x8A, 1<<6);
	Set_CursPositon(0,0);
	LCD->LCD_REG = 0x02;
	for(i=0;i<480*800;i++) LCD->LCD_RAM = 0x00;

	OV_I2C_Init();
	// for OV7670
	if((OV_Reg_Get(0x1C) != 0x7F) || (OV_Reg_Get(0x1D) != 0xA2)  // factory ID
		|| (OV_Reg_Get(0x0A) != 0x76))  // PID
	while(1);
	for(i = 0; i < 1000; i++);

	Camera_Config();

  /* Enable DMA2 stream 1 and DCMI interface then start image capture */
  DMA_Cmd(DMA2_Stream1, ENABLE); 
  DCMI_Cmd(ENABLE);
	
	for(i = 0; i < 10000000; i++);
	
	DCMI_CaptureCmd(ENABLE);
	Set_CursPositon(0,0);
	Active_Window(0, 319, 0, 239);
	LCD->LCD_REG = 0x02;
	
	while(1);
}


  
/***************************************************************END OF FILE****/
