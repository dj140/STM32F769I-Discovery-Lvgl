/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
#include "stm32f769i_discovery_sd.h"
#include "stm32f769i_discovery_qspi.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* use the default SD timout as defined in the platform BSP driver*/
#if defined(SDMMC_DATATIMEOUT)
#define SD_TIMEOUT SDMMC_DATATIMEOUT
#elif defined(SD_DATATIMEOUT)
#define SD_TIMEOUT SD_DATATIMEOUT
#else
#define SD_TIMEOUT 30 * 1000
#endif

#define SD_DEFAULT_BLOCK_SIZE 512
#define SPI_FLASH_SECTOR_SIZE   4*1024
#define SPI_FLASH_SECTOR_COUNT  1024 * 16        /* 25Q128,最后7424KB字节给FATFS占用 */
#define SPI_FLASH_BLOCK_SIZE    16               /* 每个BLOCK有8个扇区 */

/* Definitions of physical drive number for each drive */
#define DEV_MMC  0	/* Example: Map MMC/SD card to physical drive 0 */
#define DEV_RAM  1	/* Example: Map Ramdisk to physical drive 1 */
#define DEV_USB  2	/* Example: Map USB MSD to physical drive 2 */

static volatile DSTATUS Stat = STA_NOINIT;
static DSTATUS SD_CheckStatus();

/* Private functions ---------------------------------------------------------*/
static DSTATUS SD_CheckStatus()
{
  Stat = STA_NOINIT;

  if(BSP_SD_GetCardState() == MSD_OK)
  {
    Stat &= ~STA_NOINIT;
  }

  return Stat;
}

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
  BYTE pdrv /* Physical drive nmuber to identify the drive */
)
{
  DSTATUS stat;
  int result;

  switch (pdrv) {
  case DEV_RAM :
        stat &= ~STA_NOINIT;

    // translate the reslut code here

    return stat;

  case DEV_MMC :
    
        stat &= ~STA_NOINIT;

//result = BSP_SD_GetCardState();

// translate the reslut code here

return stat;

case DEV_USB :
//result = USB_disk_status();

// translate the reslut code here

    return stat;
  }
  return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
  BYTE pdrv     /* Physical drive nmuber to identify the drive */
)
{
  DSTATUS stat;
  int result;

  switch (pdrv) {
  case DEV_RAM :
//result = RAM_disk_initialize();
//          result = BSP_QSPI_Init();
        stat &= ~STA_NOINIT;
    return stat;

  case DEV_MMC :
      if(BSP_SD_Init() == MSD_OK)
      {
        stat &= ~STA_NOINIT;
      }
      else {
        stat = STA_NOINIT;
      }
    // translate the reslut code here
    return stat;

  case DEV_USB :
    //result = USB_disk_initialize();
    // translate the reslut code here
    return stat;
  }
  return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
  BYTE pdrv,    /* Physical drive nmuber to identify the drive */
  BYTE *buff,   /* Data buffer to store read data */
  LBA_t sector, /* Start sector in LBA */
  UINT count    /* Number of sectors to read */
)
{
  DRESULT res;
  int result;

  switch (pdrv) {
  case DEV_RAM :
    // translate the arguments here
    for (; count > 0; count--)
    {
        if(BSP_QSPI_Read(buff, sector * SPI_FLASH_SECTOR_SIZE, SPI_FLASH_SECTOR_SIZE) == MSD_OK)
        {
          sector++;
          buff += SPI_FLASH_SECTOR_SIZE;
        }
            res = RES_OK;
    }
    // translate the reslut code here
    return res;

  case DEV_MMC :
    // translate the arguments here
    if(BSP_SD_ReadBlocks((uint32_t*)buff,
                         (uint32_t) (sector),
                         count, SD_TIMEOUT) == MSD_OK)
    {
      /* wait until the read operation is finished */
      while(BSP_SD_GetCardState()!= MSD_OK)
      {
      }
      res = RES_OK;
    }
  //result = BSP_SD_ReadBlocks((uint32_t*)buff, (uint32_t)sector, count, SD_TIMEOUT);
  // translate the reslut code here

    return res;

  case DEV_USB :
    // translate the arguments here
    //result = USB_disk_read(buff, sector, count);
    // translate the reslut code here
    return res;
  }

  return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
  BYTE pdrv,      /* Physical drive nmuber to identify the drive */
  const BYTE *buff,	/* Data to be written */
  LBA_t sector,   /* Start sector in LBA */
  UINT count      /* Number of sectors to write */
)
{
  DRESULT res;
  int result;

  switch (pdrv) {
  case DEV_RAM :
    // translate the arguments here
    for (; count > 0; count--)
    {
        BSP_QSPI_Write((uint8_t *)buff, sector * SPI_FLASH_SECTOR_SIZE, SPI_FLASH_SECTOR_SIZE);
        sector++;
        buff += SPI_FLASH_SECTOR_SIZE;
    }
  // translate the reslut code here
    return 0;

  case DEV_MMC :
    // translate the arguments here
    if(BSP_SD_WriteBlocks((uint32_t*)buff,
                          (uint32_t)(sector),
                          count, SD_TIMEOUT) == MSD_OK)
    {
    /* wait until the Write operation is finished */
      while(BSP_SD_GetCardState() != MSD_OK)
      {
      }
      res = RES_OK;
    }
    // translate the reslut code here
    return res;

  case DEV_USB :
    // translate the arguments here
    //result = USB_disk_write(buff, sector, count);
    // translate the reslut code here

    return res;
  }

  return RES_PARERR;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
  BYTE pdrv,		/* Physical drive nmuber (0..) */
  BYTE cmd,		/* Control code */
  void *buff		/* Buffer to send/receive control data */
)
{
  DRESULT res;
  int result;
  BSP_SD_CardInfo CardInfo;

  switch (pdrv) {
  case DEV_RAM :
    switch (cmd)
    {
        case CTRL_SYNC:
            res = RES_OK;
            break;

        case GET_SECTOR_SIZE:
            *(WORD *)buff = SPI_FLASH_SECTOR_SIZE;
            res = RES_OK;
            break;

        case GET_BLOCK_SIZE:
            *(WORD *)buff = SPI_FLASH_BLOCK_SIZE;
            res = RES_OK;
            break;

        case GET_SECTOR_COUNT:
            *(DWORD *)buff = SPI_FLASH_SECTOR_COUNT;
            res = RES_OK;
            break;

        default:
            res = RES_PARERR;
            break;
    }
    return res;

  case DEV_MMC :

    // Process of the command for the MMC/SD card
  switch (cmd)
  {
  /* Make sure that no pending write process */
  case CTRL_SYNC :
    res = RES_OK;
    break;

  /* Get number of sectors on the disk (DWORD) */
  case GET_SECTOR_COUNT :
    BSP_SD_GetCardInfo(&CardInfo);
    *(DWORD*)buff = CardInfo.LogBlockNbr;
    res = RES_OK;
    break;

  /* Get R/W sector size (WORD) */
  case GET_SECTOR_SIZE :
    BSP_SD_GetCardInfo(&CardInfo);
    *(WORD*)buff = CardInfo.LogBlockSize;
    res = RES_OK;
    break;

  /* Get erase block size in unit of sector (DWORD) */
  case GET_BLOCK_SIZE :
    BSP_SD_GetCardInfo(&CardInfo);
    *(DWORD*)buff = CardInfo.LogBlockSize / SD_DEFAULT_BLOCK_SIZE;
  res = RES_OK;
    break;

  default:
    res = RES_PARERR;
  }
    return res;

  case DEV_USB :

    // Process of the command the USB drive

    return res;
  }

  return RES_PARERR;
}

