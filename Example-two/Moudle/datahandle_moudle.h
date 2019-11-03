/**
  ******************************************************************************
  * @file    datahandle_moudle.h 
  * @author  ZS
  * @version 
  * @date    28-Aug-1993
  * @brief   Header for datahandle_moudle.c module
  ******************************************************************************
  * @attention
  *
  * 
  *
  ******************************************************************************
  */
 
/**************** Define to prevent recursive inclusion ***********************/
#ifndef __DATAHANDLE_MOUDLE_H_
#define __DATAHANDLE_MOUDLE_H_

#ifdef __DATAHANDLE_MOUDLE_C_
#define DATAHANDLE_MOUDLE_EXT
#else 
#define DATAHANDLE_MOUDLE_EXT extern
#endif


/****************************** Includes **************************************/
#include "main.h"

/************************** Exported types ************************************/
DATAHANDLE_MOUDLE_EXT uint32_t Scan_Round_Cnt;


/************************* Exported constants *********************************/

/************************** Exported macro ************************************/

/************************* Exported functions *********************************/
DATAHANDLE_MOUDLE_EXT void      RFID_DataHandle_Task    (void);





#endif /* __DATAHANDLE_MOUDLE_H_ */

/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
