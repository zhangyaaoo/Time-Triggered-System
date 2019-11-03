/**
  ******************************************************************************
  * @file    queue_moudle.c 
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

#define __QUEUE_MOUDLE_C_

/******************************** Includes ************************************/
#include "queue_moudle.h"


/***************************** Private typedef ********************************/
/* Frame state */
typedef enum
{
	FRAME_HEAD,         //֡ͷ
	FRAME_CMDID,        //������
	FRAME_SEQUENCE,     //ָ�����к�
	FRAME_RESERVED,     //Ԥ���ֽ�
	FRAME_LENGTH,       //���ݳ���
	FRAME_DATA,         //����
	FRAME_BCC,          //���ݵ�BCCУ��
}FrameState_TypeDef;


/***************************** Private define *********************************/
#define QUEUE_SIZE          256
#define FRAME_MAX_SIZE      23


/****************************** Private macro *********************************/

/**************************** Private variables *******************************/
Qdata USART2_Recv_Queue[QUEUE_SIZE] = {0};
Qsize Queue_Head = 0;
Qsize Queue_Tail = 0;

/*********************** Private function prototypes **************************/
static void Queue_Pop(Qdata *pdata);
static Qsize Get_Queue_Size(void);
static uint8_t Get_BCC(uint8_t *pByte, uint32_t size);

/**************************** Private functions *******************************/

/** @funcname  Get_Frame
  * @brief     Get one frame from the USART2_Recv queue. 
  *            The frame start with '1B'
  * @param     pbuffer: Pointer to a Qdata buffer that is used to store
  *            the frame's data.
  *            buf_len: Pointer to a buffer that is used to store the length of data.
  * @retval    0: Data in the queue is not enough to get a whole frame. *OR* There is an ERROR !!!
  *            1: Get a whole frame successful.
  *
  * @info     
  */
uint8_t Get_Frame(Qdata *pbuffer, Qsize *buf_len)
{
    uint32_t Pop_Cnt = 0;
    Qdata data = 0;
    
    static FrameState_TypeDef FrameState;    
    static Qdata Data_Temp[FRAME_MAX_SIZE] = {0};
    static uint8_t Cnt = 0;
    static UnionHL_TypeDef Len_Data;
    
    while(Get_Queue_Size() > 0)
    {
        Pop_Cnt++;
                
        //���������50���ֽڵ�������Ȼû���γ�һ֡���ݣ�
        //�򷵻ش��� 50 ��������Ը���ʵ������޸�
        //����
        //������ݻ����������򷵻ش���
        if ((Pop_Cnt > 50) || (Cnt >= FRAME_MAX_SIZE))
        {
            ERROR_DEBUG_LED_ON(LED3_PORT,LED3);
            
            FrameState = FRAME_HEAD; 
            Cnt = 0;
            
            return 0; 
        }
        
        //ȡһ������
        Queue_Pop(&data);      
        Data_Temp[Cnt++] = data;
              
        switch (FrameState)
        {
            case FRAME_HEAD:            //֡ͷ
                if (0x1B == data)
                {
                    //���յ�֡ͷ
                    FrameState = FRAME_CMDID; // 1B ?? ?? ...
                }
                else
                {
                    //���û�н��յ�֡ͷ����������֡ͷ
                    Cnt = 0;
                }
       
                break;  
                    
            case FRAME_CMDID:           //������
                if ((0x2A == data) || (0x2B == data))
                {
                    //��������ȷ
                    FrameState = FRAME_SEQUENCE; // 1B 2A(2B) ?? ?? ...
                }
                else
                {
                    //��������������������¿�ʼ��֡ͷ���
                    FrameState = FRAME_HEAD; 
                    Cnt = 0;
                }
                          
                break;
            
            case FRAME_SEQUENCE:        //ָ�����к�
                if ((0x01 == data) || (0x00 == data))
                {
                    //ָ�����к���ȷ
                    FrameState = FRAME_RESERVED; // 1B 2A(2B) 01(00) ?? ??...
                }
                else
                {
                    //���ָ�����кŴ�����������¿�ʼ��֡ͷ���
                    FrameState = FRAME_HEAD; 
                    Cnt = 0;
                }
                
                
                break;
            
            case FRAME_RESERVED:        //Ԥ���ֽ�
                if (0x00 == data)
                {
                     //Ԥ���ֽ���ȷ
                    FrameState = FRAME_LENGTH; // 1B 2A(2B) 01(00) 00 ?? ??...
                }
                else
                {
                    //���Ԥ���ֽڴ�����������¿�ʼ��֡ͷ���
                    FrameState = FRAME_HEAD; 
                    Cnt = 0;
                }
                         
                break;
            
            case FRAME_LENGTH:          //���ݳ���
                            
                if (Cnt >= 6)  //���ݳ��Ƚ������
                {
                    Len_Data.byte[0] = Data_Temp[4];
                    Len_Data.byte[1] = Data_Temp[5];
                    
                    //���յ����ݳ��ȵ�ֵֻ������ (0x0010)  ��  (0x0001) �е�һ��
                    if ((Len_Data.HL == 0x0010) || (Len_Data.HL == 0x0001))
                    {
                        // 1B 2A(2B) 01 00 10 00 ?? ??...
                        // * OR *
                        // 1B 2A(2B) 00 00 01 00 ?? ??...
                        *buf_len = (Qsize)Len_Data.HL;
                        FrameState = FRAME_DATA;
                    }
                    else 
                    {
                        //���յ������ݳ����������¿�ʼ��֡ͷ���
                        FrameState = FRAME_HEAD;//���ݳ��ȴ���
                        Cnt = 0;
                    }
                }
                
                break;
            
            case FRAME_DATA:            //����
                
                if (Cnt >= (Len_Data.HL + 6))
                {
                    if ((0x00 == Data_Temp[6]) && (0x2A == Data_Temp[1]) && (0x00 == Data_Temp[2]))
                    {
                        //����ж���Ϊ������  "1B 2A 00 00 01 00 00 00"  ��֡����
                        FrameState = FRAME_HEAD;
                        Cnt = 0;
                    }
                    else
                    {
                        FrameState = FRAME_BCC; // ���ݽ������
                    }
                }

                break;
            
            case FRAME_BCC:             //BCCУ��
                
                FrameState = FRAME_HEAD;
                Cnt = 0;
                
                if (Data_Temp[Len_Data.HL + 6] == Get_BCC(&Data_Temp[6], Len_Data.HL))
                {
                    //BCCУ����ȷ
                    ByteCopy(pbuffer, &Data_Temp[6], Len_Data.HL);
                                        
                    return 1;  //�γ�һ֡���ݷ�����ȷ
                }                        
            
                break;
                
            default:
                break;
        }       
      
    } 
    
    return 0; //���ڽ��ն����е����ݻ������γ�һ֡����
} 

           
  
/** @funcname  Queue_Reset
  * @brief     Reset the queue that receives data from USART2.  
  * @param     None
  * @retval    None
  */
void Queue_Reset(void)
{
    Queue_Head = Queue_Tail = 0;
}


/** @funcname  Queue_Push
  * @brief     Push one data to the queue.  
  * @param     data to be pushed
  * @retval    None
  */
void Queue_Push(Qdata data)
{
    Qsize Position = (Queue_Head+1) % QUEUE_SIZE;
    if(Position != Queue_Tail)      
    {
        //The queue is not full.
        USART2_Recv_Queue[Queue_Head] = data;
        Queue_Head = Position;
    }
}

/** @funcname  Queue_Pop
  * @brief     POP one data from the queue.  
  * @param     Room for the data.
  * @retval    None
  */
static void Queue_Pop(Qdata* pdata)
{
    if(Queue_Tail != Queue_Head)
    {
        //The queue is not empty.
        *pdata = USART2_Recv_Queue[Queue_Tail];
        Queue_Tail = (Queue_Tail + 1) % QUEUE_SIZE;
    }
}

/** @funcname  Get_Queue_Size
  * @brief     Get the quantity of data stored in the queue.  
  * @param     Room for the data.
  * @retval    None
  */
static Qsize Get_Queue_Size(void)
{
    return ((Queue_Head + QUEUE_SIZE - Queue_Tail) % QUEUE_SIZE);
}

/** @funcname  Get_BCC
  * @brief     Get BCC check code. 
  * @param     pByte: Pointer to a byte buffer that is used to store
  *            the framedata.
  *            size: The size of framedata.
  * @retval    The BCC code.
  */
static uint8_t Get_BCC(uint8_t* pByte, uint32_t size)
{
    uint8_t i = 0, c = 0;
    
    for (i=0; i<size; i++)
    {
        c ^= pByte[i];
    }
    
    return c;
};  


/** @funcname  ByteCopy
  * @brief     This function copies n bytes from memory area src to memory area dest.
  *            The memory areas must not overlap.
  * @param     dest: Pointer to memory area dest.
  *            src: Pointer to memory area src.
  *            nBytes: The amount of byte.
  * @retval    Return the pointer to memory area dest.
  */
void *ByteCopy(void *dest, const void *src, uint32_t nBytes)
{   
    uint8_t *pdest = (uint8_t *)dest;
    uint8_t *psrc  = (uint8_t *)src;
    
    if ((NULL == dest) || (NULL == src))
    {
        return NULL;
    }
      
    while (nBytes--)
    {
        *pdest++ = *psrc++;
    }
   
    return (void *)dest;
};  


/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
