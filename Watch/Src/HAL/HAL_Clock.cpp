#include "HAL.h"
//#include "rtc.h"
#include "stm32f7xx_hal.h"
#include "bsp_debug_usart.h"

RTC_HandleTypeDef RtcHandle;
/* Defines related to Clock configuration */
#define RTC_ASYNCH_PREDIV  0x7F   /* LSE as RTC clock */
#define RTC_SYNCH_PREDIV   0x00FF /* LSE as RTC clock */
/* Buffers used for displaying Time and Date */
uint8_t aShowTime[50] = {0};
uint8_t aShowDate[50] = {0};
/**
  * @brief  Configure the current time and date.
  * @param  None
  * @retval None
  */
static void RTC_CalendarConfig(void)
{
  RTC_DateTypeDef sdatestructure;
  RTC_TimeTypeDef stimestructure;

  /*##-1- Configure the Date #################################################*/
  /* Set Date: Tuesday February 18th 2014 */
  sdatestructure.Year = 0x14;
  sdatestructure.Month = RTC_MONTH_FEBRUARY;
  sdatestructure.Date = 0x18;
  sdatestructure.WeekDay = RTC_WEEKDAY_TUESDAY;
  
  if(HAL_RTC_SetDate(&RtcHandle,&sdatestructure,RTC_FORMAT_BCD) != HAL_OK)
  {
    /* Initialization Error */
//    Error_Handler();
  }

  /*##-2- Configure the Time #################################################*/
  /* Set Time: 02:00:00 */
  stimestructure.Hours = 0x02;
  stimestructure.Minutes = 0x00;
  stimestructure.Seconds = 0x00;
  stimestructure.TimeFormat = RTC_HOURFORMAT12_AM;
  stimestructure.DayLightSaving = RTC_DAYLIGHTSAVING_NONE ;
  stimestructure.StoreOperation = RTC_STOREOPERATION_RESET;

  if (HAL_RTC_SetTime(&RtcHandle, &stimestructure, RTC_FORMAT_BCD) != HAL_OK)
  {
    /* Initialization Error */
//    Error_Handler();
  }

  /*##-3- Writes a data in a RTC Backup data Register1 #######################*/
  HAL_RTCEx_BKUPWrite(&RtcHandle, RTC_BKP_DR1, 0x32F2);
}

void HAL::Clock_Init()
{
//    RTC_Init();
/*##-1- Configure the RTC peripheral #######################################*/
  /* Configure RTC prescaler and RTC data registers */
  /* RTC configured as follows:
      - Hour Format    = Format 24
      - Asynch Prediv  = Value according to source clock
      - Synch Prediv   = Value according to source clock
      - OutPut         = Output Disable
      - OutPutPolarity = High Polarity
      - OutPutType     = Open Drain */ 
  RtcHandle.Instance = RTC; 
  RtcHandle.Init.HourFormat = RTC_HOURFORMAT_24;
  RtcHandle.Init.AsynchPrediv = RTC_ASYNCH_PREDIV;
  RtcHandle.Init.SynchPrediv = RTC_SYNCH_PREDIV;
  RtcHandle.Init.OutPut = RTC_OUTPUT_DISABLE;
  RtcHandle.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  RtcHandle.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;

  /*##-2- Check if Data stored in BackUp register1: No Need to reconfigure RTC#*/
  /* Read the Back Up Register 1 Data */
  if (HAL_RTCEx_BKUPRead(&RtcHandle, RTC_BKP_DR1) != 0x32F2)
  {
    /* Configure RTC Calendar */
    RTC_CalendarConfig();
  }
  else
  {
    /* Check if the Power On Reset flag is set */
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST) != RESET)
    {
      /* Turn on LED2: Power on reset occurred */
//      BSP_LED_On(LED2);
    }
    /* Check if Pin Reset flag is set */
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST) != RESET)
    {
      /* Turn on LED1: External reset occurred */
//      BSP_LED_On(LED1);
    }
    /* Clear source Reset Flag */
    __HAL_RCC_CLEAR_RESET_FLAGS();
  }

//    Clock_Info_t info;
//    Clock_GetInfo(&info);
//    Serial.printf(
//        "Clock: %04d-%02d-%02d %s %02d:%02d:%02d\r\n",
//        info.year,
//        info.month,
//        info.day,
//        Clock_GetWeekString(info.week),
//        info.hour,
//        info.minute,
//        info.second
//    );
}

void HAL::Clock_GetInfo(Clock_Info_t* info)
{
//    RTC_Calendar_TypeDef calendar;
//    RTC_GetCalendar(&calendar);

  RTC_DateTypeDef sdatestructureget;
  RTC_TimeTypeDef stimestructureget;

  /* Get the RTC current Time */
  HAL_RTC_GetTime(&RtcHandle, &stimestructureget, RTC_FORMAT_BIN);
  /* Get the RTC current Date */
  HAL_RTC_GetDate(&RtcHandle, &sdatestructureget, RTC_FORMAT_BIN);
//  /* Display time Format : hh:mm:ss */
//  sprintf(ashowtime[1], "%2d:%2d:%2d", stimestructureget.Hours, stimestructureget.Minutes, stimestructureget.Seconds);
//  /* Display date Format : mm-dd-yy */
//  sprintf(ashowdate[], "%2d-%2d-%2d", sdatestructureget.Month, sdatestructureget.Date, 2000 + sdatestructureget.Year);
  printf("time: %2d:%2d:%2d \n", stimestructureget.Hours, stimestructureget.Minutes, stimestructureget.Seconds);
  info->year = sdatestructureget.Year;
    info->month = sdatestructureget.Month;
    info->day = sdatestructureget.Date;
    info->week = sdatestructureget.WeekDay;
    info->hour = stimestructureget.Hours;
    info->minute = stimestructureget.Minutes;
    info->second = stimestructureget.Seconds;
    info->millisecond = 0;
}

void HAL::Clock_SetInfo(const Clock_Info_t* info)
{
//    RTC_SetTime(
//        info->year,
//        info->month,
//        info->day,
//        info->hour,
//        info->minute,
//        info->second
//    );
}

const char* HAL::Clock_GetWeekString(uint8_t week)
{
    const char* week_str[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    return week < 7 ? week_str[week] : "";
}
