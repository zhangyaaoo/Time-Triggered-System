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
static uint8_t Input1_Previous = 1, Input1_Now = 1; //Door1外接常开的门磁传感器，所以初始化状态为1
//static uint8_t Input2_Previous = 0, Input2_Now = 0; //Door2外接常闭的门磁传感器，所以初始化状态为0

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

    
    //Door1接的常开的门磁传感器，MCU引脚读到高电平表示门处于关状态
    //                           MCU引脚读到低电平表示门处于开状态
    if ((Input1_Previous == (uint8_t)0) && (Input1_Now != (uint8_t)0))
    {
        TIME_ELAPSE_DEBUG_LED_ON(LED1_PORT,LED1);
        
        Door1_Closing = 1;
        //检测到门开以后循环扫描  4  次后停止扫描
        Scan_Round_Cnt += 4;
        Write_nByte_To_USART2_OutBuf(StartCMD_Buf, 7);
        SCH_Enable_Task(TASK_USART2SEND);
        
        TIME_ELAPSE_DEBUG_LED_OFF(LED1_PORT,LED1);
    }
    
    
//     //Door2接的常闭的门磁传感器，MCU引脚读到高电平表示门处于开状态
//     //                           MCU引脚读到低电平表示门处于关状态
//     if ((Input2_Previous != (uint8_t)0) && (Input2_Now == (uint8_t)0))
//     {
//         Door2_Closing = 1;
//         SetLedON(LED2_PORT,LED2);
//     }
}  

 

/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
