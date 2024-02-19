/**
  ******************************************************************************
  * @file    sh8601b.h
  * @author  SHT FAE Team
  * @brief   This file contains all the constants parameters for the SH8601B
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SH8601B_H
#define __SH8601B_H

#ifdef __cplusplus
 extern "C" {
#endif

//#define __TARGET_EDO_1_4_1_PANEL_PREREG__

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
/** @addtogroup BSP
  * @{
  */

/** @addtogroup Components
  * @{
  */

/** @addtogroup sh8601b
  * @{
  */

/** @addtogroup SH8601B_Exported_Variables
  * @{
  */

#if defined ( __GNUC__ )
#ifndef __weak
#define __weak __attribute__((weak))
#endif /* __weak */
#endif /* __GNUC__ */

/**
 *  @brief OLED Panel Model
 */
#define PANEL_EDO_E01                                   (0x00)
#define PANEL_EDO_E02                                   (0x01)
#define PANEL_INFINITRUE_E02                            (0x02)
#define PANEL_TRULY_R01_HOLE                            (0x03)
#define PANEL_TRULY_R01_NO_HOLE                         (0x04)

/**
 *  @brief OLED DSI Packet Type
 */
#define SHT_DSI_DCS_SHORT_PKT_WRITE_P0                  (1)
#define SHT_DSI_DCS_SHORT_PKT_WRITE_P1                  (2)
#define SHT_DSI_GEN_SHORT_PKT_WRITE_P0                  (3)
#define SHT_DSI_GEN_SHORT_PKT_WRITE_P1                  (4)
#define SHT_DSI_GEN_SHORT_PKT_WRITE_P2                  (5)
#define SHT_DSI_DCS_LONG_PKT_WRITE                      (6)
#define SHT_DSI_GEN_LONG_PKT_WRITE                      (7)
#define SHT_DSI_GEN_SHORT_PKT_READ_P1                      (8)

/**
 *  @brief LCD_OrientationTypeDef
 *  Possible values of Display Orientation
 */
#define SH8601B_ORIENTATION_PORTRAIT    ((uint32_t)0x00) /* Portrait orientation choice of LCD screen  */
#define SH8601B_ORIENTATION_LANDSCAPE   ((uint32_t)0x01) /* Landscape orientation choice of LCD screen */

/**
 *  @brief  Possible values of
 *  pixel data format (ie color coding) transmitted on DSI Data lane in DSI packets
 */
#define SH8601B_FORMAT_RGB888    ((uint32_t)0x00) /* Pixel format chosen is RGB888 : 24 bpp */
#define SH8601B_FORMAT_RBG565    ((uint32_t)0x02) /* Pixel format chosen is RGB565 : 16 bpp */

#if defined(__TARGET_EDO_1_4_PANEL_MODULE__)
/**
  * @brief  EDO 1.4" Panel Size
  */

/* Width and Height in Portrait mode */
#define  SH8601B_PORTRAIT_WIDTH             ((uint16_t)400)     /* LCD PIXEL WIDTH   */
#define  SH8601B_PORTRAIT_HEIGHT            ((uint16_t)400)     /* LCD PIXEL HEIGHT  */

/* Width and Height in Landscape mode */
#define  SH8601B_LANDSCAPE_WIDTH            ((uint16_t)400)     /* LCD PIXEL WIDTH   */
#define  SH8601B_LANDSCAPE_HEIGHT           ((uint16_t)400)     /* LCD PIXEL HEIGHT  */
#elif defined(__TARGET_EDO_1_4_1_PANEL_MODULE__)
/**
  * @brief  EDO 1.4" Panel Size
  */

/* Width and Height in Portrait mode */
#define  SH8601B_PORTRAIT_WIDTH             ((uint16_t)320)     /* LCD PIXEL WIDTH   */
#define  SH8601B_PORTRAIT_HEIGHT            ((uint16_t)360)     /* LCD PIXEL HEIGHT  */

/* Width and Height in Landscape mode */
#define  SH8601B_LANDSCAPE_WIDTH            ((uint16_t)320)     /* LCD PIXEL WIDTH   */
#define  SH8601B_LANDSCAPE_HEIGHT           ((uint16_t)360)     /* LCD PIXEL HEIGHT  */
#else
/**
  * @brief  EDO 1.4" Panel Size
  */

/* Width and Height in Portrait mode */
#define  SH8601B_PORTRAIT_WIDTH             ((uint16_t)400)     /* LCD PIXEL WIDTH   */
#define  SH8601B_PORTRAIT_HEIGHT            ((uint16_t)400)     /* LCD PIXEL HEIGHT  */

/* Width and Height in Landscape mode */
#define  SH8601B_LANDSCAPE_WIDTH            ((uint16_t)400)     /* LCD PIXEL WIDTH   */
#define  SH8601B_LANDSCAPE_HEIGHT           ((uint16_t)400)     /* LCD PIXEL HEIGHT  */
#endif

/**
  * @brief  EDO 1.4" Panel Timing parameters for Portrait orientation mode
  */
#define  SH8601B_PORTRAIT_HSYNC             ((uint16_t)2)      /* Horizontal synchronization */
#define  SH8601B_PORTRAIT_HBP               ((uint16_t)34)     /* Horizontal back porch      */
#define  SH8601B_PORTRAIT_HFP               ((uint16_t)34)     /* Horizontal front porch     */
#define  SH8601B_PORTRAIT_VSYNC             ((uint16_t)1)      /* Vertical synchronization   */
#define  SH8601B_PORTRAIT_VBP               ((uint16_t)15)     /* Vertical back porch        */
#define  SH8601B_PORTRAIT_VFP               ((uint16_t)16)     /* Vertical front porch       */

/**
  * @brief  EDO 1.4" Panel Timing parameters for Landscape orientation mode
  *         Same values as for Portrait mode in fact.
  */
#define  SH8601B_LANDSCAPE_HSYNC            SH8601B_PORTRAIT_VSYNC  /* Horizontal synchronization */
#define  SH8601B_LANDSCAPE_HBP              SH8601B_PORTRAIT_VBP    /* Horizontal back porch      */
#define  SH8601B_LANDSCAPE_HFP              SH8601B_PORTRAIT_VFP    /* Horizontal front porch     */
#define  SH8601B_LANDSCAPE_VSYNC            SH8601B_PORTRAIT_HSYNC  /* Vertical synchronization   */
#define  SH8601B_LANDSCAPE_VBP              SH8601B_PORTRAIT_HBP    /* Vertical back porch        */
#define  SH8601B_LANDSCAPE_VFP              SH8601B_PORTRAIT_HFP    /* Vertical front porch       */


/* List of SH8601B used commands                                  */
#define  SH8601B_CMD_NOP                   0x00  /* NOP command */
#define  SH8601B_CMD_SWRESET               0x01  /* Sw reset command */
#define  SH8601B_CMD_RDDIDIF               0x04  /* Read Display Identification Information command */
#define  SH8601B_CMD_RDNUMED               0x05  /* Read Number of Errors on DSI command */
#define  SH8601B_CMD_RDDPM                 0x0A  /* Read Display Power Mode */
#define  SH8601B_CMD_RDDMADCTL             0x0B  /* Read Display MADCTR command : read memory display access ctrl */
#define  SH8601B_CMD_RDDCOLMOD             0x0C  /* Read Display pixel format command */
#define  SH8601B_CMD_RDDIM                 0x0D  /* Read Display Image Mode command */
#define  SH8601B_CMD_RDDSM                 0x0E  /* Read Display Signal Mode command */
#define  SH8601B_CMD_RDDSDR                0x0F  /* Read Display Self-Diagnostic Result command */
#define  SH8601B_CMD_SLPIN                 0x10  /* Sleep In command */
#define  SH8601B_CMD_SLPOUT                0x11  /* Sleep Out command */
#define  SH8601B_CMD_PTLON                 0x12  /* Partial mode On command */
#define  SH8601B_CMD_NORON                 0x13  /* Normal Display mode on command */
#define  SH8601B_CMD_INVOFF                0x20  /* Inversion Off command */
#define  SH8601B_CMD_INVON                 0x21  /* Inversion On command */
#define  SH8601B_CMD_ALLOFF                0x22  /* All Pixel Off command */
#define  SH8601B_CMD_ALLON                 0x23  /* All Pixel On command */
#define  SH8601B_CMD_DISPOFF               0x28  /* Display Off command */
#define  SH8601B_CMD_DISPON                0x29  /* Display On command */
#define  SH8601B_CMD_CASET                 0x2A  /* Column address set command */
#define  SH8601B_CMD_PASET                 0x2B  /* Page address set command */
#define  SH8601B_CMD_RAMWR                 0x2C  /* Memory (GRAM) write command */
#define  SH8601B_CMD_PTLAR                 0x30  /* Partial Area Row Set command */
#define  SH8601B_CMD_PTLAC                 0x31  /* Partial Area Column Set command */
#define  SH8601B_CMD_TEOFF                 0x34  /* Tearing Effect Line Off command : command with no parameter */
#define  SH8601B_CMD_TEON                  0x35  /* Tearing Effect Line On command : command with 1 parameter 'TELOM' */
#define  SH8601B_CMD_MADCTR                0x36  /* Memory Data Access control command  */
#define  SH8601B_CMD_IDMOFF                0x38  /* Idle mode Off command */
#define  SH8601B_CMD_IDMON                 0x39  /* Idle mode On command  */
#define  SH8601B_CMD_COLMOD                0x3A  /* Control Interface Pixel command */
#define  SH8601B_CMD_RAMWRC                0x3C  /* Memory write continue command */
#define  SH8601B_CMD_TESCAN                0x44  /* Set Tear Scan Line command */
#define  SH8601B_CMD_RDSCL                 0x45  /* Read Tear Scan Line Number command */
#define  SH8601B_CMD_SPI_RDON              0x46  /* SPI Read On command */
#define  SH8601B_CMD_SPI_RDOFF             0x47  /* SPI Read Off command */
#define  SH8601B_CMD_DSTB_CTRL             0x4F  /* Deep Standby Mode On */
#define  SH8601B_CMD_WRDISBV               0x51  /* Write Display Brightness command */
#define  SH8601B_CMD_RDDISBV               0x52  /* Read Display Brightness Value command */
#define  SH8601B_CMD_WRCTRLD1              0x53  /* Write CTRL Display 1 command */
#define  SH8601B_CMD_RDCTRLD1              0x54  /* Read CTRL Display 1 command */
#define  SH8601B_CMD_WRCTRLD2              0x55  /* Write CTRL Display 2 command */
#define  SH8601B_CMD_RDCTRLD2              0x56  /* Read CTRL Display 2 command */
#define  SH8601B_CMD_AODOFF                0x58  /* AOD Mode Off command */
#define  SH8601B_CMD_AODON                 0x59  /* Aod Mode On command */
#define  SH8601B_CMD_AOD_WRDISBV           0x61  /* Write Display Brightness in AOD mode command */
#define  SH8601B_CMD_AOD_RDDISBV           0x62  /* Read Display Brightness in AOD mode command */
#define  SH8601B_CMD_HBM_WRDISBV           0x63  /* Write Display Brightness in HBM mode command */
#define  SH8601B_CMD_HBM_RDDISBV           0x64  /* Read Display Brightness in HBM mode command */
#define  SH8601B_CMD_READ_ID1              0xDA
#define  SH8601B_CMD_READ_ID2              0xDB
#define  SH8601B_CMD_READ_ID3              0xDC

/**
  * @}
  */
   
/* Exported macro ------------------------------------------------------------*/
   
/** @defgroup SH8601B_Exported_Macros SH8601B Exported Macros
  * @{
  */ 

/**
  * @}
  */ 

/* Exported functions --------------------------------------------------------*/
  
/** @addtogroup SH8601B_Exported_Functions
  * @{
  */
void DSI_IO_WriteCmd(uint8_t type, uint8_t m_cmd, uint32_t m_size,  uint8_t* payload);
void DSI_IO_Read(uint8_t cmd, uint8_t *buffer, uint32_t size);
void DSI_IO_Read1Param(uint8_t param, uint8_t *buffer, uint32_t size);
void DSI_IO_Read2Param(uint16_t param, uint8_t *buffer, uint32_t size);
void SH8601B_Init(uint8_t panel);
void SH8601B_IO_Delay(uint32_t Delay);
/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif /* __SH8601B_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
