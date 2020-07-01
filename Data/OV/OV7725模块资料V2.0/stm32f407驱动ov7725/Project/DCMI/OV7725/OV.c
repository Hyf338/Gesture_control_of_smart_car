
#include "ov.h"
#include "i2c.h"

/* QVGA 360x240 */
static unsigned char OV_QVGA[][2]=
{
	{0x32,0x00},
	{0x2a,0x00},
	{0x11,0x03},
	{0x12,0x46},//QVGA RGB565
	
	{0x42,0x7f},
	{0x4d,0x00},
	{0x63,0xf0},
	{0x64,0x1f},
	{0x65,0x20},
	{0x66,0x00},
	{0x67,0x00},
	{0x69,0x50},  
	
	
	{0x13,0xff},
	{0x0d,0x41},
	{0x0f,0x01},
	{0x14,0x06},
	
	{0x24,0x75},
	{0x25,0x63},
	{0x26,0xd1},
	{0x2b,0xff},
	{0x6b,0xaa},
	
	{0x8e,0x10},
	{0x8f,0x00},
	{0x90,0x00},
	{0x91,0x00},
	{0x92,0x00},
	{0x93,0x00},
	
	{0x94,0x2c},
	{0x95,0x24},
	{0x96,0x08},
	{0x97,0x14},
	{0x98,0x24},
	{0x99,0x38},
	{0x9a,0x9e},
	{0x15,0x00}, 
	{0x9b,0x00},
	{0x9c,0x20},
	{0xa7,0x40},  
	{0xa8,0x40},
	{0xa9,0x80},
	{0xaa,0x80},
	
	{0x9e,0x81},
	{0xa6,0x06},
	
	{0x7e,0x0c},
	{0x7f,0x16},
	{0x80,0x2a},
	{0x81,0x4e},
	{0x82,0x61},
	{0x83,0x6f},
	{0x84,0x7b},
	{0x85,0x86},
	{0x86,0x8e},
	{0x87,0x97},
	{0x88,0xa4},
	{0x89,0xaf},
	{0x8a,0xc5},
	{0x8b,0xd7},
	{0x8c,0xe8},
	{0x8d,0x20},
	
	{0x33,0x40},
	{0x34,0x00},
	{0x22,0xaf},
	{0x23,0x01},
	
	{0x49,0x10},
	{0x4a,0x10},
	{0x4b,0x14},
	{0x4c,0x17},
	{0x46,0x05},
	
	{0x47,0x08},
	{0x0e,0x01},
	{0x0c,0x60},
	{0x09,0x03},
	
	{0x29,0x50},
	{0x2C,0x78},
	
	{0x00,0x00},
	{0x00,0x00},
	{0x00,0x60},   				

};



void OV_HW_Init(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;
//  I2C_InitTypeDef  I2C_InitStruct;

  /*** Configures the DCMI GPIOs to interface with the OV9655 camera module ***/
  /* Enable DCMI GPIOs clocks */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOH |
                         RCC_AHB1Periph_GPIOI, ENABLE);
	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);

  /* Connect DCMI pins to AF13 */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_DCMI);

  GPIO_PinAFConfig(GPIOH, GPIO_PinSource8, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource9, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource10, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource11, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource12, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource14, GPIO_AF_DCMI);

  GPIO_PinAFConfig(GPIOI, GPIO_PinSource5, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource6, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource7, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource4, GPIO_AF_DCMI);
  
  /* DCMI GPIO configuration */
  /* D0..D4(PH9/10/11/12/14), HSYNC(PH8) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |
                                GPIO_Pin_12 | GPIO_Pin_14| GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOH, &GPIO_InitStructure);

  /* D5..D7(PI4/6/7), VSYNC(PI5) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_5;
  GPIO_Init(GPIOI, &GPIO_InitStructure);

  /* PCLK(PA6) */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  /* Connect DCMI pins to AF13 */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_DCMI);

  GPIO_PinAFConfig(GPIOH, GPIO_PinSource8, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource9, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource10, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource11, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource12, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOH, GPIO_PinSource14, GPIO_AF_DCMI);

  GPIO_PinAFConfig(GPIOI, GPIO_PinSource5, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource6, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource7, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOI, GPIO_PinSource4, GPIO_AF_DCMI);
}

void OV_Reset(void)
{
  uint32_t i;
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOF, &GPIO_InitStructure);	
	GPIOF->BSRRH = GPIO_Pin_10;
	for(i=0;i<100000;i++);
	GPIOF->BSRRL = GPIO_Pin_10;	
}

void OV_Init(void)
{
  DCMI_InitTypeDef DCMI_InitStructure;
  DMA_InitTypeDef  DMA_InitStructure;

  /*** Configures the DCMI to interface with the OV camera module ***/
  /* Enable DCMI clock */
  RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);

  /* DCMI configuration */ 
  DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_Continuous;
  DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;
  DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Falling;
  DCMI_InitStructure.DCMI_VSPolarity = DCMI_VSPolarity_High;
  DCMI_InitStructure.DCMI_HSPolarity = DCMI_HSPolarity_High;
  //DCMI_InitStructure.DCMI_VSPolarity = DCMI_VSPolarity_Low;
  //DCMI_InitStructure.DCMI_HSPolarity = DCMI_HSPolarity_Low;
  DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;
  DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;

  /* Configures the DMA2 to transfer Data from DCMI */
  /* Enable DMA2 clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
  
  /* DMA2 Stream1 Configuration */
  DMA_DeInit(DMA2_Stream1);

  DMA_InitStructure.DMA_Channel = DMA_Channel_1;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = DCMI_DR_ADDRESS;	
  DMA_InitStructure.DMA_Memory0BaseAddr = FSMC_LCD_ADDRESS;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = 1;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

  /* DCMI configuration */
  DCMI_Init(&DCMI_InitStructure);

  /* DMA2 IRQ channel Configuration */
  DMA_Init(DMA2_Stream1, &DMA_InitStructure);       
}

void OV_QVGAConfig(void)
{
  uint32_t i, j;

  OV_Reset();
  for(i = 0; i < 10000; i++);

  /* Initialize OV */
	for(i=0; i<(sizeof(OV_QVGA)/2); i++)
  {
    OV_Reg_Set(OV_QVGA[i][0], OV_QVGA[i][1]);
    for(j = 0; j < 1000; j++);
  }
}






void Camera_Config(void)
{
	uint32_t i;
	
  /* Configure the OV camera and set the QVGA mode */
	OV_HW_Init();
  	OV_Init();
 	OV_QVGAConfig();
	

}
