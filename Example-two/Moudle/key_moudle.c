/**
  ******************************************************************************
  * @file    key_moudle.c 
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

#define __KEY_MOUDLE_C_

/******************************** Includes ************************************/
#include "key_moudle.h"


/***************************** Private typedef ********************************/

/***************************** Private define *********************************/

/****************************** Private macro *********************************/

/**************************** Private variables *******************************/

/*********************** Private function prototypes **************************/

/**************************** Private functions *******************************/

/** @funcname  example1
  * @brief     None  
  * @param     None
  * @retval    None
  */
void Key_Service_Task(void)
{
	KEY_Scan(&Key1);
    KEY_Scan(&Key2);
    KEY_Analysisi(&Key1);
    KEY_Analysisi(&Key2);
}  


 
  

/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
