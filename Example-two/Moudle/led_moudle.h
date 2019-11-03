/**
  ******************************************************************************
  * @file    lcd.h 
  * @author  ZS
  * @version 
  * @date    20-Oct-2016
  * @brief   Header for lcd.c module
  ******************************************************************************
  * @attention
  *
  * 
  *
  ******************************************************************************
  */
 
/**************** Define to prevent recursive inclusion ***********************/
#ifndef __LED_MOUDLE_H_
#define __LED_MOUDLE_H_

#ifdef __LED_MOUDLE_C_
#define LED_MOUDLE_EXT
#else 
#define LED_MOUDLE_EXT extern
#endif


/****************************** Includes **************************************/
#include "led.h"


/************************** Exported types ************************************/

/************************* Exported constants *********************************/

/************************** Exported macro ************************************/

/************************* Exported functions *********************************/
LED_MOUDLE_EXT void LED_Twinkle_Task        (void);
LED_MOUDLE_EXT void LED_TurnOff_Task        (void);


#endif /* __LED_MOUDLE_H_ */

/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
