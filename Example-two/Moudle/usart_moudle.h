/**
  ******************************************************************************
  * @file    usart_moudle.h 
  * @author  ZS
  * @version 
  * @date    28-Aug-1993
  * @brief   Header for usart_moudle.c module
  ******************************************************************************
  * @attention
  *
  * 
  *
  ******************************************************************************
  */
 
/**************** Define to prevent recursive inclusion ***********************/
#ifndef __USART_MOUDLE_H_
#define __USART_MOUDLE_H_

#ifdef __USART_MOUDLE_C_
#define USART_MOUDLE_EXT
#else 
#define USART_MOUDLE_EXT extern
#endif


/****************************** Includes **************************************/
#include "main.h"



/************************** Exported types ************************************/
/**
  * USARTx_Out_Queue 
  */
typedef struct USARTx_Out_Queue 
{
    uint8_t        *pBuf;
    uint32_t        Written_Index;
    uint32_t        Waiting_Index;
}tUSARTx_Out_Queue;

/**
  * USART2_SEND_CMD 
  */
typedef enum
{
	USART2_SEND_START,          //LCDµôµç×´Ì¬
    USART2_SEND_STOP,           //LCDµôµç×´Ì¬
}tUSART2_SEND_CMD;


/************************* Exported constants *********************************/

/************************** Exported macro ************************************/

/************************* Exported functions *********************************/
USART_MOUDLE_EXT void USART1_SEND_Task                  (void);
USART_MOUDLE_EXT void USART_SEND_Task                   (void);
USART_MOUDLE_EXT void USART2_RECV_Task                  (void);
USART_MOUDLE_EXT uint8_t Write_Byte_To_USART2_OutBuf    (const uint8_t byte);
USART_MOUDLE_EXT uint8_t Write_nByte_To_USART2_OutBuf   (const uint8_t* const pBuff, uint32_t nByte);


#endif /* __USART_MOUDLE_H_ */

/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
