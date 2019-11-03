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
    uint8_t Occupied;   //�ýڵ��Ƿ���ʹ�õı�־λ  
    uint8_t Existed;    //����������Ƚ�ʱ�ı�־λ
    uint8_t Data[12];   //�洢��ǩ���ݵ�����
    struct  ListNode *pPrev;
    struct  ListNode *pNext;
}LISTNODE;            //�洢��ǩ���ݵ�����Ľڵ㶨��


DLL_MOUDLE_EXT LISTNODE *pHead_Former;            //����List_Former��ͷ�ڵ�ָ��
// LISTNODE *pTail_Former;            //����List_Former��β�ڵ�ָ��

DLL_MOUDLE_EXT LISTNODE *pHead_Present;           //����List_Present��ͷ�ڵ�ָ��
// LISTNODE *pTail_Present;           //����List_Present��β�ڵ�ָ��



/* List[0] & List[1] as  HeadNode */
DLL_MOUDLE_EXT LISTNODE List[];      //�����ǩ���ݽڵ������


/************************* Exported constants *********************************/

/************************** Exported macro ************************************/

/************************* Exported functions *********************************/
DLL_MOUDLE_EXT void         Dll_Init        (void);
DLL_MOUDLE_EXT LISTNODE    *Create_Node     (LISTNODE *pHead, uint8_t *pData);
DLL_MOUDLE_EXT void         Insert_Tail     (LISTNODE *pHead, LISTNODE *New);
// DLL_MOUDLE_EXT uint8_t Delete_Node(LISTNODE *pHead, LISTNODE *pNode);





#endif /* __DLL_MOUDLE_H_ */

/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
