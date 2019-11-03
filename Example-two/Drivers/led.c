/**
  ******************************************************************************
  * @file    led.c 
  * @author  ZS
  * @version 
  * @date    05-DEC-2016
  * @brief   
  ******************************************************************************
  * @attention
  *
  * 
  *
  ******************************************************************************
  */

#define __LED_C_

/******************************** Includes ************************************/
#include "led.h"


/***************************** Private typedef ********************************/

/***************************** Private define *********************************/

/****************************** Private macro *********************************/

/**************************** Private variables *******************************/

/*********************** Private function prototypes **************************/

/**************************** Private functions *******************************/

/** @funcname  LED_Init
  * @brief     Initialize the LED ports.  
  * @param     None
  * @retval    None
  */
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /* GPIOD Periph clock enable */
    RCC_APB2PeriphClockCmd(LED_PORT_CLK, ENABLE);

    /* Configure PD0 and PD2 in output pushpull mode */
    GPIO_InitStructure.GPIO_Pin = LED1 | LED2 | LED3 | LED4;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(LED_PORT, &GPIO_InitStructure);
	
	GPIO_SetBits(LED1_PORT,LED1);
	GPIO_SetBits(LED2_PORT,LED2);
 	GPIO_SetBits(LED3_PORT,LED3);
    GPIO_SetBits(LED4_PORT,LED4);
}  


/** @funcname  SetLedOFF
  * @brief     Turn off the LEDx.  
  * @param     LED_Port, LED_Pin
  * @retval    None
  */
void SetLedOFF(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIO_SetBits(GPIOx, GPIO_Pin);
}

/** @funcname  SetLedON
  * @brief     Turn on the LEDx.  
  * @param     LED_Port, LED_Pin
  * @retval    None
  */
void SetLedON(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	GPIO_ResetBits(GPIOx, GPIO_Pin);
}

/** @funcname  SetLedTurn
  * @brief     Turn the LEDx's status.  
  * @param     LED_Port, LED_Pin
  * @retval    None
  */
void SetLedTurn(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	/* Reads the specified pin of the GPIOx and store it in ReadValue variable */ 
	uint8_t ReadValue; 
	ReadValue = GPIO_ReadOutputDataBit(GPIOx, GPIO_Pin);	
	
	if( ReadValue == 1 )
	{
		GPIO_ResetBits(GPIOx, GPIO_Pin);
	}
	else
	{
		GPIO_SetBits(GPIOx, GPIO_Pin);
	}	
}


/** @funcname  SetAllOFF
  * @brief     Turn off all the LED.  
  * @param     None
  * @retval    None
  */
void SetAllOFF(void)
{
    GPIO_SetBits(LED1_PORT, LED1);
    GPIO_SetBits(LED2_PORT, LED2);
    GPIO_SetBits(LED3_PORT, LED3);
    GPIO_SetBits(LED4_PORT, LED4);
}

/** @funcname  SetAllON
  * @brief     Turn on all the LED.  
  * @param     None
  * @retval    None
  */
void SetAllON(void)
{
    GPIO_ResetBits(LED1_PORT, LED1);
    GPIO_ResetBits(LED2_PORT, LED2);
    GPIO_ResetBits(LED3_PORT, LED3);
    GPIO_ResetBits(LED4_PORT, LED4);
} 
  

/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
