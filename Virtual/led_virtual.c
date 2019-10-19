/************************ (C) COPYRIGHT HARRY007 *******************************
 * 文件名  ：led_virtual.c
 * 描述    ：LED应用层
 * 库版本  ：V2.1.0
 * 作者    ：周鹏飞
 * 修改时间 ：2016-09-13  
*******************************************************************************/

/*************头文件包含***************/
#include "head.h"

Led_Struct led;

/*******************************************************************************
 * 名称: Led_Drive
 * 功能: LED驱动函数
 * 形参: count ->点亮次数；beep ->亮时间ms   time ->灭时间ms
 * 返回: 无
 * 说明: 无
 ******************************************************************************/
void Led_Drive( u8 num,u16 a, u16 b )
{
    led.count = num;
    led.time = a;
    led.space_time = b+led.time;
    led.down = led.space_time; 
}
    

/*******************************************************************************
 * 名称: Led_Load
 * 功能: LED负载更新函数
 * 形参: 无
 * 返回: 无
 * 说明: 无
 ******************************************************************************/
void Led_Load(void)
{   
    if( led.count > 0 )
    {
        if( led.down >( led.space_time - led.time ) )
            SetLedON(3);   
        else
        {
            SetLedOFF(3);
            if( (led.down == 0)&&(led.count >= 2) )
            {
               led.count--;
               led.down = led.space_time;
            }
        }
    }
}

/*******************************************************************************
 * 名称: Led_Update
 * 功能: LED更新函数
 * 形参: 无
 * 返回: 无
 * 说明: 放在定时中毒中
 ******************************************************************************/
void Led_Update(void)
{
    if( led.down )//led时间倒计时
	led.down --;
}



/************************ (C) COPYRIGHT HARRY007 *****END OF FILE**************/