/************************ (C) COPYRIGHT HARRY007 *******************************
 * 文件名  ：time4_drive.c
 * 描述    ：TIME4定时器底层驱动
 * 库版本  ：V2.1.0
 * 作者    ：HARRY007
 * 修改时间 ：2016-09-011
*******************************************************************************/


/* 包含自定义头文件 */
#include "time4_drive.h"

/*******************************************************************************
 * 名称: Time4_Init
 * 功能: 定时器4初始化
 * 形参: 无
 * 返回: 无
 * 说明: 定时器4用来一个1ms的时间基准
 ******************************************************************************/
void Time4_Init(void)
{
    TIM4_TimeBaseInit(TIM4_PRESCALER_128, 249);//理论定时中断时间8us*250=2MS
    TIM4_PrescalerConfig(TIM4_PRESCALER_128, TIM4_PSCRELOADMODE_IMMEDIATE);
    TIM4_ARRPreloadConfig(ENABLE);
    TIM4_ClearFlag(TIM4_FLAG_UPDATE);
    TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
    TIM4_Cmd(ENABLE);
}

/*******注：定时器4的中断函数在库版本文件stm8s_it.c文件中********************/

/************************ (C) COPYRIGHT HARRY007 *****END OF FILE**************/