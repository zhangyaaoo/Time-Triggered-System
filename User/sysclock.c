/************************ (C) COPYRIGHT HARRY007 *******************************
 * �ļ���  ��sysclock.c
 * ����    ��ϵͳʱ������   
 * ��汾  ��V2.1.0
 * ����    ��HARRY007
 *�޸�ʱ�� ��2016-09-09
*******************************************************************************/

#include "maintask.h"

/*******************************************************************************
 * ����: Sysclock_Init
 * ����: ����ϵͳʱ��Ƶ��
 * �β�: ��
 * ����: ��
 * ˵��: 
 ******************************************************************************/
void SystemClock_Init(void)
{
    CLK_HSICmd(ENABLE);//�����ڲ�����ʱ��
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);//����HSIʱ�ӷ�Ƶϵ��Ϊ1��16MHZ����CPU  
}

/************************ (C) COPYRIGHT HARRY007 *****END OF FILE**************/