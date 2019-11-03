/**
  ******************************************************************************
  * @file    led_moudle.c 
  * @author  ZS
  * @version 
  * @date    15-Oct-2016
  * @brief   
  ******************************************************************************
  * @attention
  *
  * 
  *
  ******************************************************************************
  */

#define __LED_MOUDLE_C_

/******************************** Includes ************************************/
#include "led_moudle.h"


/***************************** Private typedef ********************************/

/***************************** Private define *********************************/

/****************************** Private macro *********************************/

/***************************** Private typedef ********************************/

/**************************** Private variables *******************************/

/*********************** Private function prototypes **************************/

/**************************** Private functions *******************************/

/** @funcname  LED_Task
  * @brief     None  
  * @param     None
  * @retval    None
  */
void LED_Twinkle_Task(void)
{
    SetLedTurn(LED4_PORT, LED4);
}  


/** @funcname  LED_TurnOff_Task
  * @brief     None  
  * @param     None
  * @retval    None
  */
void LED_TurnOff_Task(void)
{
    SetLedOFF(LED1_PORT, LED1);
    SetLedOFF(LED2_PORT, LED2);
}  



/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
