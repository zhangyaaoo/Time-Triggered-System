/************************ (C) COPYRIGHT HARRY007 *******************************
 * �ļ���  ��led_drive.h
 * ����    ��LED�����ײ㺯�� 
 * ��汾  ��V2.1.0
 * ����    ��HARRY007
 * �޸�ʱ�� ��2016-09-12
*******************************************************************************/

#ifndef __LED_DRIVE_H
#define __LED_DRIVE_H

#include "stm8s.h"
/*******************************************************************************
 * ����: LED_Init
 * ����: LED����GPIO���ų�ʼ������
 * �β�: ��
 * ����: ��
 * ˵��: �� 
 ******************************************************************************/
void Led_Init(void);

/*******************************************************************************
 * ����: SetLedOFF
 * ����: �ر�ĳͨ����LED
 * �β�: ��
 * ����: ��
 * ˵��: �� 
 ******************************************************************************/
void SetLedOFF(u8 channel);

/*******************************************************************************
 * ����: SetLedON
 * ����: ��ĳͨ����LED
 * �β�: ��
 * ����: ��
 * ˵��: �� 
 ******************************************************************************/
void SetLedON(u8 channel);

/*******************************************************************************
 * ����: LedAlarm
 * ����: ����ָʾ��
 * �β�: ��
 * ����: ��
 * ˵��: �� 
 ******************************************************************************/
void LedAlarm(void);

/*******************************************************************************
 * ����: Led_SystemRun
 * ����: ϵͳ����ָʾ��
 * �β�: ��
 * ����: ��
 * ˵��: �� 
 ******************************************************************************/
void Led_SystemRun(void);

#endif


/************************ (C) COPYRIGHT HARRY007 *****END OF FILE**************/