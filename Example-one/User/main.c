/************************ (C) COPYRIGHT HARRY007 *******************************
 * �ļ���  ��main.c
 * ����    ��������   
 * ��汾  ��V2.1.0
 * ����    ��HARRY007
 * �޸�ʱ�� ��2016-09-13
 * ˵�� ��1����������ڻ��ʽ���������ر�ע�⣬ÿ���һ��������Ҫ��Task_Scheduler.h
          ���޸��������������
          2��������ʵ�ַ��ȵĶ�ʱ���ƣ�ͨ���������ö�ʱʱ��Ϳ���ʹ�ܡ�
          3����ʱʱ��Ϊ10min/20min/30min/40min/50min/60min
          4������ģʽ��S2�����ն�ʱʱ�俪�����ȣ��ٰ�һ�¿�����ǰ�ֶ��رա�
          5������ģʽ��S1�������޸�ʱ��ģʽ���ٰ�һ���˳��޸�ʱ��ģʽ��
          6���޸�ʱ��ģʽ�£���S2���Լ�10min��ʱʱ�䣬ͨ�����ƴ�����ʾ��
          7���޸�ʱ��ģʽ�£�5S���ް��������Զ����ش���ģʽ��������֮ǰ���޸�ʱ��ֵ��
          8������״̬�£�S1����Ч��
          9���ڴ���״̬��MCU���Զ��л���ͣ��ģʽ��S1����S2�����ܿ��Ի���ϵͳ��ͬʱִ��
          �������ܡ�
*******************************************************************************/

#include "head.h"

/****ָ������Ľṹ��ָ��****/
sTaskH *TASK_ONE;    //�̵���ִ������
sTaskH *TASK_TWO;    //������������
sTaskH *TASK_THREE;  //����ɨ������
sTaskH *TASK_FOUR;   //LED����ʱ������
sTaskH *TASK_FIVE;   //��������ʱ

/*********ȫ�ֱ���*********/
u8 work_state = STATE_INIT;//ϵͳĬ�Ϲ���ģʽ������״̬
u8 power_flag = OFF;

/*******************************************************************************
 * ����: main
 * ����: ������
 * �β�: ��
 * ����: ��
 * ˵��: �� 
 ******************************************************************************/

void main(void)
{
    system_init();//�ϵ��ʼ��
    
    hSCH_Init();//���ʽ��������ʼ�� ʱ��̶�2ms
    
    /******************�������************************************/
    
    TASK_ONE   = SCH_Add_Task((TASK_SCH *)Relay_Load, //�̵���ִ������
                              MIN_10, //�״�ִ�еȴ�10min
                              MIN_10, //��������10min
                              1,     //����ʽ
                              0      //��ʹ������
                              );
                              
    TASK_TWO   = SCH_Add_Task((TASK_SCH *)Key_Pro,   //������������
                              5,     //�״�ִ������ȴ�10ms
                              25,    //��������50ms
                              1,     //����ʽ
                              1      //ʹ������
                              );
                              
    TASK_THREE = SCH_Add_Task((TASK_SCH *)Key_Scan,  //����ɨ������
                              0,     //�״�ִ�в��ȴ�
                              1,     //��������2ms
                              0,     //��ռʽ
                              1      //ʹ������
                              );
    
    TASK_FOUR = SCH_Add_Task((TASK_SCH *)Led_Update,  //LED����ʱ������
                              3,     //�״�ִ�еȴ�6ms
                              5,     //��������10ms
                              0,     //��ռʽ
                              1      //ʹ������
                              );
    
    TASK_FIVE = SCH_Add_Task((TASK_SCH *)State_Dog,  //��������ʱ
                              2500,  //�״�ִ�еȴ�5S
                              2500,  //��������5S
                              1,     //����ʽ
                              0      //��ʹ������
                              );
    
    E2PROM_Init();//�������TASK_ONE����֮��
    
    enableInterrupts();//���ж�����
    
    while (1)
    {       
        hSCH_Dispatch_Tasks();//�������
        
        Led_Load();//LED����ˢ������ʵʱִ��
        
        if( power_flag == OFF )
        {
            disableInterrupts();
            GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_IN_PU_IT);
            GPIO_Init(GPIOC, GPIO_PIN_6, GPIO_MODE_IN_PU_IT);
            EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC,EXTI_SENSITIVITY_RISE_FALL);
            enableInterrupts();
            halt();
        }
            
        //IWDG_ReloadCounter();//ι��  
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
