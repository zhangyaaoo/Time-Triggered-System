/************************ (C) COPYRIGHT HARRY007 *******************************
 * 文件名  ：sysclock.c
 * 描述    ：系统时钟设置   
 * 库版本  ：V2.1.0
 * 作者    ：HARRY007
 *修改时间 ：2016-09-09
*******************************************************************************/

#include "head.h"

/*******************************************************************************
 * 名称: Sysclock_Init
 * 功能: 设置系统时钟频率
 * 形参: 无
 * 返回: 无
 * 说明: 
 ******************************************************************************/
void SystemClock_Init(void)
{
    CLK_HSICmd(ENABLE);//启用内部高速时钟
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);//配置HSI时钟分频系数为1，16MHZ供给CPU  
}

/*******************************************************************************
 * 名称: system_init
 * 功能: 系统上电初始化
 * 形参: 无
 * 返回: 无
 * 说明: 无 
 ******************************************************************************/
void system_init(void)
{
    SystemClock_Init();//系统时钟初始化
    Time4_Init();//定时器4初始化
    Led_Init();//外设LED初始化
    Key_Init();
    GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_IN_PU_IT);
    GPIO_Init(GPIOC, GPIO_PIN_6, GPIO_MODE_IN_PU_IT);
    EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC,EXTI_SENSITIVITY_FALL_ONLY);
    Relay_Init();
    //IWDG_Config();//看门狗初始化
}

/*******************************************************************************
 * 名称: IWDG_Config
 * 功能: 看门狗配置函数
 * 形参: 无
 * 返回: 无
 * 说明: 0.5S 
 ******************************************************************************/
void IWDG_Config(void)
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//写使能
    IWDG_SetPrescaler(IWDG_Prescaler_256);//预分频256,128KHZ/256 
    IWDG_SetReload(0XFA);//设置每次喂狗的计数值。256*250/128000=0.5s
    IWDG_ReloadCounter();//喂狗
    IWDG_Enable();//使能看门狗
}

/*******************************************************************************
 * 名称: State_Dog
 * 功能: 按键状态下系统设置倒计时
 * 形参: 无
 * 返回: 无
 * 说明: 进入修改时间模式，在5S内无按键按下就自动跳转到STATE_INIT模式下
 ******************************************************************************/
void State_Dog(void)
{
    work_state = STATE_INIT;                     //进入待机模式
    SCH_Disable_Task(TASK_FIVE);                 //关闭该任务
    SetLedOFF(2);                                //关闭修改状态的指示灯
    //Led_Drive( (TASK_ONE->Period/300000),20,30 );//指示一下当前的定时时间值
    power_flag = OFF;
}



/************************ (C) COPYRIGHT HARRY007 *****END OF FILE**************/