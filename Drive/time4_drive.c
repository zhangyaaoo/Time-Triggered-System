/************************ (C) COPYRIGHT HARRY007 *******************************
 * �ļ���  ��time4_drive.c
 * ����    ��TIME4��ʱ���ײ�����
 * ��汾  ��V2.1.0
 * ����    ��HARRY007
 * �޸�ʱ�� ��2016-09-011
*******************************************************************************/


/* �����Զ���ͷ�ļ� */
#include "time4_drive.h"

/*******************************************************************************
 * ����: Time4_Init
 * ����: ��ʱ��4��ʼ��
 * �β�: ��
 * ����: ��
 * ˵��: ��ʱ��4����һ��1ms��ʱ���׼
 ******************************************************************************/
void Time4_Init(void)
{
    TIM4_TimeBaseInit(TIM4_PRESCALER_128, 249);//���۶�ʱ�ж�ʱ��8us*250=2MS
    TIM4_PrescalerConfig(TIM4_PRESCALER_128, TIM4_PSCRELOADMODE_IMMEDIATE);
    TIM4_ARRPreloadConfig(ENABLE);
    TIM4_ClearFlag(TIM4_FLAG_UPDATE);
    TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
    TIM4_Cmd(ENABLE);
}

/*******ע����ʱ��4���жϺ����ڿ�汾�ļ�stm8s_it.c�ļ���********************/

/************************ (C) COPYRIGHT HARRY007 *****END OF FILE**************/