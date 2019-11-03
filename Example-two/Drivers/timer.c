/**
  ******************************************************************************
  * @file    timer.c 
  * @author  ZS
  * @version 
  * @date    05-DEC-2016
  * @brief   
  ******************************************************************************
  * @attention
  *
  * 
  *
  ******************************************************************************
  */

#define __TIMER_C_

/******************************** Includes ************************************/
#include "timer.h"
#include "main.h"


/***************************** Private typedef ********************************/

/***************************** Private define *********************************/

/****************************** Private macro *********************************/

/**************************** Private variables *******************************/

/*********************** Private function prototypes **************************/

/**************************** Private functions *******************************/

/** @funcname  TIM2_Config
  * @brief     None  
  * @param     None
  * @retval    None
  */
void TIM2_Config(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    
    /*** System Clocks Configuration ***/
    
    /* PCLK1 = HCLK/4 */
    RCC_PCLK1Config(RCC_HCLK_Div4);

    /* TIM2 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    /*** NVIC Configuration ***/
    
    /* Enable the TIM2 global Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    
    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = 9;//time period = 100us * (9+1) = 1ms.
    TIM_TimeBaseStructure.TIM_Prescaler = 3599;// frequency = 36MHz/(3599+1) = 10KHZ; period = 1/10KHZ = 100us.
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    
    /* TIM IT enable */
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); 
}  

/** @funcname  TIM2_IRQHandler
  * @brief     This function handles TIM2 interrupt request. 
  * @param     None
  * @retval    None
  */
void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //check the TIM2's update interrupt flag
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //clean the TIM2's update interrupt flag

        //TIME_ELAPSE_DEBUG_LED_ON(LED1_PORT,LED1);
        
        SCH_Update();
        
        //TIME_ELAPSE_DEBUG_LED_OFF(LED1_PORT,LED1);
    }  
}


/** @funcname  TIM3_Config
  * @brief     None  
  * @param     None
  * @retval    None
  */
void TIM3_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
    NVIC_InitTypeDef NVIC_InitStructure; 
    
    /*** NVIC Configuration ***/
    
    /* Enable the TIM2 global Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 7; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
	
    /* TIM2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);

     /* Time base configuration */
	TIM_TimeBaseStruct.TIM_Period=49;//time period = 10us * (49+1) = 500us.
	TIM_TimeBaseStruct.TIM_Prescaler=359;// frequency = 36MHz/(359+1) = 100KHZ; period = 1/100KHz = 10us.
	TIM_TimeBaseStruct.TIM_ClockDivision=0;
	TIM_TimeBaseStruct.TIM_CounterMode=TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStruct);

	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3,ENABLE);	 

    

	
}

/** @funcname  TIM3_IRQHandler
  * @brief     This function handles TIM3 interrupt request. 
  * @param     None
  * @retval    None
  */
void TIM3_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);

	
}

/************************ (C) COPYRIGHT ZS ************** END OF FILE *********/
