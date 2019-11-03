/************************ (C) COPYRIGHT HARRY007 *******************************
 * �ļ���  ��key.c
 * ����    �����������ײ㺯�� 
 * ��汾  ��V2.1.0
 * ����    ��wujianhong  �޸ģ�HARRY007
 * �޸�ʱ�� ��2016-09-13
*******************************************************************************/


/*************ͷ�ļ�����***************/
#include "head.h"

/*************��������****************/
u8 key_funcode = 0;//����������
u8 key_lock    = 0;//����������־λ
u8 delay_cout  = 0;//������ʱ����


/*******************************************************************************
 * ����: Key_Init
 * ����: KEY����GPIO���ų�ʼ������
 * �β�: ��
 * ����: ��
 * ˵��: �� 
 ******************************************************************************/
void Key_Init(void)
{
    GPIO_Init(KEY_PORT, KEY_PIN_1, GPIO_MODE_IN_PU_NO_IT);//�����������ж�
    GPIO_Init(KEY_PORT, KEY_PIN_2, GPIO_MODE_IN_PU_NO_IT);//�����������ж�
}

/*******************************************************************************
 * ����:Key_Scan 
 * ����: �������ɨ�躯��
 * �β�: ��
 * ����: ��
 * ˵��: �� 
 ******************************************************************************/
void Key_Scan(void)
{//2ms
  if( ( 0 != GPIO_ReadInputPin(KEY_PORT, KEY_PIN_1 ) )&& \
      ( 0 != GPIO_ReadInputPin(KEY_PORT, KEY_PIN_2 ) ) )  //sw0��sw1��û�а���
    {
        key_lock = 0;//���������
        delay_cout = 0;//��ʱ���
        return;
    }
    
    if( (0 == GPIO_ReadInputPin(KEY_PORT, KEY_PIN_1)) && (0 == key_lock) )
    {
        delay_cout++;
        if( delay_cout >= DELAY_CNT )//����30MS
        {
            key_funcode = SW0;
            key_lock = 1;
        }
    }
    if( (0 == GPIO_ReadInputPin(KEY_PORT, KEY_PIN_2)) && (0 == key_lock) )
    {
        delay_cout++;
        if( delay_cout >= DELAY_CNT )//����30MS
        {
            key_funcode = SW1;
            key_lock = 1;
        }
    }     
}
         
/*******************************************************************************
 * ����:Key_Pro
 * ����: ����������
 * �β�: ��
 * ����: ��
 * ˵��: �� 
 ******************************************************************************/
void Key_Pro(void)
{
    if( key_funcode == SW0 )//����1
    {
        key_funcode = NONE;
        if( work_state == STATE_INIT )//����ģʽ��
        {
            SCH_Enable_Task(TASK_ONE);//ʹ�̵ܼ���ִ������
            SetLedON(1);              //�����Ƶ���
            Relay_Drive(1,1);         //�����̵���
            work_state = STATE_RUN;   //ϵͳ����״̬�л�������״̬
            return;
        }
        
        if( work_state == STATE_RUN )//����״̬��
        {
            Relay_Drive(1,0);        //�رռ̵���
            SetLedOFF(1);            //�رչ�����
            SCH_Disable_Task(TASK_ONE);//�رռ̵���ִ������
            work_state = STATE_INIT;
            power_flag = OFF;
            return;
        }
        
        if( work_state == STATE_TIME )//�޸�ʱ��ģʽ��
        {
            TASK_ONE->Period = TASK_ONE->Period + MIN_10;//ÿ�μ�10min
            if( TASK_ONE->Period > (MIN_10*6) )//�������1Сʱ
            {
                TASK_ONE->Period = MIN_10;//�ص�10Min��С��ʱֵ
            }
            
            Led_Drive( (TASK_ONE->Period/MIN_10),20,30 );//���ƴ�����ʾ��ʱʱ��
            
            FLASH_Unlock(FLASH_MEMTYPE_DATA);//����EEPROM
            FLASH_ProgramByte(0x4000, TASK_ONE->Period/MIN_10);//���޸ĵ�ʱ�����EEPROM
            FLASH_Lock(FLASH_MEMTYPE_DATA); //����EEPROM
            
            TASK_FIVE->Delay = TASK_FIVE->Period;//ÿ����һ�ΰ�����״̬����ʱ�Զ���װ
            return;
        }   
    }
    
    if( key_funcode == SW1 )//����2
    {
        key_funcode = NONE;
        if( work_state == STATE_INIT )//����ģʽ��
        {
            work_state = STATE_TIME;  //�����޸�ʱ��ģʽ
            SCH_Enable_Task(TASK_FIVE);//ʹ��״̬����ʱ����
            SetLedON(2);              //�޸ĵƵ���
            return;
        }
        if( work_state == STATE_TIME )//�޸�ʱ��ģʽ��
        {
            work_state = STATE_INIT;  //�������ģʽ
            SCH_Disable_Task(TASK_FIVE);//�ر�״̬����ʱ
            SetLedOFF(2);             //����޸ĵ�
            power_flag = OFF;
        } 
    }
}

/************************ (C) COPYRIGHT HARRY007 *****END OF FILE**************/