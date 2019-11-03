/************************ (C) COPYRIGHT HARRY007 *******************************
 * �ļ���  ��eeprom_virtual.c
 * ����    ��eepromӦ�ò�
 * ��汾  ��V2.1.0
 * ����    ��������
 * �޸�ʱ�� ��2016-09-13  
*******************************************************************************/

/*************ͷ�ļ�����***************/
#include "head.h"

/*******************************************************************************
 * ����: E2PROM_Init
 * ����: EEPROM��ʼ��
 * �β�: ��
 * ����: ��
 * ˵��: �� 
 ******************************************************************************/
void E2PROM_Init(void)
{
    /* ���ù̶��ı��ʱ�� */
    FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);

    FLASH_Unlock(FLASH_MEMTYPE_DATA);//����EEPROM
    
    if( FLASH_ReadByte(0X407F) != 0XAA )//������°��ӣ���ʱʱ��Ĭ��10Min
    {
        /*���°���*/
        FLASH_ProgramByte(0X407F,0XAA);//ˢ��֮����Ǿɰ����ˡ���

        FLASH_ProgramByte(0x4000, 1);//Ĭ�ϴ�10Min
    }
    else
    {
        /*�ɰ���*/
        TASK_ONE->Period = FLASH_ReadByte(0x4000)*MIN_10;
        TASK_ONE->Delay = TASK_ONE->Period;
    }
    FLASH_Lock(FLASH_MEMTYPE_DATA); //����EEPROM
}




/************************ (C) COPYRIGHT HARRY007 *****END OF FILE**************/