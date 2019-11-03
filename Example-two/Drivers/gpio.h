/**
  ******************************************************************************
  * @file    gpio.h 
  * @author  ZS
  * @version 
  * @date    06-DEC-2016
  * @brief   Header for gpio.c module
  ******************************************************************************
  * @attention
  *
  * 
  *
  ******************************************************************************
  */
 
/**************** Define to prevent recursive inclusion ***********************/
#ifndef __GPIO_H_
#define __GPIO_H_

#ifdef __GPIO_C_
#define GPIO_EXT
#else 
#define GPIO_EXT extern
#endif


/****************************** Includes **************************************/
#include "stm32f10x.h"

/************************** Exported types ************************************/

/************************* Exported constants *********************************/

/************************** Exported macro ************************************/
#define GPIO_PORT_CLK   (RCC_APB2Periph_GPIOB)
#define GPIO1_PORT_CLK  (RCC_APB2Periph_GPIOB)
#define GPIO2_PORT_CLK  (RCC_APB2Periph_GPIOB)

#define GPIO_PORT       (GPIOB)
#define GPIO1_PORT      (GPIOB)
#define GPIO2_PORT      (GPIOB)

#define GPIO1           (GPIO_Pin_7)
#define GPIO2           (GPIO_Pin_6)


/************************* Exported functions *********************************/
GPIO_EXT void GPIO_Config       (void);





#endif /* __GPIO_H_ */

/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
