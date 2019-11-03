/**
  ******************************************************************************
  * @file    iwdg.h 
  * @author  ZS
  * @version 
  * @date    28-Aug-1993
  * @brief   Header for iwdg.c module
  ******************************************************************************
  * @attention
  *
  * 
  *
  ******************************************************************************
  */
 
/**************** Define to prevent recursive inclusion ***********************/
#ifndef __IWDG_H_
#define __IWDG_H_

#ifdef __IWDG_C_
#define IWDG_EXT
#else 
#define IWDG_EXT extern
#endif


/****************************** Includes **************************************/
#include "stm32f10x.h"

/************************** Exported types ************************************/

/************************* Exported constants *********************************/

/************************** Exported macro ************************************/

/************************* Exported functions *********************************/
IWDG_EXT void IWDG_Config   (uint8_t IWDG_Prescaler, uint16_t Reload_Value);
IWDG_EXT void IWDG_Feed     (void);



#endif /* __IWDG_H_ */

/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
