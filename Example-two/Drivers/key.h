/**
  ******************************************************************************
  * @file    key.h 
  * @author  ZS
  * @version 
  * @date    06-DEC-2016
  * @brief   Header for key.c module
  ******************************************************************************
  * @attention
  *
  * 
  *
  ******************************************************************************
  */
 
/**************** Define to prevent recursive inclusion ***********************/
#ifndef __KEY_H_
#define __KEY_H_

#ifdef __KEY_C_
#define KEY_EXT
#else 
#define KEY_EXT extern
#endif


/****************************** Includes **************************************/
#include "stm32f10x.h"
#include "led.h"

/************************** Exported types ************************************/
typedef enum Key_State
{
    Key_Original = 0,
    Key_1,
    Key_2,
    Key_3,
    Key_4,
    Key_5,
}tKeyState;

typedef struct KeyScan 
{
    uint32_t        DownCnt;
    uint32_t        UpCnt;
    uint8_t         FunCode;
    tKeyState       State;
    GPIO_TypeDef   *Port;
    uint16_t        Pin;
}tKeyScan;


/************************* Exported constants *********************************/
KEY_EXT tKeyScan Key1;
KEY_EXT tKeyScan Key2;


/************************** Exported macro ************************************/
#define KEY_PORT_CLK   (RCC_APB2Periph_GPIOC)
#define KEY1_PORT_CLK  (RCC_APB2Periph_GPIOC)
#define KEY2_PORT_CLK  (RCC_APB2Periph_GPIOC)

#define KEY_PORT       (GPIOC)
#define KEY1_PORT      (GPIOC)
#define KEY2_PORT      (GPIOC)

#define KEY1           (GPIO_Pin_4)
#define KEY2           (GPIO_Pin_5)

#define KEY_DOWN        0x00            

#define CLICK_PERIOD        10          //单击按下最短时间          10*5   = 50ms
#define LOOSEN_PERIOD       40          //双击间隔最长时间          40*5   = 200ms
#define LONGCLICK_PERIOD    150         //长按最短时间              100*5  = 500ms

#define CLICK           0x01
#define DBCLICK         0x02
#define LCLICK          0x03



/************************* Exported functions *********************************/
KEY_EXT void KEY_Config     (void);
KEY_EXT void KEY_Scan       (tKeyScan *Key);
KEY_EXT void KEY_Analysisi  (tKeyScan *Key);



#endif /* __KEY_H_ */

/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
