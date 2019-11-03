/**
  ******************************************************************************
  * @file    input_moudle.c 
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

#define __INPUT_MOUDLE_C_

/******************************** Includes ************************************/
#include "input_moudle.h"


/***************************** Private typedef ********************************/

/***************************** Private define *********************************/

/****************************** Private macro *********************************/

/**************************** Private variables *******************************/
static uint8_t Input1_Previous = 1, Input1_Now = 1; //Door1��ӳ������ŴŴ����������Գ�ʼ��״̬Ϊ1
//static uint8_t Input2_Previous = 0, Input2_Now = 0; //Door2��ӳ��յ��ŴŴ����������Գ�ʼ��״̬Ϊ0

uint8_t StartCMD_Buf[7] = {0x1B, 0x2A, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t StopCMD_Buf[7]  = {0x1B, 0x2B, 0x00, 0x00, 0x00, 0x00, 0x00};

               
uint32_t Door1_Closing = 0, Door2_Closing = 0;  


/*********************** Private function prototypes **************************/

/**************************** Private functions *******************************/

/** @funcname  GPIO_Input_Task
  * @brief     None  
  * @param     None
  * @retval    None
  */
void GPIO_Input_Task(void)
{
    Input1_Previous = Input1_Now;
    Input1_Now = GPIO_ReadInputDataBit(GPIO1_PORT,GPIO1);
    
//     Input2_Previous = Input2_Now;
//     Input2_Now = GPIO_ReadInputDataBit(GPIO2_PORT,GPIO2); 

    
    //Door1�ӵĳ������ŴŴ�������MCU���Ŷ����ߵ�ƽ��ʾ�Ŵ��ڹ�״̬
    //                           MCU���Ŷ����͵�ƽ��ʾ�Ŵ��ڿ�״̬
    if ((Input1_Previous == (uint8_t)0) && (Input1_Now != (uint8_t)0))
    {
        TIME_ELAPSE_DEBUG_LED_ON(LED1_PORT,LED1);
        
        Door1_Closing = 1;
        //��⵽�ſ��Ժ�ѭ��ɨ��  4  �κ�ֹͣɨ��
        Scan_Round_Cnt += 4;
        Write_nByte_To_USART2_OutBuf(StartCMD_Buf, 7);
        SCH_Enable_Task(TASK_USART2SEND);
        
        TIME_ELAPSE_DEBUG_LED_OFF(LED1_PORT,LED1);
    }
    
    
//     //Door2�ӵĳ��յ��ŴŴ�������MCU���Ŷ����ߵ�ƽ��ʾ�Ŵ��ڿ�״̬
//     //                           MCU���Ŷ����͵�ƽ��ʾ�Ŵ��ڹ�״̬
//     if ((Input2_Previous != (uint8_t)0) && (Input2_Now == (uint8_t)0))
//     {
//         Door2_Closing = 1;
//         SetLedON(LED2_PORT,LED2);
//     }
}  

 

/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
