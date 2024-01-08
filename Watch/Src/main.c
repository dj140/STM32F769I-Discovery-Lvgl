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

//#include <mooncake.h>
USBD_HandleTypeDef USBD_Device;
FATFS fsA;						/* FatFs?l??????? */
FRESULT res_flash;              /* ?l???????? */

static void MPU_Config(void);
static void SystemClock_Config(void);
static void CPU_CACHE_Enable(void);

//static   MOONCAKE::Mooncake mooncake_ui;

//int btn_value = 0;

//class AppTest : public MOONCAKE::APP_BASE {
//private:

//  lv_obj_t* screen;
//  int bbb1;
//  int bbb2;

//  uint32_t ticks;

//  static void event_handler(lv_event_t * e)
//  {
//    lv_event_code_t code = lv_event_get_code(e);

//    if(code == LV_EVENT_CLICKED) {

//      btn_value = *(int*)lv_event_get_user_data(e);

//    }
//  }
//  
//public:
//  AppTest(const char* name, void* icon = nullptr) {
//    setAppName(name);
//    setAppIcon(icon);
//  }

//  void onSetup() {
//    
//  }

//  /* Life cycle */
//  void onCreate() {
//    //DEBUG_PRINT("[%s] onCreate\n", getAppName().c_str());
//    setAllowBgRunning(false);
//  }
//  void onResume() {
//    //DEBUG_PRINT("[%s] onResume\n", getAppName().c_str());
//    btn_value = 0;


//    screen = lv_obj_create(NULL);
//    lv_scr_load_anim(screen, LV_SCR_LOAD_ANIM_MOVE_TOP, 50, 0, false);


//    lv_obj_t * label;

//    lv_obj_t * btn1 = lv_btn_create(screen);
//    bbb1 = 1;
//    lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, (void*)&bbb1);
//    lv_obj_align(btn1, LV_ALIGN_CENTER, 0, -40);

//    label = lv_label_create(btn1);
//    // lv_obj_add_flag(btn1, LV_OBJ_FLAG_CHECKABLE);
//    lv_obj_add_state(btn1, LV_STATE_CHECKED);
//    lv_label_set_text(label, "Quit App");
//    lv_obj_center(label);



//    lv_obj_t * btn2 = lv_btn_create(screen);
//    bbb2 = 2;
//    lv_obj_add_event_cb(btn2, event_handler, LV_EVENT_ALL, (void*)&bbb2);
//    lv_obj_align(btn2, LV_ALIGN_CENTER, 0, 40);

//    label = lv_label_create(btn2);
//    lv_label_set_text(label, "Run background");
//    lv_obj_center(label);

//  }
//  void onRunning() {
//    // DEBUG_PRINT("[%s] onRunning\n", getAppName().c_str());

//    if ((lv_tick_get() - ticks) > 1000) {
//      //DEBUG_PRINT("[%s] onRunning\n", getAppName().c_str());
//      ticks = lv_tick_get();
//    }
//    // DEBUG_PRINT("%d\n", btn_value);
//    if (btn_value == 1) {
//      setAllowBgRunning(false);
//      destroyApp();
//    }
//    else if (btn_value == 2) {
//      setAllowBgRunning(true);
//      closeApp();
//    }
//  }
//  void onRunningBG() {
//    // DEBUG_PRINT("[%s] onRunningBG\n", getAppName().c_str());

//    if ((lv_tick_get() - ticks) > 1000) {
//      //DEBUG_PRINT("[%s] onRunningBG\n", getAppName().c_str());
//      ticks = lv_tick_get();
//    }
//  }
//  void onPause() {
//  //            DEBUG_PRINT("[%s] onPause\n", getAppName().c_str());
//  }
//  void onDestroy() {
//  //            DEBUG_PRINT("[%s] onDestroy\n", getAppName().c_str());
//  }
//  
//};


int main(void) {
  
  /* Configure the MPU attributes */
//  MPU_Config();

  /* Enable the CPU Cache */
  CPU_CACHE_Enable();

  HAL_Init();

  SystemClock_Config();
    /* ??'??????????h???????1 */
  DEBUG_USART_Config();	
  printf("****** usart enable ******\r\n");
  	res_flash = f_mount(&fsA,"0:",1);
  if(res_flash!=FR_OK)
  {
    printf("??????Flash?????l???????(%d)\r\n",res_flash);
    printf("???????????SPI Flash??'?????????\r\n");
  }
  else
  {
    printf("okkkkkkk\r\n");    
  }
  

  lv_init();
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