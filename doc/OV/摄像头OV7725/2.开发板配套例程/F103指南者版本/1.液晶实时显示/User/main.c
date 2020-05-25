/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   摄像头火眼ov7725测试例程
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 F103-指南者 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f10x.h"
#include "./ov7725/bsp_ov7725.h"
#include "./lcd/bsp_ili9341_lcd.h"
#include "./led/bsp_led.h"   
#include "./usart/bsp_usart.h"
#include "./key/bsp_key.h"  
#include "./systick/bsp_SysTick.h"

extern uint8_t Ov7725_vsync;

unsigned int Task_Delay[NumOfTask]; 


extern OV7725_MODE_PARAM cam_mode;


/**
  * @brief  主函数
  * @param  无  
  * @retval 无
  */
int main(void) 	
{		
	
	float frame_count = 0;
	uint8_t retry = 0;

	/* 液晶初始化 */
	ILI9341_Init();
	ILI9341_GramScan ( 3 );
	
	LCD_SetFont(&Font8x16);
	LCD_SetColors(RED,BLACK);

  ILI9341_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);	/* 清屏，显示全黑 */
	
	/********显示字符串示例*******/
  ILI9341_DispStringLine_EN(LINE(0),"BH OV7725 Test Demo");

	USART_Config();
	LED_GPIO_Config();
	Key_GPIO_Config();
	SysTick_Init();
	printf("\r\n ** OV7725摄像头实时液晶显示例程** \r\n"); 
	
	/* ov7725 gpio 初始化 */
	OV7725_GPIO_Config();
	
	LED_BLUE;
	/* ov7725 寄存器默认配置初始化 */
	while(OV7725_Init() != SUCCESS)
	{
		retry++;
		if(retry>5)
		{
			printf("\r\n没有检测到OV7725摄像头\r\n");
			ILI9341_DispStringLine_EN(LINE(2),"No OV7725 module detected!");
			while(1);
		}
	}


	/*根据摄像头参数组配置模式*/
	OV7725_Special_Effect(cam_mode.effect);
	/*光照模式*/
	OV7725_Light_Mode(cam_mode.light_mode);
	/*饱和度*/
	OV7725_Color_Saturation(cam_mode.saturation);
	/*光照度*/
	OV7725_Brightness(cam_mode.brightness);
	/*对比度*/
	OV7725_Contrast(cam_mode.contrast);
	/*特殊效果*/
	OV7725_Special_Effect(cam_mode.effect);
	
	/*设置图像采样及模式大小*/
	OV7725_Window_Set(cam_mode.cam_sx,
														cam_mode.cam_sy,
														cam_mode.cam_width,
														cam_mode.cam_height,
														cam_mode.QVGA_VGA);

	/* 设置液晶扫描模式 */
	ILI9341_GramScan( cam_mode.lcd_scan );
	
	
	
	ILI9341_DispStringLine_EN(LINE(2),"OV7725 initialize success!");
	printf("\r\nOV7725摄像头初始化完成\r\n");
	
	Ov7725_vsync = 0;
	
	while(1)
	{
		/*接收到新图像进行显示*/
		if( Ov7725_vsync == 2 )
		{
			frame_count++;
			FIFO_PREPARE;  			/*FIFO准备*/					
			ImagDisp(cam_mode.lcd_sx,
								cam_mode.lcd_sy,
								cam_mode.cam_width,
								cam_mode.cam_height);			/*采集并显示*/
			
			Ov7725_vsync = 0;			
			LED1_TOGGLE;

		}
		
		/*检测按键*/
		if( Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON  )
		{
			/*LED反转*/
			LED2_TOGGLE;

		} 
		/*检测按键*/
		if( Key_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == KEY_ON  )
		{
			/*LED反转*/
			LED3_TOGGLE;			
			
				/*动态配置摄像头的模式，
			    有需要可以添加使用串口、用户界面下拉选择框等方式修改这些变量，
			    达到程序运行时更改摄像头模式的目的*/
			
				cam_mode.QVGA_VGA = 0,	//QVGA模式
				cam_mode.cam_sx = 0,
				cam_mode.cam_sy = 0,	

				cam_mode.cam_width = 320,
				cam_mode.cam_height = 240,

				cam_mode.lcd_sx = 0,
				cam_mode.lcd_sy = 0,
				cam_mode.lcd_scan = 3, //LCD扫描模式，本横屏配置可用1、3、5、7模式

				//以下可根据自己的需要调整，参数范围见结构体类型定义	
				cam_mode.light_mode = 0,//自动光照模式
				cam_mode.saturation = 0,	
				cam_mode.brightness = 0,
				cam_mode.contrast = 0,
				cam_mode.effect = 1,		//黑白模式
			
			/*根据摄像头参数写入配置*/
			OV7725_Special_Effect(cam_mode.effect);
			/*光照模式*/
			OV7725_Light_Mode(cam_mode.light_mode);
			/*饱和度*/
			OV7725_Color_Saturation(cam_mode.saturation);
			/*光照度*/
			OV7725_Brightness(cam_mode.brightness);
			/*对比度*/
			OV7725_Contrast(cam_mode.contrast);
			/*特殊效果*/
			OV7725_Special_Effect(cam_mode.effect);
			
			/*设置图像采样及模式大小*/
			OV7725_Window_Set(cam_mode.cam_sx,
																cam_mode.cam_sy,
																cam_mode.cam_width,
																cam_mode.cam_height,
																cam_mode.QVGA_VGA);

			/* 设置液晶扫描模式 */
			ILI9341_GramScan( cam_mode.lcd_scan );
		}
		
		/*每隔一段时间计算一次帧率*/
		if(Task_Delay[0] == 0)  
		{			
			printf("\r\nframe_ate = %.2f fps\r\n",frame_count/10);
			frame_count = 0;
			Task_Delay[0] = 10000;
		}
		
	}
}




/*********************************************END OF FILE**********************/

