/**
  ******************************************************************************
  * @file    input_moudle.h 
  * @author  ZS
  * @version 
  * @date    06-DEC-2016
  * @brief   Header for input_moudle.c module
  ******************************************************************************
  * @attention
  *
  * 
  *
  ******************************************************************************
  */
 
/**************** Define to prevent recursive inclusion ***********************/
#ifndef __INPUT_MOUDLE_H_
#define __INPUT_MOUDLE_H_

#ifdef __INPUT_MOUDLE_C_
#define INPUT_MOUDLE_EXT
#else 
#define INPUT_MOUDLE_EXT extern
#endif


/****************************** Includes **************************************/
#include "main.h"

/************************* Exported variables *********************************/
extern uint32_t Door1_Closing, Door2_Closing;

extern sTaskTCB *TASK_USART2SEND;

extern uint8_t StartCMD_Buf[];
extern uint8_t StopCMD_Buf[];

/************************** Exported types ************************************/

/************************* Exported constants *********************************/

/************************** Exported macro ************************************/

/************************* Exported functions *********************************/
INPUT_MOUDLE_EXT void GPIO_Input_Task               (void);





#endif /* __INPUT_MOUDLE_H_ */

/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
