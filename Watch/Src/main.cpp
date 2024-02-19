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

USBD_HandleTypeDef USBD_Device;
FATFS fs;           /* FatFs�ļ�ϵͳ���� */
FIL fnew;           /* �ļ����� */
FRESULT res_flash;              /* �ļ�������� */
BYTE work[FF_MAX_SS]; /* Work area (larger is better for processing time) */
    
//UINT fnum;                        /* �ļ��ɹ���д���� */
//BYTE ReadBuffer[1024]= {0};       /* �������� */
//BYTE WriteBuffer[] =              /*  д������*/
//        "�½��ļ�ϵͳ�����ļ�\r\n";
static void MPU_Config(void);
static void SystemClock_Config(void);
static void CPU_CACHE_Enable(void);
static void fs_init(void);


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
    /* ��ʼ�����Դ��ڣ�һ��Ϊ����1 */
  DEBUG_USART_Config();	
  printf("****** usart enable ******\r\n");
//  
  /* Init Device Library */
  USBD_Init(&USBD_Device, &MSC_Desc, 0);
  
  /* Add Supported Class */
  USBD_RegisterClass(&USBD_Device, USBD_MSC_CLASS);
  
  /* Add Storage callbacks for MSC Class */
  USBD_MSC_RegisterStorage(&USBD_Device, &USBD_DISK_fops);
  
  /* Start Device Process */
  USBD_Start(&USBD_Device);
  
  fs_init();
  lv_init();
//  lv_fs_file_t f;
//  lv_fs_res_t res = lv_fs_open(&f, "0:sdcard/boot_anim/background.png", LV_FS_MODE_RD);
//  printf("res: %d\n", res);
  tft_init();
  touchpad_init();
  App_Init();

//  lv_demo_benchmark();
//  lv_demo_music();

  while(1) {
      lv_task_handler();
      HAL_Delay(5);
    }
}

static void fs_init(void)
{

  res_flash = f_mount(&fs,"0:",1);
  if (res_flash == FR_NO_FILESYSTEM) {
    printf("��SD����û���ļ�ϵͳ���������и�ʽ��...\r\n");
    /* ��ʽ�� */
    res_flash=f_mkfs("0:",0,work, sizeof work);

    if (res_flash == FR_OK) {
        printf("��SD���ѳɹ���ʽ���ļ�ϵͳ��\r\n");
        /* ��ʽ������ȡ������ */
        res_flash = f_mount(NULL,"0:",1);
        /* ���¹��� */
        res_flash = f_mount(&fs,"0:",1);
    } else {
        printf("������ʽ��ʧ�ܡ�����\r\n");
    }
  } else if (res_flash!=FR_OK) {
      printf("����SD�������ļ�ϵͳʧ�ܡ�(%d)\r\n",res_flash);
      printf("��������ԭ��SD����ʼ�����ɹ���\r\n");
//      while (1);
  } else {
      printf("���ļ�ϵͳ���سɹ������Խ��ж�д����\r\n");
  }
//    printf("\r\n****** ���������ļ�д�����... ******\r\n");
//    res_flash=f_open(&fnew,"0:FatFs��д�����ļ�.txt",FA_CREATE_ALWAYS|FA_WRITE);
//    if ( res_flash == FR_OK ) {
//        printf("����/����FatFs��д�����ļ�.txt�ļ��ɹ������ļ�д�����ݡ�\r\n");
//        /* ��ָ���洢������д�뵽�ļ��� */
//        res_flash=f_write(&fnew,WriteBuffer,sizeof(WriteBuffer),&fnum);
//        if (res_flash==FR_OK) {
//            printf("���ļ�д��ɹ���д���ֽ����ݣ�%d\n",fnum);
//            printf("�����ļ�д�������Ϊ��\r\n%s\r\n",WriteBuffer);
//        } else {
//            printf("�����ļ�д��ʧ�ܣ�(%d)\n",res_flash);
//        }
//        /* ���ٶ�д���ر��ļ� */
//        f_close(&fnew);
//    } else {
////        LED_RED;
//        printf("������/�����ļ�ʧ�ܡ�\r\n");
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
