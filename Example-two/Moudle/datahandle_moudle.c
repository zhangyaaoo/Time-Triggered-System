/**
  ******************************************************************************
  * @file    datahandle_moudle.c 
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

#define __DATAHANDLE_MOUDLE_C_

/******************************** Includes ************************************/
#include "datahandle_moudle.h"


/***************************** Private typedef ********************************/



/***************************** Private define *********************************/
#define FRAME_MAX_SIZE          23
#define DATA_MAX_SIZE           16
#define ID_MAX_SIZE             12

/****************************** Private macro *********************************/

/**************************** Private variables *******************************/
uint32_t Scan_Round_Cnt = 0;
 
/*********************** Private function prototypes **************************/
static uint8_t Byte_Array_Compare(const void *Array1, const void *Array2, uint32_t nBytes);
static uint8_t Frame_Compare(LISTNODE *pHead, Qdata *pBuffer, Qsize Buf_Len);



/**************************** Private functions *******************************/

/** @funcname  USART2_RECV_Task
  * @brief     None  
  * @param     None
  * @retval    None
  */
void RFID_DataHandle_Task(void)
{
    static Qdata Frame_Data[DATA_MAX_SIZE] = {0};
    static Qsize Data_Length = 0;

    /* Deal with the recieved data here */ 

    while (Get_Frame((Qdata *)Frame_Data, &Data_Length))
    {
        TIME_ELAPSE_DEBUG_LED_ON(LED1_PORT,LED1);
               
        //Get a whole frame successfully.
        if (Data_Length == 1)
        {
            if (Frame_Data[0] == 0xA6)
            {
                Write_nByte_To_USART2_OutBuf(StopCMD_Buf, 7);            
                SCH_Enable_Task(TASK_USARTSEND); 
            }
            
            
            if (Frame_Data[0] == 0x00)
            {
                if (--Scan_Round_Cnt)
                {
                    Write_nByte_To_USART2_OutBuf(StartCMD_Buf, 7);
                    SCH_Enable_Task(TASK_USARTSEND);
                } 
                else
                {
                    TIME_ELAPSE_DEBUG_LED_ON(LED2_PORT, LED2);
                }
            }                    
        }
        else if (Data_Length == 16)
        {
            if (Frame_Compare(pHead_Present, Frame_Data, ID_MAX_SIZE))
            {
                //Insert the framedata in list.
                Insert_Tail(pHead_Present, Create_Node(pHead_Present, Frame_Data));
            }
        }
        
        TIME_ELAPSE_DEBUG_LED_OFF(LED1_PORT,LED1);
    }
}


/** @funcname  Frame_Compare
  * @brief     Get one frame from the queue. 
  *            The frame start with '1B'
  * @param     pbuffer: Pointer to a Qdata buffer that is used to store
  *            the framedata.
  *            buf_len: The max length of buffer.
  * @retval    0: have found a same one.
  *            1: not found the same one.
  */
static uint8_t Frame_Compare(LISTNODE *pHead, Qdata *pBuffer, Qsize Buf_Len)
{
    while (NULL != pHead)
    {
        if (Byte_Array_Compare(&(pHead->Data[0]), pBuffer, ID_MAX_SIZE))
        {
            //Equal.
            return 0;
        }
        else
        {
            //Not equal.
            pHead = pHead->pNext;
        }
    }
    return 1;
}

  
/** @funcname  Byte_Array_Compare
  * @brief     Compare two Array. 
  * @param     Array1: Pointer to the first array.
  *            Array2: Pointer to the second array.
  *            nBytes: The length of array.
  * @retval    1: Equal.
  *            0: Not Equal.
  */
static uint8_t Byte_Array_Compare(const void *Array1, const void *Array2, uint32_t nBytes)
{
    uint32_t Cnt;
    uint8_t *p1 = (uint8_t *)Array1;
    uint8_t *p2 = (uint8_t *)Array2;
    
    if ((NULL == Array1) || (NULL == Array2))
    {
        return 0;
    }
    
    p1 = p1 + nBytes -1;
    p2 = p2 + nBytes -1;
    
    for (Cnt=0; Cnt<nBytes; Cnt++)
    {
        if (*p1 == *p2)
        {
            p1--;
            p2--;
        }
        else
        {
            break;
        }
    }
    
    if (Cnt >=nBytes)
    {
        return 1;//All the datas in the two array are equal.
    }
    
    return 0;// Not equal.
}

/** @funcname  List_Compare
  * @brief     Compare two list. 
  * @param     Head_Pre: Pointer to the head node in list present.
  *            Head_For: Pointer to the head node in list former.
  * @retval    None.
  */
static void List_Compare(LISTNODE ** const Head_Pre, LISTNODE ** const Head_For)
{
    LISTNODE *Head_Present = (LISTNODE *)(*Head_Pre);
    LISTNODE *Head_Former  = (LISTNODE *)(*Head_For);
    LISTNODE *pTemp = NULL;
    
    uint8_t Flag = 0;
    
    if ((NULL == Head_Present) || (NULL == Head_Former))
    {
        return;
    }
    
    //跳过头节点
    Head_Present = Head_Present->pNext;
    Head_Former = Head_Former->pNext;
    
    while (NULL != Head_Present)
    {
        while (NULL != Head_Former)
        {
            if (!(Head_Former->Existed))
            {
                //这个节点没有匹配到
                if (Byte_Array_Compare(&(Head_Present->Data[0]), &(Head_Former->Data[0]), ID_MAX_SIZE))
                {
                    Head_Former->Existed = 1;
                    Flag = 1;
                    break;
                }
                else
                {
                    Head_Former = Head_Former->pNext;
                }
            }
            else
            {
                //这个节点已经匹配过相等的节点
                Head_Former = Head_Former->pNext;
            }
        }
        
        if (!(Flag))
        {
            //则  Present  链表当前节点没有找到匹配的节点，视为新放入的节点
            //将相关信息放入WIFI发送队列缓冲里
        }
        
        Flag = 0;       //标志位复位
        Head_Present = Head_Present->pNext;  //Head_Present  指向  Present 链表的下一个节点
        Head_Former = (*Head_For)->pNext;  //Head_Former  复位指向  Former 链表的第一个节点
    }
    
    //if you are here, the compare is complete.
    while (NULL != Head_Former)
    {
        if (!(Head_Former->Existed))
        {
            //如果执行到这里
            //则  Former   链表里的当前节点视为被拿出的节点
            //将相关信息发送到WIFI发送队列里
        }
        Head_Former = Head_Former->pNext;
    }
    
    //将   Former  list  中的  Existed  标志位清零
    
    Head_Former = (*Head_For)->pNext;  //Head_Former  复位指向  Former 链表的第一个节点
    
    while (NULL != Head_Former)
    {
        Head_Former->Existed = 0;
        Head_Former = Head_Former->pNext;
    }
    
    //调换头结点指针
    pTemp = *Head_For;
    *Head_For = *Head_Pre;
    *Head_Pre = pTemp;
}
   




/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
