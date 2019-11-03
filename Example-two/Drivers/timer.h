/**
  ******************************************************************************
  * @file    timer.h 
  * @author  ZS
  * @version 
  * @date    05-DEC-2016
  * @brief   Header for timer.c module
  ******************************************************************************
  * @attention
  *
  * 
  *
  ******************************************************************************
  */
 
/**************** Define to prevent recursive inclusion ***********************/
#ifndef __TIMER_H_
#define __TIMER_H_

#ifdef __TIMER_C_
#define TIMER_EXT
#else 
#define TIMER_EXT extern
#endif


/****************************** Includes **************************************/
#include "stm32f10x.h"
#include "Task_Scheduler.h"
//#include "led.h"

/************************** Exported types ************************************/

/************************* Exported constants *********************************/

/************************** Exported macro ************************************/

/************************* Exported functions *********************************/
TIMER_EXT void TIM2_Config          (void);
TIMER_EXT void TIM2_IRQHandler      (void);





#endif /* __TIMER_H_ */

/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
