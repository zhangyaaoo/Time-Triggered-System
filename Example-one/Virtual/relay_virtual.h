/************************ (C) COPYRIGHT HARRY007 *******************************
 * 文件名  ：relay_virtual.h
 * 描述    ：继电器应用层函数
 * 库版本  ：V2.1.0
 * 作者    ：HARRY007
 * 修改时间 ：2016-09-12
*******************************************************************************/

#ifndef __RELAY_VIRTUAL_H
#define __RELAY_VIRTUAL_H

/*************变量外部使用声明*************/
extern u32  basetime_1min;
extern u8   FanTime;


/*******************************************************************************
 * 名称: Relay_Load
 * 功能: 继电器负载执行函数
 * 形参: 无
 * 返回: 无
 * 说明: channel范围CHANNEL_1  【开：1】【关：0】
 ******************************************************************************/
void Relay_Load(void);


#endif

/************************ (C) COPYRIGHT HARRY007 *****END OF FILE**************/


