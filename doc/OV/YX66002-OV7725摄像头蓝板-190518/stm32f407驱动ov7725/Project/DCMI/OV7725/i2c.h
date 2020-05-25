

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm324xg_eval.h"



#ifndef I2C_SPEED
 #define I2C_SPEED                        10000
#endif /* I2C_SPEED */

#define I2C_SLAVE_ADDRESS7      0xC0

#define OV_ADDRESS  0x42 // for OV7670



void OV_I2C_Init(void);
void OV_Reg_Set(uint8_t reg, uint8_t data);
uint8_t OV_Reg_Get(uint8_t reg);


#ifdef __cplusplus
}
#endif




/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/


