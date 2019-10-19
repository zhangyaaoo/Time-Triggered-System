/************************ (C) COPYRIGHT HARRY007 *******************************
 * 文件名  ：main.c
 * 描述    ：主函数   
 * 库版本  ：V2.1.0
 * 作者    ：HARRY007
 * 修改时间 ：2016-09-13
 * 说明 ：1、本程序基于混合式调度器，特别注意，每添加一个任务都需要在Task_Scheduler.h
          中修改最大任务数量。
          2、本程序实现风扇的定时控制，通过按键配置定时时间和开启使能。
          3、定时时间为10min/20min/30min/40min/50min/60min
          4、待机模式下S2键按照定时时间开启风扇，再按一下可以提前手动关闭。
          5、待机模式下S1键进入修改时间模式，再按一下退出修改时间模式。
          6、修改时间模式下，按S2可以加10min定时时间，通过闪灯次数表示。
          7、修改时间模式下，5S内无按键按下自动返回待机模式，并保存之前的修改时间值。
          8、运行状态下，S1键无效。
          9、在待机状态下MCU会自动切换到停机模式，S1键和S2键功能可以唤醒系统并同时执行
          上述功能。
*******************************************************************************/

#include "head.h"

/****指向任务的结构体指针****/
sTaskH *TASK_ONE;    //继电器执行任务
sTaskH *TASK_TWO;    //按键服务任务
sTaskH *TASK_THREE;  //按键扫描任务
sTaskH *TASK_FOUR;   //LED更新时间任务
sTaskH *TASK_FIVE;   //按键倒计时

/*********全局变量*********/
u8 work_state = STATE_INIT;//系统默认工作模式：待机状态
u8 power_flag = OFF;

/*******************************************************************************
 * 名称: main
 * 功能: 主函数
 * 形参: 无
 * 返回: 无
 * 说明: 无 
 ******************************************************************************/

void main(void)
{
    system_init();//上电初始化
    
    hSCH_Init();//混合式调度器初始化 时间刻度2ms
    
    /******************添加任务************************************/
    
    TASK_ONE   = SCH_Add_Task((TASK_SCH *)Relay_Load, //继电器执行任务
                              MIN_10, //首次执行等待10min
                              MIN_10, //调度周期10min
                              1,     //合作式
                              0      //不使能任务
                              );
                              
    TASK_TWO   = SCH_Add_Task((TASK_SCH *)Key_Pro,   //按键服务任务
                              5,     //首次执行任务等待10ms
                              25,    //调度周期50ms
                              1,     //合作式
                              1      //使能任务
                              );
                              
    TASK_THREE = SCH_Add_Task((TASK_SCH *)Key_Scan,  //按键扫描任务
                              0,     //首次执行不等待
                              1,     //调度周期2ms
                              0,     //抢占式
                              1      //使能任务
                              );
    
    TASK_FOUR = SCH_Add_Task((TASK_SCH *)Led_Update,  //LED更新时间任务
                              3,     //首次执行等待6ms
                              5,     //调度周期10ms
                              0,     //抢占式
                              1      //使能任务
                              );
    
    TASK_FIVE = SCH_Add_Task((TASK_SCH *)State_Dog,  //按键倒计时
                              2500,  //首次执行等待5S
                              2500,  //调度周期5S
                              1,     //合作式
                              0      //不使能任务
                              );
    
    E2PROM_Init();//必须放在TASK_ONE创建之后
    
    enableInterrupts();//总中断允许
    
    while (1)
    {       
        hSCH_Dispatch_Tasks();//任务调度
        
        Led_Load();//LED负载刷新任务，实时执行
        
        if( power_flag == OFF )
        {
            disableInterrupts();
            GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_IN_PU_IT);
            GPIO_Init(GPIOC, GPIO_PIN_6, GPIO_MODE_IN_PU_IT);
            EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC,EXTI_SENSITIVITY_RISE_FALL);
            enableInterrupts();
            halt();
        }
            
        //IWDG_ReloadCounter();//喂狗  
    } 
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/************************ (C) COPYRIGHT HARRY007 *****END OF FILE**************/
