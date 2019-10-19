/* 所有使用到的头文件 */
#include "stm8s.h"

#include "maintask.h"
#include "led_drive.h"
#include "key_drive.h"
#include "relay_drive.h"
#include "time4_drive.h"

#include "Task_Scheduler.h"
#include "relay_virtual.h"
#include "led_virtual.h"
#include "eeprom_virtual.h"

#ifndef NULL
    #define NULL (void *)0	 //空指针
#endif

#ifndef TRUE
    #define TRUE	 (1==1)
#endif

#ifndef FALSE
    #define FALSE (0==1)
#endif

#ifndef ON
    #define ON     1
#endif

#ifndef OFF
    #define OFF    0
#endif

/***********************************/
#define STATE_INIT    0
#define STATE_TIME    1
#define STATE_RUN     2

#define MIN_10        300000

/***********************************/

extern sTaskH *TASK_ONE;
extern sTaskH *TASK_TWO;
extern sTaskH *TASK_THREE;
extern sTaskH *TASK_FOUR;
extern sTaskH *TASK_FIVE;

extern u8 work_state;
extern u8 power_flag;







