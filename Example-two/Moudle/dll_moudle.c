/**
  ******************************************************************************
  * @file    dll_moudle.c 
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

#define __DLL_MOUDLE_C_

/******************************** Includes ************************************/
#include "dll_moudle.h"


/***************************** Private typedef ********************************/

/***************************** Private define *********************************/
#define LIST_SIZE       100

/****************************** Private macro *********************************/

/**************************** Private variables *******************************/

/**

            ---------- THE DOUBLY LINKED LIST'S ARCHITECTURE --------------


               HEAD            NODE1            NODE2            NODE3

             -------          -------          -------          -------
            |       |        |       |        |       |        |       |
    NULL<---+-pPrev |<-------+-pPrev |<-------+-pPrev |<-------+-pPrev |
            |       |        |       |        |       |        |       |
             -------          -------          -------          -------
            |       |        |       |        |       |        |       |
            | pNext-+------->| pNext-+------->| pNext-+------->| pNext-+--->NULL
            |       |        |       |        |       |        |       |
             -------          -------          -------          -------
            |*******|        |       |        |       |        |       |
            |* NOT *|        |  DATA |        |  DATA |        |  DATA |
            |* USE *|        | AREA  |        | AREA  |        | AREA  |
            |*******|        |       |        |       |        |       |
             -------          -------          -------          -------
**/
/* List[0] & List[1] as  HeadNode */
LISTNODE List[LIST_SIZE];   

LISTNODE *pHead_Former = NULL;            //链表List_Former的头节点指针

LISTNODE *pHead_Present = NULL;           //链表List_Present的头节点指针

/*********************** Private function prototypes **************************/

/**************************** Private functions *******************************/

/** @funcname  Dll_Init
  * @brief     Init the doubly linked list. 
  * @param     Node.
  * @retval    Node.
  */
void Dll_Init(void)
{
    uint8_t Cnt;
	List[0].pPrev = NULL;
	List[0].pNext = NULL;
    List[0].Existed = 0x0;
	List[0].Occupied = 0x01;
    for(Cnt=0; Cnt<12; Cnt++)
    {
        List[0].Data[Cnt] = 0xAA;
    }
    pHead_Present = &List[0];
    
    List[1].pPrev = NULL;
	List[1].pNext = NULL;
    List[1].Existed = 0x0;
	List[1].Occupied = 0x01;
    for(Cnt=0; Cnt<12; Cnt++)
    {
        List[1].Data[Cnt] = 0xAA;
    }
    pHead_Former = &List[1];
}



/** @funcname  Create_Node
  * @brief     Create a node of list. 
  * @param     pHead: Pointer to the list's headnode. 
  *            pData: Pointer to data memery that is used to initialize 
  *            the node's data area.
  * @retval    The new node's pointer.
  */
LISTNODE *Create_Node(LISTNODE *pHead, uint8_t *pData)
{
    uint8_t Pos = 0;
    
    //在数组中找到空闲的节点
    for (Pos=0; Pos<LIST_SIZE; Pos++)
    {
        if (pHead[Pos].Occupied == 0x0)
        {
            break;
        }
    }
    if (Pos >= LIST_SIZE)
    {
        return NULL;
    }
    
    //将此空闲节点的已占用标志位置位
    pHead[Pos].Occupied = 0x01;
    pHead[Pos].Existed = 0x0;
    
    //初始化节点指针
    pHead[Pos].pPrev= NULL;
    pHead[Pos].pNext= NULL;
    
    //将此空闲节点的数据区填充为指定的数据
    ByteCopy(&(pHead[Pos].Data[0]), pData, EPC_ID_SIZE);

    
    //将此空闲节点的地址返回
    return (&pHead[Pos]);
}


/** @funcname  Insert_Tail
  * @brief     Insert a new node to a specified list's head. 
  * @param     pHead: Pointer to the list's headnode.
  *            New: The pointer of new node that is to be inserted.
  * @retval    The BCC code.
  */
void Insert_Tail(LISTNODE *pHead, LISTNODE *New)
{
	while (NULL != pHead->pNext)
	{
		pHead = pHead->pNext;
	}
	
	pHead->pNext = New;	
    New->pPrev = pHead;
}


/** @funcname  Delete_Node
  * @brief     Delete a node in the list. 
  * @param     pByte: Pointer to a byte buffer that is used to store
  *            the framedata.
  *            size: The size of framedata.
  * @retval    The BCC code.
  */
// uint8_t Delete_Node(LISTNODE *pHead, LISTNODE *pNode)
// {
//     if (NULL == pNode->pPrev)  //是否处于表头
//     {
//         if (NULL == pNode->pNext)//是否处于表尾
//         {
//             //只有一个节点，既是表头又是表尾
//             pTail = NULL;
//         }
//         else
//         {
//             //处于表头，非表尾
//             pNode->pNext->pPrev = NULL;
//         }
//         
//         pHead = pNode->pNext;
//     }
//     else
//     {
//         pNode->pPrev->pNext = pNode->pNext;
//         
//         if (NULL == pNode->pNext)//是否处于表尾
//         {
//             //不处于表头，处于表尾
//             pTail = pNode->pPrev;
//         }
//         else
//         {
//              //不处于表头，不处于表尾。 既是中间的节点
//             pNode->pNext->pPrev = pNode->pPrev;
//         }
//     }
//     
//     return 0;
// }
  
  

/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
