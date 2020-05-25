

/* Includes ------------------------------------------------------------------*/
#include "RA8875.h"

/*********************************************************************//**
 * @brief 		Delay
 * @param[in]	delayCnt Delay value
 * @return 		None
 **********************************************************************/
void delay(uint32_t delayCnt)
{
	uint32_t i;

	for ( i = 0; i < delayCnt; i++ );
	return;
}

void LCD_Reset(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	uint32_t i;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOH, &GPIO_InitStructure);	 
	GPIOH->BSRRH = GPIO_Pin_2;	
	for(i = 0; i < 1000000; i++);
	GPIOH->BSRRL = GPIO_Pin_2;
}

void LCD_Mode8080(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOI, &GPIO_InitStructure);
	GPIOI->BSRRH = GPIO_Pin_8;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOE, &GPIO_InitStructure);	
	GPIOE->BSRRH = GPIO_Pin_6;			 // 8080
}

void FSMC_Init(void)
{
  FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef  p;
  GPIO_InitTypeDef GPIO_InitStructure; 
  
  /* Enable GPIOs clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF |
                         RCC_AHB1Periph_GPIOG, ENABLE);

  /* Enable FSMC clock */
  RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE); 
  
/*-- GPIOs Configuration ------------------------------------------------------*/
/*
 +-------------------+--------------------+------------------+------------------+
 +                       SRAM pins assignment                                  +
 +-------------------+--------------------+------------------+------------------+
 | PD0  <-> FSMC_D2  | PE0  <-> FSMC_NBL0 | PF0  <-> FSMC_A0 | PG0 <-> FSMC_A10 |
 | PD1  <-> FSMC_D3  | PE1  <-> FSMC_NBL1 | PF1  <-> FSMC_A1 | PG1 <-> FSMC_A11 |
 | PD4  <-> FSMC_NOE | PE7  <-> FSMC_D4   | PF2  <-> FSMC_A2 | PG2 <-> FSMC_A12 |
 | PD5  <-> FSMC_NWE | PE8  <-> FSMC_D5   | PF3  <-> FSMC_A3 | PG3 <-> FSMC_A13 |
 | PD8  <-> FSMC_D13 | PE9  <-> FSMC_D6   | PF4  <-> FSMC_A4 | PG4 <-> FSMC_A14 |
 | PD9  <-> FSMC_D14 | PE10 <-> FSMC_D7   | PF5  <-> FSMC_A5 | PG5 <-> FSMC_A15 |
 | PD10 <-> FSMC_D15 | PE11 <-> FSMC_D8   | PF12 <-> FSMC_A6 | PG9 <-> FSMC_NE2 |
 | PD11 <-> FSMC_A16 | PE12 <-> FSMC_D9   | PF13 <-> FSMC_A7 |------------------+
 | PD12 <-> FSMC_A17 | PE13 <-> FSMC_D10  | PF14 <-> FSMC_A8 | PG10 <-> FSMC_NE3
 | PD14 <-> FSMC_D0  | PE14 <-> FSMC_D11  | PF15 <-> FSMC_A9 | PG12 <-> FSMC_NE4
 | PD15 <-> FSMC_D1  | PE15 <-> FSMC_D12  |------------------+
 +-------------------+--------------------+
 PD7 <-> FSMC_NE1
*/
  /* GPIOD configuration */
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_FSMC);
	//GPIO_PinAFConfig(GPIOD, GPIO_PinSource7, GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FSMC);
  //GPIO_PinAFConfig(GPIOD, GPIO_PinSource11, GPIO_AF_FSMC); 
  //GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FSMC);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | //GPIO_Pin_7 |
                                GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | //GPIO_Pin_11 |
                                /*GPIO_Pin_12 |*/ GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;

  GPIO_Init(GPIOD, &GPIO_InitStructure);


  /* GPIOE configuration */
  //GPIO_PinAFConfig(GPIOE, GPIO_PinSource0 , GPIO_AF_FSMC);
  //GPIO_PinAFConfig(GPIOE, GPIO_PinSource1 , GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource7 , GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource8 , GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource9 , GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource10 , GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource11 , GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource12 , GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource13 , GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource14 , GPIO_AF_FSMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource15 , GPIO_AF_FSMC);

  GPIO_InitStructure.GPIO_Pin = /*GPIO_Pin_0  | GPIO_Pin_1 |*/ GPIO_Pin_7 |
                                GPIO_Pin_8  | GPIO_Pin_9  | GPIO_Pin_10 | GPIO_Pin_11|
                                GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;

  GPIO_Init(GPIOE, &GPIO_InitStructure);


  /* GPIOF configuration */
  GPIO_PinAFConfig(GPIOF, GPIO_PinSource0 , GPIO_AF_FSMC);
//   GPIO_PinAFConfig(GPIOF, GPIO_PinSource1 , GPIO_AF_FSMC);
//   GPIO_PinAFConfig(GPIOF, GPIO_PinSource2 , GPIO_AF_FSMC);
//   GPIO_PinAFConfig(GPIOF, GPIO_PinSource3 , GPIO_AF_FSMC);
//   GPIO_PinAFConfig(GPIOF, GPIO_PinSource4 , GPIO_AF_FSMC);
//   GPIO_PinAFConfig(GPIOF, GPIO_PinSource5 , GPIO_AF_FSMC);
//   GPIO_PinAFConfig(GPIOF, GPIO_PinSource12 , GPIO_AF_FSMC);
//   GPIO_PinAFConfig(GPIOF, GPIO_PinSource13 , GPIO_AF_FSMC);
//   GPIO_PinAFConfig(GPIOF, GPIO_PinSource14 , GPIO_AF_FSMC);
//   GPIO_PinAFConfig(GPIOF, GPIO_PinSource15 , GPIO_AF_FSMC);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 /* | GPIO_Pin_1  | GPIO_Pin_2  | GPIO_Pin_3 | 
                                GPIO_Pin_4  | GPIO_Pin_5  | 
                                GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15*/;      

  GPIO_Init(GPIOF, &GPIO_InitStructure);


  /* GPIOG configuration */
//   GPIO_PinAFConfig(GPIOG, GPIO_PinSource0 , GPIO_AF_FSMC);
//   GPIO_PinAFConfig(GPIOG, GPIO_PinSource1 , GPIO_AF_FSMC);
//   GPIO_PinAFConfig(GPIOG, GPIO_PinSource2 , GPIO_AF_FSMC);
//   GPIO_PinAFConfig(GPIOG, GPIO_PinSource3 , GPIO_AF_FSMC);
//   GPIO_PinAFConfig(GPIOG, GPIO_PinSource4 , GPIO_AF_FSMC);
//   GPIO_PinAFConfig(GPIOG, GPIO_PinSource5 , GPIO_AF_FSMC);
//   GPIO_PinAFConfig(GPIOG, GPIO_PinSource9 , GPIO_AF_FSMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource10 , GPIO_AF_FSMC);

  GPIO_InitStructure.GPIO_Pin = /*GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_2  | GPIO_Pin_3 | 
                                GPIO_Pin_4  | GPIO_Pin_5  |*/GPIO_Pin_10;//  |GPIO_Pin_12;      

  GPIO_Init(GPIOG, &GPIO_InitStructure);

/*-- FSMC Configuration ------------------------------------------------------*/
  p.FSMC_AddressSetupTime = 5;
  p.FSMC_AddressHoldTime = 0;
  p.FSMC_DataSetupTime = 9;
  p.FSMC_BusTurnAroundDuration = 0;
  p.FSMC_CLKDivision = 0;
  p.FSMC_DataLatency = 0;
  p.FSMC_AccessMode = FSMC_AccessMode_A;
//   p.FSMC_AddressSetupTime = 0x5;
//   p.FSMC_AddressHoldTime = 0x7;
//   p.FSMC_DataSetupTime = 0x7;
//   p.FSMC_BusTurnAroundDuration = 0x00;
//   p.FSMC_CLKDivision = 0x00;
//   p.FSMC_DataLatency = 0x00;
//   p.FSMC_AccessMode = FSMC_AccessMode_B;
//   p.FSMC_AddressSetupTime = 0;
//   p.FSMC_AddressHoldTime = 0;
//   p.FSMC_DataSetupTime = 4;
//   p.FSMC_BusTurnAroundDuration = 1;
//   p.FSMC_CLKDivision = 0;
//   p.FSMC_DataLatency = 0;
//   p.FSMC_AccessMode = FSMC_AccessMode_A;

  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM3;
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p;

  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 

  /*!< Enable FSMC Bank1_SRAM3 Bank */
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM3, ENABLE); 	
}

void LCD_DataWrite(uint16_t reg, uint16_t data)
{
	LCD->LCD_REG = reg;
  LCD->LCD_RAM = data;	
}

void LCD_DDRAMWrite(uint32_t count, const uint16_t *data)
{
	uint32_t i;
	
	LCD->LCD_REG = 0x02;
	for(i = 0; i < count; i++)
		LCD->LCD_RAM = data[i];
}

uint16_t LCD_DataRead(uint16_t reg)
{
	LCD->LCD_REG = reg;
  return (LCD->LCD_RAM);	
}

void LCD_Init(void)
{
	LCD_DataWrite(0x88, 0x0A);
	delay(1000);
	LCD_DataWrite(0x89, 0x02);
	delay(1000);
	
	LCD_DataWrite(0x04, 0x82);  // PCLK
	delay(1000);

	//Horizontal set
	LCD_DataWrite(0x14, 0x3B);  // 
	LCD_DataWrite(0x15, 0x00);
	LCD_DataWrite(0x16, 0x01);
	LCD_DataWrite(0x17, 0x00);
	LCD_DataWrite(0x18, 0x05);

	//Vertical  set
	LCD_DataWrite(0x19, 0x0F);  // 
	LCD_DataWrite(0x1A, 0x01);
	LCD_DataWrite(0x1B, 0x02);
	LCD_DataWrite(0x1C, 0x00);
	LCD_DataWrite(0x1D, 0x07);
	LCD_DataWrite(0x1E, 0x00);
	LCD_DataWrite(0x1F, 0x09);



// 	//setting active window X
// 	LCD_DataWrite(0x30, 0x00);  // 
// 	LCD_DataWrite(0x31, 0x00);
// 	LCD_DataWrite(0x34, 0xDF);
// 	LCD_DataWrite(0x35, 0x01);
// 	
// 	//setting active window Y
// 	LCD_DataWrite(0x32, 0x00);  // 
// 	LCD_DataWrite(0x33, 0x00);
// 	LCD_DataWrite(0x36, 0x0F);
// 	LCD_DataWrite(0x37, 0x01);	
	

	LCD_DataWrite(0x10, 0x0F);  // SYSR 16-bit interface, 65k colors
}

void Active_Window(uint16_t XL,uint16_t XR ,uint16_t YT ,uint16_t YB)
{
	LCD_DataWrite(0x30, XL);
	LCD_DataWrite(0x31, XL >> 8);
	
	LCD_DataWrite(0x34, XR);
	LCD_DataWrite(0x35, XR >> 8);
	
	LCD_DataWrite(0x32, YT);
	LCD_DataWrite(0x33, YT >> 8);
	
	LCD_DataWrite(0x36, YB);
	LCD_DataWrite(0x37, YB >> 8);
}

void Set_CursPositon(uint16_t X, uint16_t Y)
{
	LCD_DataWrite(0x80, X);
	LCD_DataWrite(0x81, X >> 8);
	
	LCD_DataWrite(0x82, Y);
	LCD_DataWrite(0x83, Y >> 8);
}

void Display_ON(void)
{
	LCD_DataWrite(0x01, 0x80);
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
