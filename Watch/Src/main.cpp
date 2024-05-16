/**
******************************************************************************
* @file    main.c
* @author  Ac6
* @version V1.0
* @date    01-December-2013
* @brief   Default main function.
******************************************************************************
*/

#include "main.h"
#include "App.h"
#include "Common/HAL/HAL.h"


USBD_HandleTypeDef USBD_Device;
FATFS fs[FF_VOLUMES];           /* FatFs文件系统对象 */
FIL fnew;           /* 文件对象 */
FRESULT res_flash;              /* 文件操作结果 */
BYTE work[FF_MAX_SS]; /* Work area (larger is better for processing time) */
    
UINT fnum;                        /* 文件成功读写数量 */
BYTE ReadBuffer[1024]= {0};       /* 读缓冲区 */
BYTE WriteBuffer[] =              /*  写缓冲区*/
        "新建文件系统测试文件\r\n";
static void MPU_Config(void);
static void SystemClock_Config(void);
static void CPU_CACHE_Enable(void);
static void fs_init(void);

//LV_IMG_DECLARE(img_src_bg_digital_392x392);
//#include "MjpegClass.h"
//static MjpegClass mjpeg;
//#define MJPEG_BUFFER_SIZE (390 * 450 * 2) // memory for a single JPEG frame
//extern DMA_HandleTypeDef     DmaHandle;
//static uint16_t * my_fb = (uint16_t *)((uint32_t)0xC0000000);

/* variables */
//static int total_frames = 0;
//static unsigned long total_read_video = 0;
//static unsigned long total_decode_video = 0;
//static unsigned long total_show_video = 0;
//static unsigned long start_ms, curr_ms;

// pixel drawing callback
//static int jpegDrawCallback(JPEGDRAW *pDraw)
//{
//  printf("Draw pos = %d,%d. size = %d x %d\n", pDraw->x, pDraw->y, pDraw->iWidth, pDraw->iHeight);
//  unsigned long start = millis();
////  gfx->draw16bitBeRGBBitmap(pDraw->x, pDraw->y, pDraw->pPixels, pDraw->iWidth, pDraw->iHeight);
//  HAL_DMA_Start_IT(&DmaHandle,(uint32_t)pDraw->pPixels, (uint32_t)&my_fb[pDraw->y * TFT_HOR_RES + pDraw->x],pDraw->iWidth * pDraw->iHeight * 2);
//  total_show_video += millis() - start;
//  return 1;
//}

int main(void) {
  
  /* Configure the MPU attributes */
//  MPU_Config();

  /* Enable the CPU Cache */
  CPU_CACHE_Enable();

  /* STM32F7xx HAL library initialization:
  - Configure the Flash prefetch
  - Systick timer is configured by default as source of time base, but user
  can eventually implement his proper time base source (a general purpose
  timer for example or other time source), keeping in mind that Time base
  duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and
  handled in milliseconds basis.
  - Set NVIC Group Priority to 4
  - Low Level Initialization
  */
  HAL_Init();

  SystemClock_Config();

  DEBUG_USART_Config();
  printf("****** usart enable ******\r\n"); 
  int status = BSP_QSPI_Init();
  printf("flash init status = %d\n", status);

  fs_init();
  lv_init();
//  lv_fs_file_t f;
//  lv_fs_res_t res = lv_fs_open(&f, "0:sdcard/boot_anim/background.png", LV_FS_MODE_RD);
//  printf("res: %d\n", res);
  tft_init();
//  touchpad_init();
  HAL::HAL_Init();
  App_Init();
  
//  res_flash = f_open(&fnew,"0:earth.mjpeg",FA_READ);
//  printf("res: %d\n", res_flash);
//  uint8_t *mjpeg_buf = (uint8_t *)malloc(MJPEG_BUFFER_SIZE);
//  start_ms = millis();
//  curr_ms = millis();
//  mjpeg.setup(
//  fnew, mjpeg_buf, jpegDrawCallback, true /* useBigEndian */,
//  0 /* x */, 0 /* y */, 390 /* widthLimit */, 450 /* heightLimit */);

//  while ( !res_flash && mjpeg.readMjpegBuf())
//  {
//    // Read video
//    total_read_video += millis() - curr_ms;
//    curr_ms = millis();

//    // Play video
//    mjpeg.drawJpg();
//    total_decode_video += millis() - curr_ms;

//    curr_ms = millis();
//    total_frames++;
//  }

  /* Init Device Library */
//  USBD_Init(&USBD_Device, &MSC_Desc, 0);
//  
//  /* Add Supported Class */
//  USBD_RegisterClass(&USBD_Device, USBD_MSC_CLASS);
//  
//  /* Add Storage callbacks for MSC Class */
//  USBD_MSC_RegisterStorage(&USBD_Device, &USBD_DISK_fops);
//  
//  /* Start Device Process */
//  USBD_Start(&USBD_Device);
//  lv_demo_benchmark();
//  lv_demo_music();
//    lv_obj_t * img1 = lv_img_create(lv_scr_act());
//    lv_img_set_src(img1, &img_src_bg_digital_392x392);
//    lv_obj_align(img1, LV_ALIGN_CENTER, 0, 0);
    
  while(1) {
      lv_task_handler();
      HAL_Delay(1);
    }
}

static void fs_init(void)
{
  f_mount(&fs[0],"0:",1);
  res_flash = f_mount(&fs[1],"1:",1);
  if (res_flash == FR_NO_FILESYSTEM) {
    printf("》SD卡还没有文件系统，即将进行格式化...\r\n");
    /* 格式化 */
    res_flash=f_mkfs("1:",0,work, sizeof work);
    if (res_flash == FR_OK) {
        printf("》SD卡已成功格式化文件系统。\r\n");
        /* 格式化后，先取消挂载 */
        res_flash = f_mount(NULL,"1:",1);
        /* 重新挂载 */
        res_flash = f_mount(&fs[1],"1:",1);
        printf("flash init (%d)\r\n",res_flash);
    } else {
        printf("《《格式化失败。》》\r\n");
    }
  } else if (res_flash!=FR_OK) {
      printf("！！SD卡挂载文件系统失败。(%d)\r\n",res_flash);
      printf("！！可能原因：SD卡初始化不成功。\r\n");
//      while (1);
  } else {
      printf("》文件系统挂载成功，可以进行读写测试\r\n");
  }
//    printf("\r\n****** 即将进行文件写入测试... ******\r\n");
//    res_flash=f_open(&fnew,"1:FatFs读写测试文件.txt",FA_CREATE_ALWAYS|FA_WRITE);
//    if ( res_flash == FR_OK ) {
//        printf("》打开/创建FatFs读写测试文件.txt文件成功，向文件写入数据。\r\n");
//        /* 将指定存储区内容写入到文件内 */
//        res_flash=f_write(&fnew,WriteBuffer,sizeof(WriteBuffer),&fnum);
//        if (res_flash==FR_OK) {
//            printf("》文件写入成功，写入字节数据：%d\n",fnum);
//            printf("》向文件写入的数据为：\r\n%s\r\n",WriteBuffer);
//        } else {
//            printf("！！文件写入失败：(%d)\n",res_flash);
//        }
//        /* 不再读写，关闭文件 */
//        f_close(&fnew);
//    } else {
////        LED_RED;
//        printf("！！打开/创建文件失败。\r\n");
//    }
}
//#pragma push
//#pragma O0
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_StatusTypeDef ret = HAL_OK;

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 400;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  RCC_OscInitStruct.PLL.PLLR = 7;

  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }

  /* Activate the OverDrive to reach the 216 MHz Frequency */
  ret = HAL_PWREx_EnableOverDrive();
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
}
//#pragma pop

/**
  * @brief  Toggle LEDs to show user input state.   
  * @param  None
  * @retval None
  */
void Toggle_Leds(void)
{
  static uint32_t ticks;
  
  if(ticks++ == 100)
  {
    BSP_LED_Toggle(LED1);
    BSP_LED_Toggle(LED2);
    ticks = 0;
  }
}

/**
  * @brief  Configure the MPU attributes
  * @param  None
  * @retval None
  */
static void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct;

  /* Disable the MPU */
  HAL_MPU_Disable();

  /* Configure the MPU as Strongly ordered for not defined regions */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0x00;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Enable the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}


/**
* @brief  CPU L1-Cache enable.
* @param  None
* @retval None
*/
static void CPU_CACHE_Enable(void)
{
  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}
