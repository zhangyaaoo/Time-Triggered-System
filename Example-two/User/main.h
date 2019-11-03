/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

// #ifdef __MAIN_C_
// #define MAIN_EXT
// #else 
// #define MAIN_EXT extern
// #endif



/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

#include "stm32f10x.h"

#include "Task_Scheduler.h"
#include "timer.h"

#include "led.h"
#include "timer.h"
#include "gpio.h"
#include "usart.h"
#include "iwdg.h"
#include "key.h"

#include "datahandle_moudle.h"
#include "queue_moudle.h"
#include "dll_moudle.h"
#include "led_moudle.h"
#include "input_moudle.h"
#include "usart_moudle.h"
#include "iwdg_moudle.h"
#include "key_moudle.h"
#include "rs485_moudle.h"

#include "debug.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#ifndef NULL
    #define     NULL        (void *)0	 //∂®“Âø’÷∏’Î
#endif

#ifndef TRUE
    #define     TRUE        (1==1)
#endif

#ifndef FALSE
    #define     FALSE       (0==1)
#endif

#ifndef ON
    #define     ON          1
#endif

#ifndef OFF
    #define     OFF         0
#endif

/* Exported functions ------------------------------------------------------- */

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT ZS**********************END OF FILE****/
