/************************ (C) COPYRIGHT HARRY007 *******************************
 * �ļ���  ��sysclock.c
 * ����    ��ϵͳʱ������   
 * ��汾  ��V2.1.0
 * ����    ��HARRY007
 *�޸�ʱ�� ��2016-09-12
*******************************************************************************/
#ifndef __MAINTASK_H
#define __MAINTASK_H

#include "stm8s.h"

/*******************************************************************************
 * ����: Sysclock_Init
 * ����: ����ϵͳʱ��Ƶ��
 * �β�: ��
 * ����: ��
 * ˵��: 
 ******************************************************************************/
void SystemClock_Init();

/*******************************************************************************
 * ����: system_init
 * ����: ϵͳ�ϵ��ʼ��
 * �β�: ��
 * ����: ��
 * ˵��: �� 
 ******************************************************************************/
void system_init(void);

/*******************************************************************************
 * ����: IWDG_Config
 * ����: ���Ź����ú���
 * �β�: ��
 * ����: ��
 * ˵��: 0.5S 
 ******************************************************************************/
void IWDG_Config(void);

/*******************************************************************************
 * ����: State_Dog
 * ����: ����״̬��ϵͳ���õ���ʱ
 * �β�: ��
 * ����: ��
 * ˵��: �����޸�ʱ��ģʽ����5S���ް������¾��Զ���ת��STATE_INITģʽ��
 ******************************************************************************/
void State_Dog(void);

#endif

/************************ (C) COPYRIGHT HARRY007 *****END OF FILE**************/