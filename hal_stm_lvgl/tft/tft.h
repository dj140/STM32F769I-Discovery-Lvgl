/**
 * @file disp.h
 * 
 */

#ifndef DISP_H
#define DISP_H

#ifdef __cplusplus
 extern "C" {
#endif
/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include "lvgl/lvgl.h"

/*********************
 *      DEFINES
 *********************/
#define TFT_HOR_RES     800
#define TFT_VER_RES     480
#define TFT_NO_TEARING  1    /*1: no tearing but slower*/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void tft_init(void);

/**********************
 *      MACROS
 **********************/
#ifdef __cplusplus
}
#endif

#endif
