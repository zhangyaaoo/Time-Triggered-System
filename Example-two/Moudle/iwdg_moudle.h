/**
  ******************************************************************************
  * @file    iwdg_moudle.h 
  * @author  ZS
  * @version 
  * @date    28-Aug-1993
  * @brief   Header for iwdg_moudle.c module
  ******************************************************************************
  * @attention
  *
  * 
  *
  ******************************************************************************
  */
 
/**************** Define to prevent recursive inclusion ***********************/
#ifndef __IWDG_MOUDLE_H_
#define __IWDG_MOUDLE_H_

#ifdef __IWDG_MOUDLE_C_
#define IWDG_MOUDLE_EXT
#else 
#define IWDG_MOUDLE_EXT extern
#endif


/****************************** Includes **************************************/
#include "main.h"

/************************** Exported types ************************************/

/************************* Exported constants *********************************/

/************************** Exported macro ************************************/

/************************* Exported functions *********************************/
IWDG_MOUDLE_EXT void IWDG_Task  (void);


#endif /* __IWDG_MOUDLE_H_ */

/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
