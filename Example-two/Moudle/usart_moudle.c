/**
  ******************************************************************************
  * @file    usart_moudle.c 
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

#define __USART_MOUDLE_C_

/******************************** Includes ************************************/
#include "usart_moudle.h"


/***************************** Private typedef ********************************/

/***************************** Private define *********************************/
#define EACHTIME_USART2_SEND_CNT        3
#define USART2_SENDOUT_BUF_LENGTH       50
#define UART4_SENDOUT_BUF_LENGTH        50
/****************************** Private macro *********************************/

/**************************** Private variables *******************************/
tUSART2_SEND_CMD USART2_SEND_CMD;

uint8_t     USART2_SendOut_Buf[USART2_SENDOUT_BUF_LENGTH] = {0x0};
uint8_t     UART4_SendOut_Buf[UART4_SENDOUT_BUF_LENGTH] = {0x0};

tUSARTx_Out_Queue USART2_Out_Queue;
tUSARTx_Out_Queue UART4_Out_Queue;





uint8_t buffer[22] = {0x1B, 0x2A, 0x01, 0x00, 0x10, 0x00, 0xE3, 0x2D, 0x77, 0xFC, 0xA1, 
					  0x20, 0x15, 0x09, 0x25, 0x01, 0xC1, 0x67, 0x29, 0xA1, 0x00, 0x01};

/*********************** Private function prototypes **************************/

/**************************** Private functions *******************************/


/** @funcname  USART1_SEND_Task
  * @brief     None  
  * @param     None
  * @retval    None
  */
void USART1_SEND_Task(void)
{   
    //USART1_Send_nByte(buffer, 2);
}



/** @funcname  USART2_SEND_Task
  * @brief     None  
  * @param     None
  * @retval    None
  */
void USART_SEND_Task(void)
{
    uint8_t i;
    /* Deal with transmit bytes here */ 

    TIME_ELAPSE_DEBUG_LED_ON(LED1_PORT,LED1);
    
    for (i=0; i<EACHTIME_USART2_SEND_CNT; i++)
    {
        // Is there any data ready to send?
        if (Out_Written_Index_G < Out_Waiting_Index_G)
        {
            if (USART2_Send_Byte(USART2_SendOut_Buf[Out_Written_Index_G]))
            {
                //USART2 send time out
                SCH_Disable_Task(TASK_USART2SEND);
                break;
            }                
            Out_Written_Index_G++;
        }
        else
        {
            // No data to send - just reset the buffer index
            Out_Waiting_Index_G = 0;
            Out_Written_Index_G = 0;
            
            SCH_Disable_Task(TASK_USART2SEND);
            
            TIME_ELAPSE_DEBUG_LED_OFF(LED1_PORT,LED1);
            
            break;
        } 
    }

    TIME_ELAPSE_DEBUG_LED_OFF(LED1_PORT,LED1);
}  


/** @funcname  USART2_RECV_Task
  * @brief     None  
  * @param     None
  * @retval    None
  */
void USART2_RECV_Task(void)
{
    /* Deal with the recieved data here */ 

    TIME_ELAPSE_DEBUG_LED_ON(LED1_PORT,LED1);
    
    TIME_ELAPSE_DEBUG_LED_OFF(LED1_PORT,LED1);
}  




/** @funcname  Write_Byte_To_USARTx_OutBuf
  * @brief     Stores a byte in the 'write' buffer, ready for 
  *            later transmission.  
  * @param     The byte to be stored.
  * @retval    successful: 0     failed: 1
  */
uint8_t Write_Byte_To_USARTx_OutBuf(tUSARTx_Out_Queue *USARTx, const uint8_t byte)
{
    uint8_t Return_Code = 0;
    
    // Write to the buffer *only* if there is space
    if (USARTx->Out_Waiting_Index < USART2_SENDOUT_BUF_LENGTH)
    {
        USART2_SendOut_Buf[USARTx->Out_Waiting_Index] = byte;
        USARTx->Out_Waiting_Index ++;     
    }
    else
    {
        // Write buffer is full
        // Increase the size of USART2_SENDOUT_BUF_LENGTH
        // or increase the rate at which USART 'update' function is called 
        // or reduce the amount of data sent to PC
        Return_Code = 0x01;
    }
    
    return Return_Code;
}
   
   
  
/** @funcname  Write_nByte_To_USARTx_OutBuf
  * @brief     Copies a (null terminated) string to the character buffer.  
  *            
  * @param     The charcater to be stored.
  * @retval    successful: 0     failed: 1
  */
uint8_t Write_nByte_To_USARTx_OutBuf(tUSARTx_Out_Queue *USARTx, const uint8_t* const pBuff, uint32_t nByte)
{
    uint8_t i = 0, Return_Code = 0;

    while (nByte--)
    {
        if (Write_Byte_To_USARTx_OutBuf(USARTx, pBuff[i]))
        {
            // Write buffer is full
            Return_Code = 0x01;
        }
        i++;
    }
      
    return Return_Code;
}
   


/** @funcname  SendOut_Byte_From_USARTx_OutBuf
  * @brief     Stores a byte in the 'write' buffer, ready for 
  *            later transmission.  
  * @param     The byte to be stored.
  * @retval    successful: 0     failed: 1
  */
uint8_t SendOut_Byte_From_USARTx_OutBuf(tUSARTx_Out_Queue *USARTx)
{
    uint8_t Return_Code = 0;
    
    // Is there any data ready to send?
    if (USARTx->Out_Written_Index < USARTx->Out_Waiting_Index)
    {
        if (USART2_Send_Byte(USART2_SendOut_Buf[USARTx->Out_Written_Index]))
        {
            //USART2 send time out
            //ERROR HANDLING
        }                
        USARTx->Out_Written_Index ++;
    }
    else
    {
        // No data to send - just reset the buffer index
        USARTx->Out_Waiting_Index = 0;
        USARTx->Out_Written_Index = 0;
        
        SCH_Disable_Task(TASK_USART2SEND);
    } 
    
    return Return_Code;
}
   
   
  
/** @funcname  Write_nByte_To_USARTx_OutBuf
  * @brief     Copies a (null terminated) string to the character buffer.  
  *            
  * @param     The charcater to be stored.
  * @retval    successful: 0     failed: 1
  */
uint8_t SendOut_nByte_From_USARTx_OutBuf(tUSARTx_Out_Queue *USARTx, const uint8_t* const pBuff, uint32_t nByte)
{
    uint8_t i = 0, Return_Code = 0;

    while (nByte--)
    {
        if (Write_Byte_To_USARTx_OutBuf(USARTx, pBuff[i]))
        {
            // Write buffer is full
            Return_Code = 0x01;
        }
        i++;
    }
      
    return Return_Code;
}


/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
