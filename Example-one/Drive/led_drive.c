/************************ (C) COPYRIGHT HARRY007 *******************************
 * �ļ���  ��led_drive.c
 * ����    ��LED�����ײ㺯�� 
 * ��汾  ��V2.1.0
 * ����    ��HARRY007
 * �޸�ʱ�� ��2016-09-12
*******************************************************************************/


/*************ͷ�ļ�����***************/
#include "head.h"


void Delay(u32 t)
{
    while (t!= 0)
    {
	t--;
    }
}
/*******************************************************************************
 * ����: LED_Init
 * ����: LED����GPIO���ų�ʼ������
 * �β�: ��
 * ����: ��
 * ˵��: �� 
 ******************************************************************************/
void Led_Init(void)
{
    GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_FAST);
    
}

/*******************************************************************************
 * ����: SetLedOFF
 * ����: �ر�ĳͨ����LED
 * �β�: ��
 * ����: ��
 * ˵��: �� 
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
 * ����: SetLedON
 * ����: ��ĳͨ����LED
 * �β�: ��
 * ����: ��
 * ˵��: �� 
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
 * ����: Led_SystemRun
 * ����: ϵͳ����ָʾ��
 * �β�: ��
 * ����: ��
 * ˵��: �� 
 ******************************************************************************/
void Led_SystemRun(void)
{
    GPIO_WriteReverse(GPIOC, GPIO_PIN_7);//ϵͳ����״ָ̬ʾ��   
}


/************************ (C) COPYRIGHT HARRY007 *****END OF FILE**************/