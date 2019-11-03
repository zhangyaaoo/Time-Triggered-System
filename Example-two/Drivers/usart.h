/**
  ******************************************************************************
  * @file    usart.h 
  * @author  ZS
  * @version 
  * @date    06-DEC-2016
  * @brief   Header for usart.c module
  ******************************************************************************
  * @attention
  *
  * 
  *
  ******************************************************************************
  */
 
/**************** Define to prevent recursive inclusion ***********************/
#ifndef __USART_H_
#define __USART_H_

#ifdef __USART_C_
#define USART_EXT
#else 
#define USART_EXT extern
#endif


/****************************** Includes **************************************/
#include "stm32f10x.h"
#include "datahandle_moudle.h"

/************************** Exported types ************************************/

/************************* Exported constants *********************************/

/************************** Exported macro ************************************/

/************************* Exported functions *********************************/
USART_EXT void      USART1_Config           (void);
USART_EXT void      USART1_Send_nByte       (uint8_t *buffer, uint32_t count);
USART_EXT uint8_t   USART1_Send_Byte        (uint8_t buffer);
USART_EXT void      USART1_IRQHandler       (void);


USART_EXT void      USART2_Config           (void);
USART_EXT void      USART2_Send_nByte       (uint8_t *buffer, uint32_t count);
USART_EXT uint8_t   USART2_Send_Byte        (uint8_t buffer);
USART_EXT void      USART2_IRQHandler       (void);


USART_EXT void      USART3_Config           (void);
USART_EXT void      USART3_Send_nByte       (uint8_t *buffer, uint32_t count);
USART_EXT uint8_t   USART3_Send_Byte        (uint8_t buffer);
USART_EXT void      USART3_IRQHandler       (void);






#endif /* __USART_H_ */

/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
