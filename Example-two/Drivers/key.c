/**
  ******************************************************************************
  * @file    key.c 
  * @author  ZS
  * @version 
  * @date    06-DEC-2016
  * @brief   
  ******************************************************************************
  * @attention
  *
  * 
  *
  ******************************************************************************
  */

#define __KEY_C_

/******************************** Includes ************************************/
#include "key.h"


/***************************** Private typedef ********************************/



/***************************** Private define *********************************/

/****************************** Private macro *********************************/

/**************************** Private variables *******************************/
tKeyScan Key1;
tKeyScan Key2;

/*********************** Private function prototypes **************************/

/**************************** Private functions *******************************/

/** @funcname  KEY_Config
  * @brief     Initialize the KEY input ports.  
  * @param     None
  * @retval    None
  */
void KEY_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /* KEYD Periph clock enable */
    RCC_APB2PeriphClockCmd(KEY_PORT_CLK, ENABLE);

    /* Configure PD0 and PD2 in output pushpull mode */
    GPIO_InitStructure.GPIO_Pin = KEY1 | KEY2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(KEY_PORT, &GPIO_InitStructure);
    
    /* Key struct init */
    Key1.Port = KEY1_PORT;
    Key1.Pin  = KEY1;
    Key1.DownCnt = 0;
    Key1.UpCnt = 0;
    Key1.FunCode = 0; 
    Key1.State = Key_Original;
    
    Key2.Port = KEY2_PORT;
    Key2.Pin  = KEY2;
    Key2.DownCnt = 0;
    Key2.UpCnt = 0;
    Key2.FunCode = 0; 
    Key2.State = Key_Original;
}  

/** @funcname  KEY_Scan
  * @brief     Initialize the KEY input ports.  
  * @param     None
  * @retval    None
  */
void KEY_Scan(tKeyScan *Key)
{   
    uint8_t Key_Value = 0;   
        
    Key_Value = GPIO_ReadInputDataBit(Key->Port, Key->Pin);
                  
    switch (Key->State)
    {
        case Key_Original:      // 按键处于无按键按下状态 
            if (KEY_DOWN == Key_Value)
            {
                Key->DownCnt ++;
                
                if (Key->DownCnt >= CLICK_PERIOD) 
                {
                    Key->State = Key_1;        //第一次按下完成，接着进行后续判断      
                }               
            }
            else
            {
                Key->DownCnt = 0;
                Key->State = Key_Original;
            }
            
            break;
        
        case Key_1:         //检测到按键按下完成，根据后续的判断是长按、单击还是双击  
            if (KEY_DOWN == Key_Value)
            {
                Key->DownCnt++;
                
                if (Key->DownCnt >= LONGCLICK_PERIOD) 
                {
                    Key->DownCnt = 0;
                    Key->FunCode = LCLICK;        // 返回长按 
                    Key->State = Key_5;           //长按完成，等待松开   
                }               
            }
            else
            {
                Key->DownCnt = 0;
                Key->State = Key_2;
            }
            
            
            break;
        
        case Key_2:         //单击松开后，根据后续判断是单击还是双击
            if (KEY_DOWN != Key_Value)
            {
                Key->UpCnt ++;
                
                if (Key->UpCnt >= LOOSEN_PERIOD) 
                {
                    Key->UpCnt = 0;
                    
                    Key->State = Key_Original;
                    Key->FunCode = CLICK;                //  产生一次单击  返回单击
                }               
            }
            else
            {
                Key->DownCnt = 0;
                Key->State = Key_3;     
            }
            
        
   
            break;
        
        case Key_3:         //双击的第二次按下
            if (KEY_DOWN == Key_Value)
            {
                Key->DownCnt ++;
                
                if (Key->DownCnt >= CLICK_PERIOD) 
                {
                    Key->DownCnt = 0;
                    Key->State = Key_4;    //第二次双击按下完成
                }               
            }
            else
            {
                Key->DownCnt = 0;
                Key->UpCnt ++;
                         
                if (Key->UpCnt >= LOOSEN_PERIOD) 
                {
                    Key->UpCnt = 0;
                    Key->State = Key_Original;
                    Key->FunCode = CLICK;                //  产生一次单击  返回单击
                }  
            }
               
            break;
        
        case Key_4:         //等待双击松开
            if (KEY_DOWN != Key_Value)
            {
                Key->State = Key_Original;
                Key->FunCode = DBCLICK;   // 返回双击         
            }
                  
            break;
        
        case Key_5:         //等待长按松开
            if (KEY_DOWN != Key_Value)
            {
                Key->State = Key_Original;                     
            }
                  
            break;
        
        default:          
            break;          
    }
} 
  

void KEY_Analysisi(tKeyScan *Key)
{
    switch (Key->FunCode)
    {
        case 0x01:      // 单击
            Key->FunCode = 0x00;
        
            //处理单击事件
            SetLedTurn(LED1_PORT,LED1);
        
        
            break;
        
        case 0x02:      // 双击
            Key->FunCode = 0x00;
        
            //处理双击事件
            SetLedTurn(LED2_PORT,LED2);
        
            break;
        
        case 0x03:      // 长按
            Key->FunCode = 0x00;
        
            //处理长按事件
            SetLedTurn(LED3_PORT,LED3);
               
            break;
        
        default:          
            break;
    }   
}

/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
