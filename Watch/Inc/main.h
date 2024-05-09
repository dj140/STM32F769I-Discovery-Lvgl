/**
  ******************************************************************************
  * @file    LCD_DSI/LCD_DSI_CmdMode_DoubleBuffering/Inc/main.h
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif
  
/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "stm32f7xx_it.h"

#include "tft.h"
#include "touchpad.h"
#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/demos/lv_demos.h"
  
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_msc.h"
#include "usbd_storage.h"
  
#include "stm32f769i_discovery.h"
#include "stm32f769i_discovery_sd.h"
#include "stm32f769i_discovery_lcd.h"
#include "stm32f769i_discovery_qspi.h"

/* FatFs includes component */
//#include "ff_gen_drv.h"
//#include "sd_diskio.h"
#include "ff.h"
#include "diskio.h"

//#include "fonts/fonts.h"
//#include "icon/anim/icon_anim.h"
//#include "icon/static/icon_static.h"

#include "bsp_debug_usart.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void Toggle_Leds(void);
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

