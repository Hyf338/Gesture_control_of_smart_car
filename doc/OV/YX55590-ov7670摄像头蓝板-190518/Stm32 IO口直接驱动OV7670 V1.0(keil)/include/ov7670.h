#ifndef _OV7660_H
#define _OV7660_H


#include "SCCB.h"



#define LCD_HREF_BIT    GPIO_Pin_8 //接口PC8
#define LCD_XCLK_BIT    GPIO_Pin_8 //接口PA8
#define LCD_VSYNC_BIT   GPIO_Pin_11	 //接口PC11
#define LCD_PCLK_BIT    GPIO_Pin_9	 //接口PC9


#define XCLK_H	        GPIOA->BSRR =  GPIO_Pin_8;
#define XCLK_L		    GPIOA->BRR =   GPIO_Pin_8;

#define LCD_PCLK_STATE    GPIOC->IDR&0x0200
#define LCD_HREF_STATE    GPIOC->IDR&0x0100
#define LCD_VSYNC_STATE_H GPIOC->IDR&0x0800
#define LCD_VSYNC_STATE_L (~GPIOC->IDR)&0x0800;

#define GPIOC_CRL		    GPIOC->BRR =0x0000; 

/////////////////////////////////////////
void CLK_init_ON(void);
void CLK_init_OFF(void);
unsigned char wrOV7660Reg(unsigned char regID, unsigned char regDat);
unsigned char rdOV7660Reg(unsigned char regID, unsigned char *regDat);
void OV7660_config_window(unsigned int startx,unsigned int starty,unsigned int width, unsigned int height);
unsigned char OV7660_init(void);
void ov7660_GPIO_Init(void);
//void ov7660_GPIO_CONTRL_CONFIG(void)

#endif /* _OV7660_H */



