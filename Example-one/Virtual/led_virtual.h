/************************ (C) COPYRIGHT HARRY007 *******************************
 * 文件名  ：led_virtual.h
 * 描述    ：LED应用层函数
 * 库版本  ：V2.1.0
 * 作者    ：HARRY007
 * 修改时间 ：2016-09-13
*******************************************************************************/

#ifndef __LED_VIRTUAL_H
#define __LED_VIRTUAL_H

typedef struct aa
{
    u16 down;  //LED点亮次数
    u16 count;  //计数次数
    u16 space_time;  //间隔时间
    u16 time;  //点亮时间
}Led_Struct;

extern Led_Struct led;
/*******************************************************************************
 * 名称: Led_Drive
 * 功能: LED驱动函数
 * 形参: count ->点亮次数；beep ->亮时间ms   time ->灭时间ms
 * 返回: 无
 * 说明: 无
 ******************************************************************************/
void Led_Drive( u8 num,u16 a, u16 b  );

/*******************************************************************************
 * 名称: Led_Load
 * 功能: LED负载更新函数
 * 形参: 无
 * 返回: 无
 * 说明: 无
 ******************************************************************************/
void Led_Load(void);

/*******************************************************************************
 * 名称: Led_Update
 * 功能: LED更新函数
 * 形参: 无
 * 返回: 无
 * 说明: 放在定时中毒中
 ******************************************************************************/
void Led_Update(void);

#endif

/************************ (C) COPYRIGHT HARRY007 *****END OF FILE**************/
