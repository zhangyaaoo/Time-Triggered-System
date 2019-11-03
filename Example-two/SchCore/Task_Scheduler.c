/************************ (C) COPYRIGHT ZS *************************************
 * �ļ���   ��Task_Scheduler.c
 * ����     �����ʽ������C�ļ�
 * ��汾   ��V1.2.0
 * ԭ����   ��HARRY007  �ο���Michael J. Pont , liubing����
 * ����     : ZS
 * �޸�ʱ�� ��2016-10-13
*******************************************************************************/


/* �����Զ���ͷ�ļ� */
#include "Task_Scheduler.h"

sTaskTCB hSCH_tasks_G[hSCH_MAX_TASKS];

/*******************************************************************************
 * ����: hSCH_Init
 * ����: �����ʼ��
 * �β�: ��
 * ����: ��
 * ˵��: �� 
 ******************************************************************************/
void hSCH_Init(void)
{
    u8 i;
    for(i = 0;i < hSCH_MAX_TASKS;i ++)
    {
        hSCH_tasks_G[i].pTask  = NULL;
        hSCH_tasks_G[i].Delay  = 0;
        hSCH_tasks_G[i].Period = 0;
        hSCH_tasks_G[i].RunMe  = 0;
        hSCH_tasks_G[i].Co_op  = 1;
        hSCH_tasks_G[i].Enable = 0;
    }
}

/*******************************************************************************
 * ����: SCH_Start
 * ����: ��ʼ�������
 * �β�: ��
 * ����: ��
 * ˵��: �� 
 ******************************************************************************/
void SCH_Start(void)
{
    //������������ȵĶ�ʱ�����ն˼���ʼ���������
    
    /* TIM2 enable counter */
    TIM_Cmd(TIM2, ENABLE);
}

/*******************************************************************************
 * ����: hSCH_Dispatch_Tasks
 * ����: �������
 * �β�: ��
 * ����: ��
 * ˵��: ��Ҫ����������������ѭ����
 ******************************************************************************/
void hSCH_Dispatch_Tasks(void)
{
   u8 Index;

    for (Index = 0; Index < hSCH_MAX_TASKS; Index++)//������������
    {
        if ((hSCH_tasks_G[Index].Co_op) && (hSCH_tasks_G[Index].RunMe > 0))  //ĳ�����Ƿ����
        {
            if(hSCH_tasks_G[Index].pTask != NULL)//��Ҫִ�������Ƿ���������
            {
                hSCH_tasks_G[Index].pTask();//ִ������
            }
            hSCH_tasks_G[Index].RunMe -= 1; //����ִ����ɺ��1
        }

        if (hSCH_tasks_G[Index].Period == 0)//�����������Ϊ0����ɾ������
        {
            hSCH_tasks_G[Index].pTask = NULL;//������ɾ��
        }
    }
}  

/*******************************************************************************
 * ����: SCH_Add_Task
 * ����: �������
 * �β�: ������ָ�룬�״ο�ʼִ��ʱ�䣬�������ڣ��������ͣ�����ʹ��
 * ����: �ṹ��ָ��sTaskH
 * ˵��: �����������Ϊ0�����������Ϊ����ִ�е�����ִ��һ�κ󽫱�ɾ��
 ******************************************************************************/
sTaskTCB *SCH_Add_Task(TASK_SCH *pFunction, u32 DELAY, u32 PERIOD,u8 task_mode,u8 ENABLE)  
{
    static u8 Index = 0;
    if (Index < hSCH_MAX_TASKS)
    {    
        hSCH_tasks_G[Index].pTask  = pFunction;     //����ָ���͹��� 
        hSCH_tasks_G[Index].Delay  = DELAY;         //�ӳ�DELAY��ʼ�״�ִ��
        hSCH_tasks_G[Index].Period = PERIOD;        //��������
        hSCH_tasks_G[Index].RunMe  = 0;             //�ȴ���ִ��
        hSCH_tasks_G[Index].Co_op  = task_mode;     //������������ 
        hSCH_tasks_G[Index].Enable = ENABLE;        //����ʹ��
        Index++;
    }
    return &hSCH_tasks_G[Index-1];
}

/*******************************************************************************
 * ����: SCH_Delete_Task
 * ����: ����ɾ��
 * �β�: �ṹ��ָ��sTaskH
 * ����: ��
 * ˵��: ����û�����ɾ����ֻ�ǲ�ִ�����������ѣ�ָ���ָ��
 ******************************************************************************/
void SCH_Delete_Task(sTaskTCB *task) 
{
    task->pTask = NULL;
    task->Delay   = 0;
    task->Period  = 0;
    task->RunMe   = 0;
    task->Enable  = 0;
}

/*******************************************************************************
 * ����: SCH_Enable_Task
 * ����: ʹ������
 * �β�: �ṹ��ָ��sTaskH
 * ����: ��
 * ˵��: ��
 ******************************************************************************/
void SCH_Enable_Task(sTaskTCB *task) 
{
    task->Enable  = 1;
    //task->Delay = task->Period;
}

/*******************************************************************************
 * ����: SCH_Disable_Task
 * ����: ʹ������
 * �β�: �ṹ��ָ��sTaskH
 * ����: ��
 * ˵��: ��
 ******************************************************************************/
void SCH_Disable_Task(sTaskTCB *task) 
{
    task->Enable  = 0;
    task->Delay = 0;
}

/*******************************************************************************
 * ����: SCH_Delay_Task
 * ����: ��������ʱִ��N��ʱ��Ƭ
 * �β�: �ṹ��ָ��sTaskH����ʱ��ʱ��Ƭ����delaytime
 * ����: ��
 * ˵��: ��
 ******************************************************************************/
void SCH_Delay_Task(sTaskTCB *task, uint32_t delaytime) 
{
    task->Delay  += delaytime;
}

/*******************************************************************************
 * ����: SCH_Update
 * ����: �������ʱ�����
 * �β�: ��
 * ����: ��
 * ˵��: ��Ҫ���ڶ�ʱ���жϺ�����
 ******************************************************************************/
void SCH_Update(void) 
{
    u8 Index_temp;

    for (Index_temp = 0; Index_temp < hSCH_MAX_TASKS; Index_temp++)
    {
        if(hSCH_tasks_G[Index_temp].Enable)
        {
            if(hSCH_tasks_G[Index_temp].Delay == 0)
            {
                if(hSCH_tasks_G[Index_temp].Co_op)//����ʽ
                {
                    hSCH_tasks_G[Index_temp].RunMe += 1;  
                }
                else//��ռʽ
                {
                    if( hSCH_tasks_G[Index_temp].pTask != NULL )
                    {
                        hSCH_tasks_G[Index_temp].pTask();    //ִ������
                        //hSCH_tasks_G[Index_temp].RunMe -= 1; //����ִ����ɺ��1
                    }
                }
                
                if(hSCH_tasks_G[Index_temp].Period)
                {
                    hSCH_tasks_G[Index_temp].Delay = (hSCH_tasks_G[Index_temp].Period - 1);
                }
            }
            else
            {
                hSCH_tasks_G[Index_temp].Delay -= 1;
            }
         }         
      }
} 


/************************ (C) COPYRIGHT HARRY007 *****END OF FILE**************/


