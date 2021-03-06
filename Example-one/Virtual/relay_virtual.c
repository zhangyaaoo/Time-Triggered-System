/************************ (C) COPYRIGHT HARRY007 *******************************
 * 文件名  ：relay_virtual.c
 * 描述    ：继电器应用层
 * 库版本  ：V2.1.0
 * 作者    ：周鹏飞
 * 修改时间 ：2016-09-12    
*******************************************************************************/

/*************头文件包含***************/
#include "head.h"

/**************变量声明***************/
u32  basetime_1min = 0; //1min基准
u8   FanTime       = 0; //风扇开启时间


/*******************************************************************************
 * 名称: Relay_Load
 * 功能: 继电器负载执行函数
 * 形参: 无
 * 返回: 无
 * 说明: channel范围CHANNEL_1  【开：1】【关：0】
 ******************************************************************************/
void Relay_Load(void)
{
    Relay_Drive(1,0);//通道1关闭
    SetLedOFF(1);
    SCH_Disable_Task(TASK_ONE);
    work_state = STATE_INIT;
    //halt();
}


/************************ (C) COPYRIGHT HARRY007 *****END OF FILE**************/