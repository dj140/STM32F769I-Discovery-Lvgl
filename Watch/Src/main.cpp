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
#include <mooncake.h>

USBD_HandleTypeDef USBD_Device;


static void MPU_Config(void);
static void SystemClock_Config(void);
static void CPU_CACHE_Enable(void);

static   MOONCAKE::Mooncake mooncake_ui;

int btn_value = 0;

class AppTest : public MOONCAKE::APP_BASE {
private:

  lv_obj_t* screen;
  int bbb1;
  int bbb2;

  uint32_t ticks;

  static void event_handler(lv_event_t * e)
  {
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {

      btn_value = *(int*)lv_event_get_user_data(e);

    }
  }
  
public:
  AppTest(const char* name, void* icon = nullptr) {
    setAppName(name);
    setAppIcon(icon);
  }

  void onSetup() {
    
  }

  /* Life cycle */
  void onCreate() {
    //DEBUG_PRINT("[%s] onCreate\n", getAppName().c_str());
    setAllowBgRunning(false);
  }
  void onResume() {
    //DEBUG_PRINT("[%s] onResume\n", getAppName().c_str());
    btn_value = 0;


    screen = lv_obj_create(NULL);
    lv_scr_load_anim(screen, LV_SCR_LOAD_ANIM_MOVE_TOP, 50, 0, false);


    lv_obj_t * label;

    lv_obj_t * btn1 = lv_btn_create(screen);
    bbb1 = 1;
    lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, (void*)&bbb1);
    lv_obj_align(btn1, LV_ALIGN_CENTER, 0, -40);

    label = lv_label_create(btn1);
    // lv_obj_add_flag(btn1, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_add_state(btn1, LV_STATE_CHECKED);
    lv_label_set_text(label, "Quit App");
    lv_obj_center(label);



    lv_obj_t * btn2 = lv_btn_create(screen);
    bbb2 = 2;
    lv_obj_add_event_cb(btn2, event_handler, LV_EVENT_ALL, (void*)&bbb2);
    lv_obj_align(btn2, LV_ALIGN_CENTER, 0, 40);

    label = lv_label_create(btn2);
    lv_label_set_text(label, "Run background");
    lv_obj_center(label);

  }
  void onRunning() {
    // DEBUG_PRINT("[%s] onRunning\n", getAppName().c_str());

    if ((lv_tick_get() - ticks) > 1000) {
      //DEBUG_PRINT("[%s] onRunning\n", getAppName().c_str());
      ticks = lv_tick_get();
    }
    // DEBUG_PRINT("%d\n", btn_value);
    if (btn_value == 1) {
      setAllowBgRunning(false);
      destroyApp();
    }
    else if (btn_value == 2) {
      setAllowBgRunning(true);
      closeApp();
    }
  }
  void onRunningBG() {
    // DEBUG_PRINT("[%s] onRunningBG\n", getAppName().c_str());

    if ((lv_tick_get() - ticks) > 1000) {
      //DEBUG_PRINT("[%s] onRunningBG\n", getAppName().c_str());
      ticks = lv_tick_get();
    }
  }
  void onPause() {
  //            DEBUG_PRINT("[%s] onPause\n", getAppName().c_str());
  }
  void onDestroy() {
  //            DEBUG_PRINT("[%s] onDestroy\n", getAppName().c_str());
  }
  
};
FATFS fsA;						/* FatFs文件系统对象 */
FIL fnew;						/* 文件对象 */
FRESULT res_flash;              /* 文件操作结果 */
UINT fnum;            			/* 文件成功读写数量 */
char fpath[100];                /* 保存当前扫描路径 */
char readbuffer[512];           /*  */
//extern FATFS flash_fs;
/* FatFs多项功能测试 */
DIR dirA;
FATFS *pfs;
DWORD fre_clust, fre_sect, tot_sect;
static FRESULT miscellaneous(void)
{
  printf("\n*************** 设备信息获取 ***************\r\n");
  /* 获取设备信息和空簇大小 */
  res_flash = f_getfree("A:", &fre_clust, &pfs);

  /* 计算得到总的扇区个数和空扇区个数 */
  tot_sect = (pfs->n_fatent - 2) * pfs->csize;
  fre_sect = fre_clust * pfs->csize;

  /* 打印信息(4096 字节/扇区) */
  printf("》设备总空间：%10lu KB。\n》可用空间：  %10lu KB。\n", tot_sect *4, fre_sect *4);
  
  printf("\n******** 文件定位和格式化写入功能测试 ********\r\n");
  res_flash = f_open(&fnew, "A:FatFs.txt",
                            FA_OPEN_ALWAYS|FA_WRITE|FA_READ );
	if ( res_flash == FR_OK )
	{
    /*  文件定位 */
    res_flash = f_lseek(&fnew,f_size(&fnew));
    if (res_flash == FR_OK)
    {
      /* 格式化写入，参数格式类似printf函数 */
      f_printf(&fnew,"\n在原来文件新添加一行内容\n");
      f_printf(&fnew,"》设备总空间：%10lu KB。\n》可用空间：  %10lu KB。\n", tot_sect *4, fre_sect *4);
      /*  文件定位到文件起始位置 */
      res_flash = f_lseek(&fnew,0);
      /* 读取文件所有内容到缓存区 */
      res_flash = f_read(&fnew,readbuffer,f_size(&fnew),&fnum);
      if(res_flash == FR_OK)
      {
        printf("》文件内容：\n%s\n",readbuffer);
      }
    }
    f_close(&fnew);    
    
    printf("\n********** 目录创建和重命名功能测试 **********\r\n");
    /* 尝试打开目录 */
    res_flash=f_opendir(&dirA,"A:TestDir");
    if(res_flash!=FR_OK)
    {
      /* 打开目录失败，就创建目录 */
      res_flash=f_mkdir("A:TestDir");
    }
    else
    {
      /* 如果目录已经存在，关闭它 */
      res_flash=f_closedir(&dirA);
      /* 删除文件 */
      f_unlink("A:TestDir/testdir.txt");
    }
    if(res_flash==FR_OK)
    {
      /* 重命名并移动文件 */
      res_flash=f_rename("A:FatFsa.txt","1:TestDir/testdir.txt");      
    } 
	}
  else
  {
    printf("!! 打开文件失败：%d\n",res_flash);
    printf("!! 或许需要再次运行“FatFs移植与读写测试”工程\n");
  }
  return res_flash;
}

/**
  * 文件信息获取
  */
static FRESULT file_check(void)
{
  FILINFO fno;
  
  /* 获取文件信息 */
  res_flash=f_stat("A:TestDir/testdir.txt",&fno);
  if(res_flash==FR_OK)
  {
    printf("“testdir.txt”文件信息：\n");
    printf("》文件大小: %ld(字节)\n", fno.fsize);
    printf("》时间戳: %u/%02u/%02u, %02u:%02u\n",
           (fno.fdate >> 9) + 1980, fno.fdate >> 5 & 15, fno.fdate & 31,fno.ftime >> 11, fno.ftime >> 5 & 63);
    printf("》属性: %c%c%c%c%c\n\n",
           (fno.fattrib & AM_DIR) ? 'D' : '-',      // 是一个目录
           (fno.fattrib & AM_RDO) ? 'R' : '-',      // 只读文件
           (fno.fattrib & AM_HID) ? 'H' : '-',      // 隐藏文件
           (fno.fattrib & AM_SYS) ? 'S' : '-',      // 系统文件
           (fno.fattrib & AM_ARC) ? 'A' : '-');     // 档案文件
  }
  return res_flash;
}

/**
  * @brief  scan_files 递归扫描FatFs内的文件
  * @param  path:初始扫描路径
  * @retval result:文件系统的返回值
  */
static FRESULT scan_files (char* path) 
{ 
  FRESULT res; 		//部分在递归过程被修改的变量，不用全局变量	
  FILINFO fno; 
  DIR dirA; 
  int i;            
  char *fn;        // 文件名	
	
//#if _USE_LFN 
//  /* 长文件名支持 */
//  /* 简体中文需要2个字节保存一个“字”*/
//  static char lfn[_MAX_LFN*2 + 1]; 	
//  fno.lfname = lfn; 
//  fno.lfsize = sizeof(lfn); 
//#endif 
  //打开目录
  res = f_opendir(&dirA, path); 
  if (res == FR_OK) 
	{ 
    i = strlen(path); 
    for (;;) 
		{ 
      //读取目录下的内容，再读会自动读下一个文件
      res = f_readdir(&dirA, &fno); 								
      //为空时表示所有项目读取完毕，跳出
      if (res != FR_OK || fno.fname[0] == 0) break; 	
#if _USE_LFN 
//      fn = *fno.lfname ? fno.lfname : fno.fname; 
            fn = fno.fname; 

#else 
      fn = fno.fname; 
#endif 
      //点表示当前目录，跳过			
      if (*fn == '.') continue; 	
      //目录，递归读取      
      if (fno.fattrib & AM_DIR)         
			{ 			
        //合成完整目录名        
        sprintf(&path[i], "/%s", fn); 		
        //递归遍历         
        res = scan_files(path);	
        path[i] = 0;         
        //打开失败，跳出循环        
        if (res != FR_OK) 
					break; 
      } 
			else 
			{ 
				printf("%s/%s\r\n", path, fn);								//输出文件名	
        /* 可以在这里提取特定格式的文件路径 */        
      }//else
    } //for
  } 
  return res; 
}
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
    /* 初始化调试串口，一般为串口1 */
  DEBUG_USART_Config();	
  printf("****** usart enable ******\r\n");
  	res_flash = f_mount(&fsA,"A:",1);
  if(res_flash!=FR_OK)
  {
    printf("！！外部Flash挂载文件系统失败。(%d)\r\n",res_flash);
    printf("！！可能原因：SPI Flash初始化不成功。\r\n");
		while(1);
  }
  else
  {
    printf("》文件系统挂载成功，可以进行测试\r\n");    
  }
  
//  /* FatFs多项功能测试 */
//  res_flash = miscellaneous();

//  
//  printf("\n*************** 文件信息获取测试 **************\r\n");
//  res_flash = file_check();

//  
//  printf("***************** 文件扫描测试 ****************\r\n");
//  strcpy(fpath,"A:");
//  scan_files(fpath);

//  
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

  lv_init();
//  lv_fs_file_t f;
//  lv_fs_res_t res = lv_fs_open(&f, "A:/b.txt", LV_FS_MODE_RD);
//  printf("res: %d\n", res);
  tft_init();
  touchpad_init();

//  lv_demo_benchmark();
//  lv_demo_music();
  mooncake_ui.setDisplay(368, 448);
  mooncake_ui.init();
  mooncake_ui.installBuiltinApps();

  /* Install Apps */
  MOONCAKE::APP_BASE* app_ptr = nullptr;

  app_ptr = new AppTest("333", (void*)&ui_img_app_icon_hdpi_boxing_png);
  mooncake_ui.install(app_ptr);
  app_ptr = new AppTest("444", (void*)&ui_img_app_icon_hdpi_camera_png);
  mooncake_ui.install(app_ptr);
  // app_ptr = new AppTest("555", (void*)&ui_img_app_icon_hdpi_canvas_png);
  // mooncake_ui.install(app_ptr);
  app_ptr = new AppTest("111", (void*)&ui_img_app_icon_hdpi_badminton_png);
  mooncake_ui.install(app_ptr);
  app_ptr = new AppTest("222", (void*)&ui_img_app_icon_hdpi_birdhead_png);
  mooncake_ui.install(app_ptr);
  app_ptr = new AppTest("666", (void*)&ui_img_app_icon_hdpi_cheers_png);
  mooncake_ui.install(app_ptr);
  app_ptr = new AppTest("999", (void*)&ui_img_app_icon_hdpi_pingpong_png);
  mooncake_ui.install(app_ptr);
  app_ptr = new AppTest("1010", (void*)&ui_img_app_icon_hdpi_weather_png);
  mooncake_ui.install(app_ptr);
  app_ptr = new AppTest("777", (void*)&ui_img_app_icon_hdpi_location_png);
  mooncake_ui.install(app_ptr);
  app_ptr = new AppTest("888", (void*)&ui_img_app_icon_hdpi_music_png);
  mooncake_ui.install(app_ptr);

  while(1) {
      mooncake_ui.update();
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
