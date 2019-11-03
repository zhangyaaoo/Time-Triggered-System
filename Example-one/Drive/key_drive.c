/************************ (C) COPYRIGHT HARRY007 *******************************
 * 文件名  ：key.c
 * 描述    ：按键驱动底层函数 
 * 库版本  ：V2.1.0
 * 作者    ：wujianhong  修改：HARRY007
 * 修改时间 ：2016-09-13
*******************************************************************************/


/*************头文件包含***************/
#include "head.h"

/*************变量定义****************/
u8 key_funcode = 0;//按键功能码
u8 key_lock    = 0;//按键自锁标志位
u8 delay_cout  = 0;//消抖计时变量


/*******************************************************************************
 * 名称: Key_Init
 * 功能: KEY外设GPIO引脚初始化操作
 * 形参: 无
 * 返回: 无
 * 说明: 无 
 ******************************************************************************/
void Key_Init(void)
{
    GPIO_Init(KEY_PORT, KEY_PIN_1, GPIO_MODE_IN_PU_NO_IT);//上拉输入无中断
    GPIO_Init(KEY_PORT, KEY_PIN_2, GPIO_MODE_IN_PU_NO_IT);//上拉输入无中断
}

/*******************************************************************************
 * 名称:Key_Scan 
 * 功能: 按键检测扫描函数
 * 形参: 无
 * 返回: 无
 * 说明: 无 
 ******************************************************************************/
void Key_Scan(void)
{//2ms
  if( ( 0 != GPIO_ReadInputPin(KEY_PORT, KEY_PIN_1 ) )&& \
      ( 0 != GPIO_ReadInputPin(KEY_PORT, KEY_PIN_2 ) ) )  //sw0和sw1都没有按下
    {
        key_lock = 0;//清除按键锁
        delay_cout = 0;//延时清空
        return;
    }
    
    if( (0 == GPIO_ReadInputPin(KEY_PORT, KEY_PIN_1)) && (0 == key_lock) )
    {
        delay_cout++;
        if( delay_cout >= DELAY_CNT )//消抖30MS
        {
            key_funcode = SW0;
            key_lock = 1;
        }
    }
    if( (0 == GPIO_ReadInputPin(KEY_PORT, KEY_PIN_2)) && (0 == key_lock) )
    {
        delay_cout++;
        if( delay_cout >= DELAY_CNT )//消抖30MS
        {
            key_funcode = SW1;
            key_lock = 1;
        }
    }     
}
         
/*******************************************************************************
 * 名称:Key_Pro
 * 功能: 按键处理函数
 * 形参: 无
 * 返回: 无
 * 说明: 无 
 ******************************************************************************/
void Key_Pro(void)
{
    if( key_funcode == SW0 )//按键1
    {
        key_funcode = NONE;
        if( work_state == STATE_INIT )//待机模式下
        {
            SCH_Enable_Task(TASK_ONE);//使能继电器执行任务
            SetLedON(1);              //工作灯点亮
            Relay_Drive(1,1);         //开启继电器
            work_state = STATE_RUN;   //系统工作状态切换到运行状态
            return;
        }
        
        if( work_state == STATE_RUN )//运行状态下
        {
            Relay_Drive(1,0);        //关闭继电器
            SetLedOFF(1);            //关闭工作灯
            SCH_Disable_Task(TASK_ONE);//关闭继电器执行任务
            work_state = STATE_INIT;
            power_flag = OFF;
            return;
        }
        
        if( work_state == STATE_TIME )//修改时间模式下
        {
            TASK_ONE->Period = TASK_ONE->Period + MIN_10;//每次加10min
            if( TASK_ONE->Period > (MIN_10*6) )//如果大于1小时
            {
                TASK_ONE->Period = MIN_10;//回到10Min最小定时值
            }
            
            Led_Drive( (TASK_ONE->Period/MIN_10),20,30 );//闪灯次数表示定时时间
            
            FLASH_Unlock(FLASH_MEMTYPE_DATA);//解锁EEPROM
            FLASH_ProgramByte(0x4000, TASK_ONE->Period/MIN_10);//将修改的时间存入EEPROM
            FLASH_Lock(FLASH_MEMTYPE_DATA); //上锁EEPROM
            
            TASK_FIVE->Delay = TASK_FIVE->Period;//每按下一次按键，状态倒计时自动重装
            return;
        }   
    }
    
    if( key_funcode == SW1 )//按键2
    {
        key_funcode = NONE;
        if( work_state == STATE_INIT )//待机模式下
        {
            work_state = STATE_TIME;  //进入修改时间模式
            SCH_Enable_Task(TASK_FIVE);//使能状态倒计时任务
            SetLedON(2);              //修改灯点亮
            return;
        }
        if( work_state == STATE_TIME )//修改时间模式下
        {
            work_state = STATE_INIT;  //进入待机模式
            SCH_Disable_Task(TASK_FIVE);//关闭状态倒计时
            SetLedOFF(2);             //灭掉修改灯
            power_flag = OFF;
        } 
    }
}

/************************ (C) COPYRIGHT HARRY007 *****END OF FILE**************/