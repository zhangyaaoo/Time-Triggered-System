/**
  ******************************************************************************
  * @file    gpio.c 
  * @author  ZS
  * @version 
  * @date    06-DEC-2016
  * @brief   
  ******************************************************************************
  * @attention
  *
  * 
  *
  ******************************************************************************
  */

#define __GPIO_C_

/******************************** Includes ************************************/
#include "gpio.h"


/***************************** Private typedef ********************************/

/***************************** Private define *********************************/

/****************************** Private macro *********************************/

/**************************** Private variables *******************************/

/*********************** Private function prototypes **************************/

/**************************** Private functions *******************************/

/** @funcname  GPIO_Config
  * @brief     Initialize the GPIO input ports.  
  * @param     None
  * @retval    None
  */
void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /* GPIOD Periph clock enable */
    RCC_APB2PeriphClockCmd(GPIO_PORT_CLK, ENABLE);

    /* Configure PD0 and PD2 in output pushpull mode */
    GPIO_InitStructure.GPIO_Pin = GPIO1 | GPIO2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIO_PORT, &GPIO_InitStructure);
}  


  

/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
