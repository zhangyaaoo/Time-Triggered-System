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

LISTNODE *pHead_Former = NULL;            //����List_Former��ͷ�ڵ�ָ��

LISTNODE *pHead_Present = NULL;           //����List_Present��ͷ�ڵ�ָ��

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
    
    //���������ҵ����еĽڵ�
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
    
    //���˿��нڵ����ռ�ñ�־λ��λ
    pHead[Pos].Occupied = 0x01;
    pHead[Pos].Existed = 0x0;
    
    //��ʼ���ڵ�ָ��
    pHead[Pos].pPrev= NULL;
    pHead[Pos].pNext= NULL;
    
    //���˿��нڵ�����������Ϊָ��������
    ByteCopy(&(pHead[Pos].Data[0]), pData, EPC_ID_SIZE);

    
    //���˿��нڵ�ĵ�ַ����
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
//     if (NULL == pNode->pPrev)  //�Ƿ��ڱ�ͷ
//     {
//         if (NULL == pNode->pNext)//�Ƿ��ڱ�β
//         {
//             //ֻ��һ���ڵ㣬���Ǳ�ͷ���Ǳ�β
//             pTail = NULL;
//         }
//         else
//         {
//             //���ڱ�ͷ���Ǳ�β
//             pNode->pNext->pPrev = NULL;
//         }
//         
//         pHead = pNode->pNext;
//     }
//     else
//     {
//         pNode->pPrev->pNext = pNode->pNext;
//         
//         if (NULL == pNode->pNext)//�Ƿ��ڱ�β
//         {
//             //�����ڱ�ͷ�����ڱ�β
//             pTail = pNode->pPrev;
//         }
//         else
//         {
//              //�����ڱ�ͷ�������ڱ�β�� �����м�Ľڵ�
//             pNode->pNext->pPrev = pNode->pPrev;
//         }
//     }
//     
//     return 0;
// }
  
  

/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
