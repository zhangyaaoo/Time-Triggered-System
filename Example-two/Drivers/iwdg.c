/**
  ******************************************************************************
  * @file    iwdg.c 
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

#define __IWDG_C_

/******************************** Includes ************************************/
#include "iwdg.h"


/***************************** Private typedef ********************************/

/***************************** Private define *********************************/

/****************************** Private macro *********************************/

/**************************** Private variables *******************************/

/*********************** Private function prototypes **************************/


/**************************** Private functions *******************************/

/** @funcname  IWDG_Config
  * @brief     Configuration the IWDG.  
  * @param  IWDG_Prescaler: specifies the IWDG Prescaler value.
  *   This parameter can be one of the following values:
  *     @arg IWDG_Prescaler_4:   IWDG prescaler set to 4
  *     @arg IWDG_Prescaler_8:   IWDG prescaler set to 8
  *     @arg IWDG_Prescaler_16:  IWDG prescaler set to 16
  *     @arg IWDG_Prescaler_32:  IWDG prescaler set to 32
  *     @arg IWDG_Prescaler_64:  IWDG prescaler set to 64
  *     @arg IWDG_Prescaler_128: IWDG prescaler set to 128
  *     @arg IWDG_Prescaler_256: IWDG prescaler set to 256
  * @param  Reload_Value: specifies the IWDG Reload value.
  *   This parameter must be a number between 0 and 0x0FFF.
  *
  * @attention
  *                     IWDG_Prescaler * (Reload_Value + 1)
  *  timeout period =  -------------------------------------
  *                                  40KHz
  *  for example: when the IWDG_Prescaler = IWDG_Prescaler_256; 
  *                        Reload_Value   = 0x012B (299D)
  *
  *                     256 * (299 + 1)
  *  timeout period =  ----------------- =  1920ms (1.92s)
  *                         40KHz
  * @retval    None
  */
void IWDG_Config(uint8_t IWDG_Prescaler, uint16_t Reload_Value)
{		
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //使能对寄存器IWDG_PR和IWDG_RLR的写操作
	
	IWDG_SetPrescaler(IWDG_Prescaler);  //设置IWDG预分频值:设置IWDG预分频值为256
	
	IWDG_SetReload(Reload_Value);  //设置IWDG重装载值
	
	IWDG_ReloadCounter();  //按照IWDG重装载寄存器的值重装载IWDG计数器
	
	IWDG_Enable();  //使能IWDG
}



/** @funcname  IWDG_Feed
  * @brief     Reloads IWDG counter with value defined in the reload register.  
  * @param     None
  * @retval    None
  */
void IWDG_Feed(void)
{   
 	IWDG_ReloadCounter();										   
}


/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
