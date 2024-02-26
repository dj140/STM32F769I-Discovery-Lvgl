/**
  ******************************************************************************
  * @file    USB_Device/MSC_Standalone/Src/usbd_storage.c
  * @author  MCD Application Team
  * @brief   Memory management layer
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usbd_storage.h"
#include "stm32f769i_discovery_sd.h"
#include "stm32f769i_discovery_qspi.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//#define STORAGE_LUN_NBR                  1
#define STORAGE_BLK_NBR                  0x10000
#define STORAGE_BLK_SIZ                  0x200
#define USER_STORAGE_BLK_SIZ                  4096

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* USB Mass storage Standard Inquiry Data */
int8_t STORAGE_Inquirydata[] = { /* 36 */
    /* LUN 0 */
    0x00,
    0x80,
    0x02,
    0x02,
    (STANDARD_INQUIRY_DATA_LEN - 4),
    0x00,
    0x00,
    0x00,
    /* Vendor Identification */
    'A', 'L', 'I', 'E', 'N', 'T', 'E', 'K', ' ',/* 9字节 */
    /* Product Identification */
    'S', 'P', 'I', ' ', 'F', 'l', 'a', 's', 'h',/* 15字节 */
    ' ', 'D', 'i', 's', 'k', ' ',
    /* Product Revision Level */
    '1', '.', '0', ' ',							/* 4字节 */

    /* LUN 1 */
    0x00,
    0x80,
    0x02,
    0x02,
    (STANDARD_INQUIRY_DATA_LEN - 4),
    0x00,
    0x00,
    0x00,
    /* Vendor Identification */
    'A', 'L', 'I', 'E', 'N', 'T', 'E', 'K', ' ',	/* 9字节 */
    /* Product Identification */
    'S', 'D', ' ', 'F', 'l', 'a', 's', 'h', ' ',/* 15字节 */
    'D', 'i', 's', 'k', ' ', ' ',
    /* Product Revision Level */
    '1', '.', '0', ' ',                      	/* 4字节 */
    
};

/* Private function prototypes -----------------------------------------------*/
int8_t STORAGE_Init(uint8_t lun);
int8_t STORAGE_GetCapacity(uint8_t lun, uint32_t *block_num, uint16_t *block_size);
int8_t STORAGE_IsReady(uint8_t lun);
int8_t STORAGE_IsWriteProtected(uint8_t lun);
int8_t STORAGE_Read(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
int8_t STORAGE_Write(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
int8_t STORAGE_GetMaxLun(void);

USBD_StorageTypeDef USBD_DISK_fops = {
  STORAGE_Init,
  STORAGE_GetCapacity,
  STORAGE_IsReady,
  STORAGE_IsWriteProtected,
  STORAGE_Read,
  STORAGE_Write,
  STORAGE_GetMaxLun,
  STORAGE_Inquirydata,
};
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the storage unit (medium)
  * @param  lun: Logical unit number
  * @retval Status (0 : OK / -1 : Error)
  */
int8_t STORAGE_Init(uint8_t lun)
{
    switch (lun)
  {
      case 0: /* SPI FLASH */
          /* 没有初始化函数！不能调用：NORFLASH_Init！调用该函数将导致QSPI内存映射模式失效,程序运行可能异常
           * 因为在sys.c里面,开启内存映射的时候，已经初始化QSPI接口了 
           */
//          BSP_QSPI_Init();
          break;

      case 1: /* SD卡 */
//          BSP_SD_Init();
          break;
  }
//  BSP_SD_Init();
  return 0;
}

/**
  * @brief  Returns the medium capacity.
  * @param  lun: Logical unit number
  * @param  block_num: Number of total block number
  * @param  block_size: Block size
  * @retval Status (0: OK / -1: Error)
  */
int8_t STORAGE_GetCapacity(uint8_t lun, uint32_t *block_num, uint16_t *block_size)
{
  HAL_SD_CardInfoTypeDef info;
  int8_t ret = -1;
  switch (lun)
  {
      case 0: /* SPI FLASH */
            *block_size = 4096;
            *block_num = 1024*16;
                  ret = 0;
          break;

      case 1: /* SD卡 */
          if(BSP_SD_IsDetected() != SD_NOT_PRESENT)
          {
            BSP_SD_GetCardInfo(&info);

            *block_num = info.LogBlockNbr;
            *block_size = info.LogBlockSize;
            ret = 0;
          }
          break;
  }
  return ret;
}

/**
  * @brief  Checks whether the medium is ready.
  * @param  lun: Logical unit number
  * @retval Status (0: OK / -1: Error)
  */
int8_t STORAGE_IsReady(uint8_t lun)
{
  static int8_t prev_status = 0;
  int8_t ret = -1;

  if(BSP_SD_IsDetected() != SD_NOT_PRESENT)
  {
    if(prev_status < 0)
    {
      BSP_SD_Init();
      prev_status = 0;

    }
    if(BSP_SD_GetCardState() == SD_TRANSFER_OK)
    {
      ret = 0;
    }
  }
  else if(prev_status == 0)
  {
    prev_status = -1;
  }
  return 0;
}

/**
  * @brief  Checks whether the medium is write protected.
  * @param  lun: Logical unit number
  * @retval Status (0: write enabled / -1: otherwise)
  */
int8_t STORAGE_IsWriteProtected(uint8_t lun)
{
  return 0;
}

/**
  * @brief  Reads data from the medium.
  * @param  lun: Logical unit number
  * @param  blk_addr: Logical block address
  * @param  blk_len: Blocks number
  * @retval Status (0: OK / -1: Error)
  */
int8_t STORAGE_Read(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
{
  int8_t ret = -1;
  uint16_t i = 0;
  uint32_t timeout = 100000;
    switch (lun)
    {
      case 0: /* SPI FLASH */
//          for(i = 0;i < blk_len;i++)
//          {
//                    BSP_QSPI_Read(buf, blk_addr * 512, blk_len * 512);
//          }
          for(i = 0;i < blk_len;i++)
          {
            BSP_QSPI_Read(buf + i * USER_STORAGE_BLK_SIZ, blk_addr * USER_STORAGE_BLK_SIZ+ i * USER_STORAGE_BLK_SIZ, USER_STORAGE_BLK_SIZ);
          }
      break;

      case 1: /* SD卡 */
          if(BSP_SD_IsDetected() != SD_NOT_PRESENT)
          {
            BSP_SD_ReadBlocks((uint32_t *)buf, blk_addr, blk_len, 1000);

            /* Wait until SD card is ready to use for new operation */
            while(BSP_SD_GetCardState() != SD_TRANSFER_OK)
            {
              if (timeout-- == 0)
              {
                return ret;
              }
            }
            ret = 0;
          }
      break;
    }
  return ret;
}

/**
  * @brief  Writes data into the medium.
  * @param  lun: Logical unit number
  * @param  blk_addr: Logical block address
  * @param  blk_len: Blocks number
  * @retval Status (0 : OK / -1 : Error)
  */
int8_t STORAGE_Write(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
{
  int8_t ret = -1;
    uint16_t i = 0;

  uint32_t timeout = 100000;
    switch (lun)
    {
        case 0: /* SPI FLASH */
//            BSP_QSPI_Write(buf, blk_addr * 512, blk_len * 512);
            for(i = 0;i < blk_len;i++)
            {
              BSP_QSPI_Write((uint8_t *)(buf + i * USER_STORAGE_BLK_SIZ),blk_addr * USER_STORAGE_BLK_SIZ + i * USER_STORAGE_BLK_SIZ,USER_STORAGE_BLK_SIZ );
            }
            break;

        case 1: /* SD卡 */
            if(BSP_SD_IsDetected() != SD_NOT_PRESENT)
            {
              BSP_SD_WriteBlocks((uint32_t *)buf, blk_addr, blk_len, 1000);

              /* Wait until SD card is ready to use for new operation */
              while(BSP_SD_GetCardState() != SD_TRANSFER_OK)
              {
                if (timeout-- == 0)
                {
                  return ret;
                }
              }
              ret = 0;
            }
        break;
    }

  return ret;
}

/**
  * @brief  Returns the Max Supported LUNs.
  * @param  None
  * @retval Lun(s) number
  */
int8_t STORAGE_GetMaxLun(void)
{
  return(STORAGE_LUN_NBR - 1);
}


