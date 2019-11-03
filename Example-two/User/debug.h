/**
  ******************************************************************************
  * @file    debug.h 
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
 
/**************** Define to prevent recursive inclusion ***********************/
#ifndef __DEBUG_H_
#define __DEBUG_H_

#define TIME_ELAPSE_DEBUG

#ifdef TIME_ELAPSE_DEBUG
    #define TIME_ELAPSE_DEBUG_LED_ON(PORT, PIN)  SetLedON((PORT), (PIN))
    #define TIME_ELAPSE_DEBUG_LED_OFF(PORT, PIN) SetLedOFF((PORT), (PIN))
#else
    #define TIME_ELASPE_DEBUG_LED_ON(PORT, PIN)  ((void)0)
    #define TIME_ELASPE_DEBUG_LED_OFF(PORT, PIN) ((void)0)
#endif 



#define ERROR_DEBUG

#ifdef ERROR_DEBUG
    #define ERROR_DEBUG_LED_ON(PORT, PIN)  SetLedON((PORT), (PIN))
    #define ERROR_DEBUG_LED_OFF(PORT, PIN) SetLedOFF((PORT), (PIN))
#else
    #define ERROR_DEBUG_LED_ON(PORT, PIN)  ((void)0)
    #define ERROR_DEBUG_LED_OFF(PORT, PIN) ((void)0)
#endif 




/****************************** Includes **************************************/

/************************** Exported types ************************************/

/************************* Exported constants *********************************/

/************************** Exported macro ************************************/

/************************* Exported functions *********************************/






#endif /* __DEBUG_H_ */

/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
