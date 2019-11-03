/**
  ******************************************************************************
  * @file    rs485_moudle.c 
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

#define __RS485_MOUDLE_C_

/******************************** Includes ************************************/
#include "rs485_moudle.h"


/***************************** Private typedef ********************************/

/***************************** Private define *********************************/

/****************************** Private macro *********************************/

/**************************** Private variables *******************************/
uint8_t buffer[12] = {0x12, 0x35, 0x65, 0x58, 0x65, 0x62, 0x45, 0x22, 0x11, 0x25, 0x25, 0x25};



/*********************** Private function prototypes **************************/

/**************************** Private functions *******************************/

/** @funcname  RS485_Config
  * @brief     None  
  * @param     None
  * @retval    None
  */
void RS485_Task(void)
{
    RS485_SendData(buffer,12);
}
/** @funcname  RS485_Config
  * @brief     None  
  * @param     None
  * @retval    None
  */
void RS485_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
    
    USART3_Config();
	
	RCC_APB2PeriphClockCmd( RS485EN_PORT_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Pin = RS485EN_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(RS485EN_PORT, &GPIO_InitStructure);	
	
	RS485_OUT();
}

/** @funcname  RS485_IN
  * @brief     None  
  * @param     None
  * @retval    None
  */
void RS485_IN(void)
{
	GPIO_ResetBits(RS485EN_PORT, RS485EN_PIN); /* 设置485使能引脚为接收 */
}

/** @funcname  RS485_OUT
  * @brief     None  
  * @param     None
  * @retval    None
  */
void RS485_OUT(void)
{
	GPIO_SetBits(RS485EN_PORT, RS485EN_PIN);  /* 设置485使能引脚为发送 */
}

/** @funcname  RS485_Config
  * @brief     None  
  * @param     None
  * @retval    None
  */
void RS485_SendData(uint8_t *buffer, uint8_t count)
{
	//RS485_OUT();
	//delay_ms(5);
	USART3_Send_nByte(buffer, count);
	//delay_ms(5);
	//RS485_IN();
}


/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
