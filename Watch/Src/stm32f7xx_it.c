/**
  ******************************************************************************
  * @file    stm32f7xx_it.c
  * @author  Ac6
  * @version V1.0
  * @date    02-Feb-2015
  * @brief   Default Interrupt Service Routines.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "stm32f7xx.h"
#ifdef USE_RTOS_SYSTICK
#include <cmsis_os.h>
#endif
#include "stm32f7xx_it.h"
#include "stm32f769i_discovery.h"
#include "stm32f769i_discovery_lcd.h"
#include "lvgl/lvgl.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern DSI_HandleTypeDef hdsi_discovery;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
extern PCD_HandleTypeDef hpcd;

/******************************************************************************/
/*            	  	    Processor Exceptions Handlers                         */
/******************************************************************************/
#ifndef SYSTICK_TICK_FREQ
#  define SYSTICK_TICK_FREQ     1000 // Hz
#endif

#define SYSTICK_TICK_INTERVAL   (1000 / SYSTICK_TICK_FREQ)
#define SYSTICK_LOAD_VALUE      (SystemCoreClock / SYSTICK_TICK_FREQ)
#define SYSTICK_MILLIS          (SystemTickCount * SYSTICK_TICK_INTERVAL)
static volatile uint32_t SystemTickCount = 0;

/**
  * @brief  This function handles SysTick Handler, but only if no RTOS defines it.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  SystemTickCount++;
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  lv_tick_inc(1);
#ifdef USE_RTOS_SYSTICK
  osSystickHandler();
#endif
}

uint32_t millis(void)
{
    return SYSTICK_MILLIS;
}

void delay_ms(uint32_t ms)
{
    uint32_t tickstart = SystemTickCount;
    uint32_t wait = ms / SYSTICK_TICK_INTERVAL;

    while((SystemTickCount - tickstart) < wait)
    {
    }
}

void delay_us(uint32_t us)
{
    uint32_t total = 0;
    uint32_t target = SystemCoreClock / 1000000U * us;
    int last = SysTick->VAL;
    int now = last;
    int diff = 0;
start:
    now = SysTick->VAL;
    diff = last - now;
    if(diff > 0)
    {
        total += diff;
    }
    else
    {
        total += diff + SYSTICK_LOAD_VALUE;
    }
    if(total > target)
    {
        return;
    }
    last = now;
    goto start;
}
/**
  * @brief  This function handles DSI Handler.
  * @param  None
  * @retval None
  */
void DSI_IRQHandler(void){
  HAL_DSI_IRQHandler(&hdsi_discovery);
}

/**
  * @brief  This function handles USB-On-The-Go FS/HS global interrupt request.
  * @param  None
  * @retval None
  */
void OTG_HS_IRQHandler(void)
{
  HAL_PCD_IRQHandler(&hpcd);
}

