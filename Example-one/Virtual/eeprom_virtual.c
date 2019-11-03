/************************ (C) COPYRIGHT HARRY007 *******************************
 * 文件名  ：eeprom_virtual.c
 * 描述    ：eeprom应用层
 * 库版本  ：V2.1.0
 * 作者    ：周鹏飞
 * 修改时间 ：2016-09-13  
*******************************************************************************/

/*************头文件包含***************/
#include "head.h"

/*******************************************************************************
 * 名称: E2PROM_Init
 * 功能: EEPROM初始化
 * 形参: 无
 * 返回: 无
 * 说明: 无 
 ******************************************************************************/
void E2PROM_Init(void)
{
    /* 设置固定的编程时间 */
    FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);

    FLASH_Unlock(FLASH_MEMTYPE_DATA);//解锁EEPROM
    
    if( FLASH_ReadByte(0X407F) != 0XAA )//如果是新板子，定时时间默认10Min
    {
        /*是新板子*/
        FLASH_ProgramByte(0X407F,0XAA);//刷过之后就是旧板子了……

        FLASH_ProgramByte(0x4000, 1);//默认存10Min
    }
    else
    {
        /*旧板子*/
        TASK_ONE->Period = FLASH_ReadByte(0x4000)*MIN_10;
        TASK_ONE->Delay = TASK_ONE->Period;
    }
    FLASH_Lock(FLASH_MEMTYPE_DATA); //上锁EEPROM
}




/************************ (C) COPYRIGHT HARRY007 *****END OF FILE**************/