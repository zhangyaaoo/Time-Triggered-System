/**
  ******************************************************************************
  * @file    usart.c 
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

#define __USART_C_

/******************************** Includes ************************************/
#include "usart.h"


/***************************** Private typedef ********************************/

/***************************** Private define *********************************/

/****************************** Private macro *********************************/

/**************************** Private variables *******************************/

/*********************** Private function prototypes **************************/

/**************************** Private functions *******************************/


/** @funcname  USART1_Config
  * @brief     None  
  * @param     None
  * @retval    None
  */
void USART1_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef  	USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    /* System Clocks Configuration ********************************************/

    /* Enable USART1 Clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO, ENABLE); 
    
    /* Configure the GPIO ports ***********************************************/
    
    /* Configure USART1_Rx(PA10) as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* Configure USART1_Tx(PA9) as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* NVIC configuration *****************************************************/

    /* Configure the NVIC Preemption Priority Bits */  
    //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
    /* Enable the USART2 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* USART2 configuration ***************************************************/
    /* USART2 configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    /* Configure USART2 */
    USART_Init(USART1, &USART_InitStructure);

    /* Enable USART2 Receive interrupts */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);      //使能串口2接收中断
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);     //清除USARTx的中断待处理位
    
	
    /* Enable the USART2 */
	USART_Cmd(USART1, ENABLE);//使能串口2外设	
    
    USART_ClearFlag(USART1, USART_FLAG_TC);             //查询TC，首次清除，避免第一个字节丢失
}  


/** @funcname  USART1_Send_nByte
  * @brief     None  
  * @param     None
  * @retval    None
  */
void USART1_Send_nByte(uint8_t *buffer, uint32_t count)
{
	while(count)
	{ 
        while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET);
        USART_SendData(USART1, *buffer++);  
		count--;
	}
}

/** @funcname  USART1_Send_Byte
  * @brief     串口发送一个字节的数据，如果串口处于忙碌状态则不等待函数直接返回
  *            如果出口不处于忙碌状态，则向串口的发送发送缓冲区写入待发送的数据
  *            函数不等待数据发送
  * @param     
  * @retval    None
  */
uint8_t USART1_Send_Byte(uint8_t buffer)
{
    uint8_t temp = 0;
    
    if (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
    {
        USART_SendData(USART1, buffer);
    }
    else
    {
        temp = 0x01;
    }
    
    return temp;
}


/** @funcname  USART1_RxDone_Detect
  * @brief    
  * @param     
  * @retval    None
  */
void USART1_RxDone_Detect(void)
{
//     uint8_t temp = 0;
    

}



/** @funcname  USART1_IRQHandler
  * @brief     None  
  * @param     None
  * @retval    None
  */
void USART1_IRQHandler(void)
{
	uint8_t temp1,temp2;
	
	temp1 = USART1->SR; //读出状态寄存器(USART_FLAG_RXNE)
	
	if (temp1 & 0x20) //判断是否接收非空
	{
		
        temp2 = USART_ReceiveData(USART1); //如果是其他错误标志进来中断，则执行读操作		

	}
	else
	{
		temp2 = USART_ReceiveData(USART1);//如果是其他错误标志进来中断，则执行读操作
		USART1->SR &= 0xC0; //除了TC和TXE其余的清零
		
		/* 防止编译器优化提示变量未使用 */
		temp1++; temp2++; 
	}
}



/** @funcname  USART2_Config
  * @brief     None  
  * @param     None
  * @retval    None
  */
void USART2_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef  	USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    /* System Clocks Configuration ********************************************/

    /* Enable USART2 Clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE); 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    
    /* Configure the GPIO ports ***********************************************/
    
    /* Configure USART2_Rx(PA3) as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* Configure USART2_Tx(PA2) as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* NVIC configuration *****************************************************/

    /* Configure the NVIC Preemption Priority Bits */  
    //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
    /* Enable the USART2 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* USART2 configuration ***************************************************/
    /* USART2 configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    /* Configure USART2 */
    USART_Init(USART2, &USART_InitStructure);

    /* Enable USART2 Receive interrupts */
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);      //使能串口2接收中断
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);     //清除USARTx的中断待处理位
    
	USART_ClearFlag(USART2, USART_FLAG_TC);             //查询TC，首次清除，避免第一个字节丢失
    
    /* Enable the USART2 */
	USART_Cmd(USART2, ENABLE);//使能串口2外设	
}  


/** @funcname  USART2_Send_nByte
  * @brief     None  
  * @param     None
  * @retval    None
  */
void USART2_Send_nByte(uint8_t *buffer, uint32_t count)
{
	while(count)
	{
        
        USART_SendData(USART2, *buffer++);
        while(USART_GetFlagStatus(USART2, USART_FLAG_TC)==RESET);
        
		count--;
	}
}

/** @funcname  USART2_Send_Byte
  * @brief     
  * @param     
  * @retval    
  */
uint8_t USART2_Send_Byte(uint8_t buffer)
{
    uint8_t temp = 0;
    uint16_t TimeOut = 0;
    
    while ((++TimeOut) && (USART_GetFlagStatus(USART2, USART_FLAG_TC)==RESET));
    USART_SendData(USART2, buffer);
       
    if (0 == TimeOut)
    {
        temp = 0x01;
    }
    
    return temp;
}


/** @funcname  USART2_RxDone_Detect
  * @brief    
  * @param     
  * @retval    None
  */
// void USART2_RxDone_Detect(void)
// {
//     /* USART2接收帧结束判断 */
//     if ((0 != UASRT2_RxBusyFlag) && (0 == UASRT2_RxFrameDone))
//     {
//         USART2_Elasping_Cnt += 1;		
//         if (USART2_Elasping_Cnt > 10)
//         {
//             UASRT2_RxFrameDone = 1;
//             USART2_Elasping_Cnt = 0;
//         }
//     }	  

// }

/** @funcname  USART2_IRQHandler
  * @brief     None  
  * @param     None
  * @retval    None
  */
void USART2_IRQHandler(void)
{
	uint8_t temp1;
    uint8_t temp2;
	
	temp1 = USART2->SR; //读出状态寄存器(USART_FLAG_RXNE)
	
	if (temp1 & 0x20) //判断是否接收非空
	{
        temp2 = USART_ReceiveData(USART2);
        Queue_Push(temp2);
	}
	else
	{
		temp2 = USART_ReceiveData(USART2);//如果是其他错误标志进来中断，则执行读操作
		USART2->SR &= 0xC0; //除了TC和TXE其余的清零
		
		/* 防止编译器优化提示变量未使用 */
		temp1++; temp2++; 
	}
}
 

/** @funcname  USART3_Config
  * @brief     None  
  * @param     None
  * @retval    None
  */


void USART3_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef  	USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    /* System Clocks Configuration ********************************************/

    /* Enable USART3 Clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    
    /* Configure the GPIO ports ***********************************************/
    
    /* Configure USART3_Rx(PB11) as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    /* Configure USART3_Tx(PB10) as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    /* NVIC configuration *****************************************************/

    /* Configure the NVIC Preemption Priority Bits */  
    //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
    /* Enable the USART3 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* USART3 configuration ***************************************************/
    /* USART3 configured as follow:
        - BaudRate = 9600 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    /* Configure USART3 */
    USART_Init(USART3, &USART_InitStructure);

    /* Enable USART3 Receive interrupts */
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);      //使能串口3接收中断
	USART_ClearITPendingBit(USART3, USART_IT_RXNE);     //清除USARTx的中断待处理位
    
	USART_ClearFlag(USART3, USART_FLAG_TC);             //查询TC，首次清除，避免第一个字节丢失
    
    /* Enable the USART3 */
	USART_Cmd(USART3, ENABLE);//使能串口2外设	
}  


/** @funcname  USART3_Send_nByte
  * @brief     None  
  * @param     None
  * @retval    None
  */
void USART3_Send_nByte(uint8_t *buffer, uint32_t count)
{
	while(count)
	{ 
        while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==RESET);
        USART_SendData(USART3, *buffer++);  
		count--;
	}
}

/** @funcname  USART3_Send_Byte
  * @brief     串口发送一个字节的数据，如果串口处于忙碌状态则不等待函数直接返回
  *            如果出口不处于忙碌状态，则向串口的发送发送缓冲区写入待发送的数据
  *            函数不等待数据发送
  * @param     
  * @retval    None
  */
uint8_t USART3_Send_Byte(uint8_t buffer)
{
    uint8_t temp = 0;
    
    if (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
    {
        USART_SendData(USART3, buffer);
    }
    else
    {
        temp = 0x01;
    }
    
    return temp;
}


/** @funcname  USART3_RxDone_Detect
  * @brief    
  * @param     
  * @retval    None
  */
void USART3_RxDone_Detect(void)
{
//     uint8_t temp = 0;
    

}



/** @funcname  USART3_IRQHandler
  * @brief     None  
  * @param     None
  * @retval    None
  */
void USART3_IRQHandler(void)
{
	uint8_t temp1,temp2;
	
	temp1 = USART3->SR; //读出状态寄存器(USART_FLAG_RXNE)
	
	if (temp1 & 0x20) //判断是否接收非空
	{
		
        temp2 = USART_ReceiveData(USART3); //如果是其他错误标志进来中断，则执行读操作		

	}
	else
	{
		temp2 = USART_ReceiveData(USART3);//如果是其他错误标志进来中断，则执行读操作
		USART3->SR &= 0xC0; //除了TC和TXE其余的清零
		
		/* 防止编译器优化提示变量未使用 */
		temp1++; temp2++; 
	}
}




/** @funcname  UART4_Config
  * @brief     None  
  * @param     None
  * @retval    None
  */


void UART4_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef  	USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    /* System Clocks Configuration ********************************************/

    /* Enable USART2 Clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE); 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
    
    /* Configure the GPIO ports ***********************************************/
    
    /* Configure UART4_Rx(PC11) as input floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    /* Configure UART4_Tx(PC10) as alternate function push-pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    /* NVIC configuration *****************************************************/

    /* Configure the NVIC Preemption Priority Bits */  
    //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
    /* Enable the UART4 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* UART4 configuration ***************************************************/
    /* UART4 configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    /* Configure UART4 */
    USART_Init(UART4, &USART_InitStructure);

    /* Enable USART2 Receive interrupts */
    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);      //使能串口4接收中断
	USART_ClearITPendingBit(UART4, USART_IT_RXNE);     //清除USARTx的中断待处理位
    
	USART_ClearFlag(UART4, USART_FLAG_TC);             //查询TC，首次清除，避免第一个字节丢失
    
    /* Enable the USART2 */
	USART_Cmd(UART4, ENABLE);//使能串口2外设	
}  


/** @funcname  UART4_Send_nByte
  * @brief     None  
  * @param     None
  * @retval    None
  */
void UART4_Send_nByte(uint8_t *buffer, uint32_t count)
{
	while(count)
	{ 
        while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET);
        USART_SendData(USART1, *buffer++);  
		count--;
	}
}

/** @funcname  UART4_Send_Byte
  * @brief     串口发送一个字节的数据，如果串口处于忙碌状态则不等待函数直接返回
  *            如果出口不处于忙碌状态，则向串口的发送发送缓冲区写入待发送的数据
  *            函数不等待数据发送
  * @param     
  * @retval    None
  */
uint8_t UART4_Send_Byte(uint8_t buffer)
{
    uint8_t temp = 0;
    
    if (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
    {
        USART_SendData(USART1, buffer);
    }
    else
    {
        temp = 0x01;
    }
    
    return temp;
}


/** @funcname  UART4_RxDone_Detect
  * @brief    
  * @param     
  * @retval    None
  */
void UART4_RxDone_Detect(void)
{
//     uint8_t temp = 0;
    

}



/** @funcname  UART4_IRQHandler
  * @brief     None  
  * @param     None
  * @retval    None
  */
void UART4_IRQHandler(void)
{
	uint8_t temp1,temp2;
	
	temp1 = USART1->SR; //读出状态寄存器(USART_FLAG_RXNE)
	
	if (temp1 & 0x20) //判断是否接收非空
	{
		
        temp2 = USART_ReceiveData(USART1); //如果是其他错误标志进来中断，则执行读操作		

	}
	else
	{
		temp2 = USART_ReceiveData(USART1);//如果是其他错误标志进来中断，则执行读操作
		USART1->SR &= 0xC0; //除了TC和TXE其余的清零
		
		/* 防止编译器优化提示变量未使用 */
		temp1++; temp2++; 
	}
}





/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
