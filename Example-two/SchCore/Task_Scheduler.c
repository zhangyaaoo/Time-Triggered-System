/************************ (C) COPYRIGHT ZS *************************************
 * 文件名   ：Task_Scheduler.c
 * 描述     ：混合式调度器C文件
 * 库版本   ：V1.2.0
 * 原作者   ：HARRY007  参考：Michael J. Pont , liubing等人
 * 作者     : ZS
 * 修改时间 ：2016-10-13
*******************************************************************************/


/* 包含自定义头文件 */
#include "Task_Scheduler.h"

sTaskTCB hSCH_tasks_G[hSCH_MAX_TASKS];

/*******************************************************************************
 * 名称: hSCH_Init
 * 功能: 任务初始化
 * 形参: 无
 * 返回: 无
 * 说明: 无 
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
 * 名称: SCH_Start
 * 功能: 开始任务调度
 * 形参: 无
 * 返回: 无
 * 说明: 无 
 ******************************************************************************/
void SCH_Start(void)
{
    //打开用于任务调度的定时器的终端即开始了任务调度
    
    /* TIM2 enable counter */
    TIM_Cmd(TIM2, ENABLE);
}

/*******************************************************************************
 * 名称: hSCH_Dispatch_Tasks
 * 功能: 任务调度
 * 形参: 无
 * 返回: 无
 * 说明: 需要放在主函数超级大循环中
 ******************************************************************************/
void hSCH_Dispatch_Tasks(void)
{
   u8 Index;

    for (Index = 0; Index < hSCH_MAX_TASKS; Index++)//遍历所有任务
    {
        if ((hSCH_tasks_G[Index].Co_op) && (hSCH_tasks_G[Index].RunMe > 0))  //某任务是否就绪
        {
            if(hSCH_tasks_G[Index].pTask != NULL)//需要执行任务是否真正存在
            {
                hSCH_tasks_G[Index].pTask();//执行任务
            }
            hSCH_tasks_G[Index].RunMe -= 1; //任务执行完成后减1
        }

        if (hSCH_tasks_G[Index].Period == 0)//如果调度周期为0，则删除任务
        {
            hSCH_tasks_G[Index].pTask = NULL;//将任务删除
        }
    }
}  

/*******************************************************************************
 * 名称: SCH_Add_Task
 * 功能: 添加任务
 * 形参: 任务函数指针，首次开始执行时间，调度周期，任务类型，任务使能
 * 返回: 结构体指针sTaskH
 * 说明: 调度周期如果为0，则该任务视为单次执行的任务，执行一次后将被删除
 ******************************************************************************/
sTaskTCB *SCH_Add_Task(TASK_SCH *pFunction, u32 DELAY, u32 PERIOD,u8 task_mode,u8 ENABLE)  
{
    static u8 Index = 0;
    if (Index < hSCH_MAX_TASKS)
    {    
        hSCH_tasks_G[Index].pTask  = pFunction;     //函数指针送过来 
        hSCH_tasks_G[Index].Delay  = DELAY;         //延迟DELAY后开始首次执行
        hSCH_tasks_G[Index].Period = PERIOD;        //调度周期
        hSCH_tasks_G[Index].RunMe  = 0;             //等待不执行
        hSCH_tasks_G[Index].Co_op  = task_mode;     //配置任务类型 
        hSCH_tasks_G[Index].Enable = ENABLE;        //任务使能
        Index++;
    }
    return &hSCH_tasks_G[Index-1];
}

/*******************************************************************************
 * 名称: SCH_Delete_Task
 * 功能: 任务删除
 * 形参: 结构体指针sTaskH
 * 返回: 无
 * 说明: 代码没有真的删除，只是不执行这个任务而已，指向空指针
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
 * 名称: SCH_Enable_Task
 * 功能: 使能任务
 * 形参: 结构体指针sTaskH
 * 返回: 无
 * 说明: 无
 ******************************************************************************/
void SCH_Enable_Task(sTaskTCB *task) 
{
    task->Enable  = 1;
    //task->Delay = task->Period;
}

/*******************************************************************************
 * 名称: SCH_Disable_Task
 * 功能: 使能任务
 * 形参: 结构体指针sTaskH
 * 返回: 无
 * 说明: 无
 ******************************************************************************/
void SCH_Disable_Task(sTaskTCB *task) 
{
    task->Enable  = 0;
    task->Delay = 0;
}

/*******************************************************************************
 * 名称: SCH_Delay_Task
 * 功能: 将任务延时执行N个时间片
 * 形参: 结构体指针sTaskH，延时的时间片个数delaytime
 * 返回: 无
 * 说明: 无
 ******************************************************************************/
void SCH_Delay_Task(sTaskTCB *task, uint32_t delaytime) 
{
    task->Delay  += delaytime;
}

/*******************************************************************************
 * 名称: SCH_Update
 * 功能: 任务调度时间更新
 * 形参: 无
 * 返回: 无
 * 说明: 需要放在定时器中断函数中
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
                if(hSCH_tasks_G[Index_temp].Co_op)//合作式
                {
                    hSCH_tasks_G[Index_temp].RunMe += 1;  
                }
                else//抢占式
                {
                    if( hSCH_tasks_G[Index_temp].pTask != NULL )
                    {
                        hSCH_tasks_G[Index_temp].pTask();    //执行任务
                        //hSCH_tasks_G[Index_temp].RunMe -= 1; //任务执行完成后减1
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


