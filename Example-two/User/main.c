/**
  ******************************************************************************
  * @file    GPIO/IOToggle/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 


// #define __MAIN_C_


/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/*********ָ������Ľṹ��ָ��***************************/
sTaskTCB *TASK_LED_TWINKLE;    
sTaskTCB *TASK_INPUT_DETECTION; 
sTaskTCB *TASK_KEY_SCAN; 
sTaskTCB *TASK_IWDG;
sTaskTCB *TASK_USART1SEND;
sTaskTCB *TASK_USART_SEND;
sTaskTCB *TASK_USART2RECV_DATAHANDLE;
sTaskTCB *TASK_RS485;

/* Private function prototypes -----------------------------------------------*/
static void BSP_Init(void);
static void NVIC_P_G_Config(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */     
    
    BSP_Init();         //�弶Ӳ����ʼ��
    
    Dll_Init();         //�����ʼ��
    
    hSCH_Init();        //��ʼ��������
    
    
    /******************�������************************************/
    
    TASK_RS485                      = SCH_Add_Task((TASK_SCH *)RS485_Task,        //USART2���ڽ������ݴ���
                                        13,             //�����״�ִ�еȴ�ʱ��13ms                
                                        1000,           //�����������1s 
                                        1,              //����ʽ����
                                        1               //����ʹ��
                                        );
    
    TASK_USART2RECV_DATAHANDLE      = SCH_Add_Task((TASK_SCH *)RFID_DataHandle_Task,        //USART2���ڽ������ݴ���
                                        13,             //�����״�ִ�еȴ�ʱ��13ms                
                                        5,              //�����������1ms 
                                        1,              //����ʽ����
                                        0               //����ʹ��
                                        );
    
                                        
    TASK_USART_SEND                 = SCH_Add_Task((TASK_SCH *)USART_SEND_Task,             //USART2SEND
                                        0,              //�����״�ִ�еȴ�ʱ��0ms                
                                        1,              //�����������1ms 
                                        1,              //����ʽ����
                                        0               //����ʹ��
                                        );


    TASK_USART1SEND                 = SCH_Add_Task((TASK_SCH *)USART1_SEND_Task,             //USART1SEND
                                        0,              //�����״�ִ�еȴ�ʱ��0ms                
                                        1000,           //�����������1s 
                                        1,              //����ʽ����
                                        0               //����ʹ��
                                        );
                                        

    TASK_INPUT_DETECTION            = SCH_Add_Task((TASK_SCH *)GPIO_Input_Task,             //����������
                                        5,              //�����״�ִ�еȴ�ʱ��5ms                
                                        50,             //�����������50ms 
                                        1,              //����ʽ����
                                        0               //����ʹ��
                                        );
                                        
    TASK_INPUT_DETECTION            = SCH_Add_Task((TASK_SCH *)Key_Service_Task,            //������������
                                        19,             //�����״�ִ�еȴ�ʱ��19ms
                                        5,              //�����������5ms 
                                        1,              //����ʽ����
                                        1               //����ʹ��
                                        );
                                        
                                        
    TASK_LED_TWINKLE                = SCH_Add_Task((TASK_SCH *)LED_Twinkle_Task,            //LED������˸���� 
                                        3,              //�����״�ִ�еȴ�ʱ��3ms                
                                        500,            //�����������500ms 
                                        0,              //��ռʽ����
                                        1               //����ʹ��
                                        );
                                        
    TASK_IWDG                       = SCH_Add_Task((TASK_SCH *)IWDG_Task,                   //ι������
                                        9,              //�����״�ִ�еȴ�ʱ��9ms                
                                        1000,           //�����������1000ms 
                                        1,              //����ʽ����
                                        0               //����ʹ��
                                        );
                                        
                                        
    SCH_Start();    //��ʼ�������
   
    while (1)
    {
        hSCH_Dispatch_Tasks();
    }
}







/** @funcname  BSP_Init
  * @brief     �弶Ӳ����ʼ��
  * @param     None
  * @retval    None
  */
static void BSP_Init(void)
{
    NVIC_P_G_Config();              //�������ȼ���
    TIM2_Config();                  //TIM2��ʼ�������ڲ���1ms��ʱ��Ƭ�������������
    LED_Init();                     //LED��ʼ��
    GPIO_Config();                  //��ʼ��������˿�
    USART1_Config();                //��ʼ��USART1
    USART2_Config();                //��ʼ��USART2
    KEY_Config();                   //��ʼ������IO
    //IWDG_Config(IWDG_Prescaler_256, 299);   //��ʼ�����Ź�
}

/** @funcname  NVIC_P_G_Config
  * @brief     None.
  * @param     None.
  * @retval    None.
  */
static void NVIC_P_G_Config(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

/**     @arg NVIC_PriorityGroup_0: 0 bits for pre-emption priority
  *                                4 bits for subpriority
  *     @arg NVIC_PriorityGroup_1: 1 bits for pre-emption priority
  *                                3 bits for subpriority
  *     @arg NVIC_PriorityGroup_2: 2 bits for pre-emption priority
  *                                2 bits for subpriority
  *     @arg NVIC_PriorityGroup_3: 3 bits for pre-emption priority
  *                                1 bits for subpriority
  *     @arg NVIC_PriorityGroup_4: 4 bits for pre-emption priority
  *                                0 bits for subpriority
 
  The table below gives the allowed values of the pre-emption priority and subpriority according
  to the Priority Grouping configuration performed by NVIC_PriorityGroupConfig function
  ============================================================================================================================
    NVIC_PriorityGroup   | NVIC_IRQChannelPreemptionPriority | NVIC_IRQChannelSubPriority  | Description
  ============================================================================================================================
   NVIC_PriorityGroup_0  |                0                  |            0-15             |   0 bits for pre-emption priority
                         |                                   |                             |   4 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------
   NVIC_PriorityGroup_1  |                0-1                |            0-7              |   1 bits for pre-emption priority
                         |                                   |                             |   3 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_2  |                0-3                |            0-3              |   2 bits for pre-emption priority
                         |                                   |                             |   2 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_3  |                0-7                |            0-1              |   3 bits for pre-emption priority
                         |                                   |                             |   1 bits for subpriority
  ----------------------------------------------------------------------------------------------------------------------------    
   NVIC_PriorityGroup_4  |                0-15               |            0                |   4 bits for pre-emption priority
                         |                                   |                             |   0 bits for subpriority         
  ============================================================================================================================  
 
   */
}



#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}

#endif

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
