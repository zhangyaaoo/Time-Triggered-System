/**
  ******************************************************************************
  * @file    iwdg_moudle.c 
  * @author  ZS
  * @version 
  * @date    28-Aug-1993
  * @brief   
  ******************************************************************************
  * @attention
  *
  * 
  *
  ******************************************************************************
  */

#define __IWDG_MOUDLE_C_

/******************************** Includes ************************************/
#include "iwdg_moudle.h"


/***************************** Private typedef ********************************/

/***************************** Private define *********************************/

/****************************** Private macro *********************************/

/**************************** Private variables *******************************/

/*********************** Private function prototypes **************************/


/**************************** Private functions *******************************/

/** @funcname  IWDG_Task
  * @brief     None  
  * @param     None
  * @retval    None
  */
void IWDG_Task(void)
{
    IWDG_Feed();  //Feed the IWDG.
}  


/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
