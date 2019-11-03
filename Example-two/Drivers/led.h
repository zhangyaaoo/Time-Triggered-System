/**
  ******************************************************************************
  * @file    led.h 
  * @author  ZS
  * @version 
  * @date    28-Aug-1993
  * @brief   Header for led.c module
  ******************************************************************************
  * @attention
  *
  * 
  *
  ******************************************************************************
  */
 
/**************** Define to prevent recursive inclusion ***********************/
#ifndef __LED_H_
#define __LED_H_

#ifdef __LED_C_
#define LED_EXT
#else 
#define LED_EXT extern
#endif


/****************************** Includes **************************************/
#include "stm32f10x.h"

/************************** Exported types ************************************/

/************************* Exported constants *********************************/

/************************** Exported macro ************************************/
#define LED_PORT_CLK   (RCC_APB2Periph_GPIOB)
#define LED1_PORT_CLK  (RCC_APB2Periph_GPIOB)
#define LED2_PORT_CLK  (RCC_APB2Periph_GPIOB)
#define LED3_PORT_CLK  (RCC_APB2Periph_GPIOB)
#define LED4_PORT_CLK  (RCC_APB2Periph_GPIOB)

#define LED_PORT       (GPIOB)
#define LED1_PORT      (GPIOB)
#define LED2_PORT      (GPIOB)
#define LED3_PORT      (GPIOB)
#define LED4_PORT      (GPIOB)


#define LED1           (GPIO_Pin_15)
#define LED2           (GPIO_Pin_14)
#define LED3           (GPIO_Pin_13)
#define LED4           (GPIO_Pin_12)

/************************* Exported functions *********************************/
void LED_Init   (void);
void SetLedOFF  (GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void SetLedON   (GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void SetLedTurn (GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void SetAllOFF  (void);
void SetAllON   (void);





#endif /* __LED_H_ */

/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
