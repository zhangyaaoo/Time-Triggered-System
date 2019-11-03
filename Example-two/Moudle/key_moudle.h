/**
  ******************************************************************************
  * @file    key_moudle.h 
  * @author  ZS
  * @version 
  * @date    28-Aug-1993
  * @brief   Header for key_moudle.c module
  ******************************************************************************
  * @attention
  *
  * 
  *
  ******************************************************************************
  */
 
/**************** Define to prevent recursive inclusion ***********************/
#ifndef __KEY_MOUDLE_H_
#define __KEY_MOUDLE_H_

#ifdef __KEY_MOUDLE_C_
#define KEY_MOUDLE_EXT
#else 
#define KEY_MOUDLE_EXT extern
#endif


/****************************** Includes **************************************/
#include "key.h"

/************************** Exported types ************************************/

/************************* Exported constants *********************************/

/************************** Exported macro ************************************/

/************************* Exported functions *********************************/
KEY_MOUDLE_EXT void Key_Service_Task(void);





#endif /* __KEY_MOUDLE_H_ */

/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
