/**
  ******************************************************************************
  * @file    rs485_moudle.h 
  * @author  ZS
  * @version 
  * @date    28-Aug-1993
  * @brief   Header for rs485_moudle.c module
  ******************************************************************************
  * @attention
  *
  * 
  *
  ******************************************************************************
  */
 
/**************** Define to prevent recursive inclusion ***********************/
#ifndef __RS485_MOUDLE_H_
#define __RS485_MOUDLE_H_

#ifdef __RS485_MOUDLE_C_
#define RS485_MOUDLE_EXT
#else 
#define RS485_MOUDLE_EXT extern
#endif


/****************************** Includes **************************************/
#include "main.h"

/************************** Exported types ************************************/

/************************* Exported constants *********************************/

/************************** Exported macro ************************************/
#define RS485EN_PORT_CLK         (RCC_APB2Periph_GPIOB)
#define RS485EN_PORT             (GPIOB)
#define RS485EN_PIN              (GPIO_Pin_1)



/************************* Exported functions *********************************/
RS485_MOUDLE_EXT void RS485_Task(void);


RS485_MOUDLE_EXT void RS485_Config(void);
RS485_MOUDLE_EXT void RS485_IN(void);
RS485_MOUDLE_EXT void RS485_OUT(void);
RS485_MOUDLE_EXT void RS485_SendData(uint8_t *buffer, uint8_t count);


#endif /* __RS485_MOUDLE_H_ */

/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
