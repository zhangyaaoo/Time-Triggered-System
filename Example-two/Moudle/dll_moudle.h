/**
  ******************************************************************************
  * @file    dll_moudle.h 
  * @author  ZS
  * @version 
  * @date    28-Aug-1993
  * @brief   Header for dll_moudle.c module
  ******************************************************************************
  * @attention
  *
  * 
  *
  ******************************************************************************
  */
 
/**************** Define to prevent recursive inclusion ***********************/
#ifndef __DLL_MOUDLE_H_
#define __DLL_MOUDLE_H_

#ifdef __DLL_MOUDLE_C_
#define DLL_MOUDLE_EXT
#else 
#define DLL_MOUDLE_EXT extern
#endif


/****************************** Includes **************************************/
//#include "main.h"
#include "stm32f10x.h"
#include "queue_moudle.h"



/************************** Exported types ************************************/
typedef struct ListNode 
{
    uint8_t Occupied;   //该节点是否在使用的标志位  
    uint8_t Existed;    //用于两链表比较时的标志位
    uint8_t Data[12];   //存储标签数据的数组
    struct  ListNode *pPrev;
    struct  ListNode *pNext;
}LISTNODE;            //存储标签数据的链表的节点定义


DLL_MOUDLE_EXT LISTNODE *pHead_Former;            //链表List_Former的头节点指针
// LISTNODE *pTail_Former;            //链表List_Former的尾节点指针

DLL_MOUDLE_EXT LISTNODE *pHead_Present;           //链表List_Present的头节点指针
// LISTNODE *pTail_Present;           //链表List_Present的尾节点指针



/* List[0] & List[1] as  HeadNode */
DLL_MOUDLE_EXT LISTNODE List[];      //保存标签数据节点的数组


/************************* Exported constants *********************************/

/************************** Exported macro ************************************/

/************************* Exported functions *********************************/
DLL_MOUDLE_EXT void         Dll_Init        (void);
DLL_MOUDLE_EXT LISTNODE    *Create_Node     (LISTNODE *pHead, uint8_t *pData);
DLL_MOUDLE_EXT void         Insert_Tail     (LISTNODE *pHead, LISTNODE *New);
// DLL_MOUDLE_EXT uint8_t Delete_Node(LISTNODE *pHead, LISTNODE *pNode);





#endif /* __DLL_MOUDLE_H_ */

/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
