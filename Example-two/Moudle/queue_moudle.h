/**
  ******************************************************************************
  * @file    queue_moudle.h 
  * @author  ZS
  * @version 
  * @date    28-Aug-1993
  * @brief   Header for queue_moudle.c module
  ******************************************************************************
  * @attention
  *
  * 
  *
  ******************************************************************************
  */
 
/**************** Define to prevent recursive inclusion ***********************/
#ifndef __QUEUE_MOUDLE_H_
#define __QUEUE_MOUDLE_H_

#ifdef __QUEUE_MOUDLE_C_
#define QUEUE_MOUDLE_EXT
#else 
#define QUEUE_MOUDLE_EXT extern
#endif


/****************************** Includes **************************************/
//#include "main.h"
#include "stm32f10x.h"
#include "led_moudle.h"
#include "usart_moudle.h"
#include "Task_Scheduler.h"

#include "debug.h"

/************************** Exported types ************************************/
typedef union UnionHighByteAndLowByte
{
    u16 HL;          //字型数据
	u8 byte[2];      //高低字节放置数组
}UnionHL_TypeDef;

typedef unsigned char   Qdata;
typedef unsigned int    Qsize;




/************************* Exported constants *********************************/

/************************** Exported macro ************************************/
#define EPC_ID_SIZE         12



/************************* Exported functions *********************************/
QUEUE_MOUDLE_EXT void       Queue_Reset (void);
QUEUE_MOUDLE_EXT void       Queue_Push  (Qdata data);
QUEUE_MOUDLE_EXT uint8_t    Get_Frame   (Qdata *pbuffer, Qsize *buf_len);
QUEUE_MOUDLE_EXT void *     ByteCopy    (void *dest, const void *src, uint32_t nBytes);


#endif /* __QUEUE_MOUDLE_H_ */

/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
