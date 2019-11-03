/************************ (C) COPYRIGHT HARRY007 *******************************
 * 文件名  ：led_drive.c
 * 描述    ：LED驱动底层函数 
 * 库版本  ：V2.1.0
 * 作者    ：HARRY007
 * 修改时间 ：2016-09-12
*******************************************************************************/


/*************头文件包含***************/
#include "head.h"


void Delay(u32 t)
{
    while (t!= 0)
    {
	t--;
    }
}
/*******************************************************************************
 * 名称: LED_Init
 * 功能: LED外设GPIO引脚初始化操作
 * 形参: 无
 * 返回: 无
 * 说明: 无 
 ******************************************************************************/
void Led_Init(void)
{
    GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_FAST);
    
}

/*******************************************************************************
 * 名称: SetLedOFF
 * 功能: 关闭某通道的LED
 * 形参: 无
 * 返回: 无
 * 说明: 无 
 ******************************************************************************/
void SetLedOFF(u8 channel)
{
    if( 1 == channel )
        GPIO_WriteHigh(GPIOD, GPIO_PIN_3);
    if( 2 == channel )
        GPIO_WriteHigh(GPIOD, GPIO_PIN_2);
    if( 3 == channel )
        GPIO_WriteHigh(GPIOC, GPIO_PIN_7);
}

/*******************************************************************************
 * 名称: SetLedON
 * 功能: 打开某通道的LED
 * 形参: 无
 * 返回: 无
 * 说明: 无 
 ******************************************************************************/
void SetLedON(u8 channel)
{
    if( 1 == channel )
        GPIO_WriteLow(GPIOD, GPIO_PIN_3);
    if( 2 == channel )
        GPIO_WriteLow(GPIOD, GPIO_PIN_2);
    if( 3 == channel )
        GPIO_WriteLow(GPIOC, GPIO_PIN_7);	
}



/*******************************************************************************
 * 名称: Led_SystemRun
 * 功能: 系统运行指示灯
 * 形参: 无
 * 返回: 无
 * 说明: 无 
 ******************************************************************************/
void Led_SystemRun(void)
{
    GPIO_WriteReverse(GPIOC, GPIO_PIN_7);//系统运行状态指示灯   
}


/************************ (C) COPYRIGHT HARRY007 *****END OF FILE**************/