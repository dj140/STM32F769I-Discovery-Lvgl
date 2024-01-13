#include "TemplateView.h"
#include <stdarg.h>
#include <stdio.h>
#include "ff.h"

using namespace Page;
#define MAX_BMP_FILES     25
#define MAX_BMP_FILE_NAME 11
uint8_t  ubNumberOfFiles = 0;
    uint32_t counter = 0;
uint32_t uwBmplen = 0;
/* Internal Buffer defined in SDRAM memory */
uint8_t *uwInternalBuffer;
FILINFO fno;
DIR dir;
FIL F;
char* pDirectoryFiles[MAX_BMP_FILES];

void TemplateView::Create(lv_obj_t* root)
{
//    lv_obj_t* label = lv_label_create(root);
//    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 20);
//    lv_label_set_text(label, "");
//    ui.labelTitle = label;

//    label = lv_label_create(root);
//    lv_label_set_text(label, "");
//    lv_obj_center(label);
//    ui.labelTick = label;
    lv_obj_t* cont = lv_obj_create(root);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 397, 397);
    lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_clear_flag(cont, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_set_style_bg_color(cont, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cont, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* image = lv_img_create(cont);
    /* Main infinite loop */
 


    counter = 0;
    uint8_t str[30];
    for (counter = 0; counter < MAX_BMP_FILES; counter++)
    {
              printf("11111");
        lv_img_set_src(image, "0:sdcard/boot_anim/background.bin");
      lv_obj_fade_in(image, 1000, 0);
              lv_img_set_src(image, "0:sdcard/boot_anim/shm_logo.bin");
//      pDirectoryFiles[counter] = new char[MAX_BMP_FILE_NAME];
//      if(pDirectoryFiles[counter] == NULL)
//      {
//        /* Set the Text Color */
////        BSP_LCD_SetTextColor(LCD_COLOR_RED);
//        printf("Cannot allocate memory");
////        BSP_LCD_DisplayStringAtLine(8, (uint8_t*)"  Cannot allocate memory ");
////        while(1) { ; }
//      }
    }

    /* Get the BMP file names on root directory */
    ubNumberOfFiles = Storage_GetDirectoryBitmapFiles("/Media", pDirectoryFiles);
      printf("Media/%s", pDirectoryFiles[counter]);

    if (ubNumberOfFiles == 0)
    {
      for (counter = 0; counter < MAX_BMP_FILES; counter++)
      {
        delete(pDirectoryFiles[counter]);
      }
        printf("no bin image");

    }
    while ((counter) < ubNumberOfFiles)
    {
      /* Step1 : Display on Foreground layer -------------------------------*/
      /* Format the string */
      sprintf ((char*)str, "Media/%-11.11s", pDirectoryFiles[counter]);
      printf("Media/%s", pDirectoryFiles[counter]);
        /* Format the string */
//        sprintf ((char*)str, "Media/%-11.11s", pDirectoryFiles[counter]);

        /* Set LCD foreground Layer */
//        BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER_FOREGROUND);

        /* Open a file and copy its content to an internal buffer */
//        Storage_OpenReadFile(uwInternalBuffer, (const char*)str);
        lv_img_set_src(image, (const char*)str);
        /* Write bmp file on LCD frame buffer */
//        BSP_LCD_DrawBitmap(0, 0, uwInternalBuffer);

        /* Jump to the next image */
        counter++;
    }
}
/**
  * @brief  List up to 25 file on the root directory with extension .BMP
  * @param  None
  * @retval The number of the found files
  */
uint32_t TemplateView::Storage_GetDirectoryBitmapFiles (const char* DirName, char* Files[])
{
  FRESULT res;
  uint32_t index = 0;

//  /* Open filesystem */
//  if(f_mount(&fs, (TCHAR const*)"",0) != FR_OK)
//  {
//    return 0;
//  }

  /* Start to search for wave files */
  res = f_findfirst(&dir, &fno, DirName, "*.bin");

  /* Repeat while an item is found */
  while (fno.fname[0])
  {
    if(res == FR_OK)
    {
      if(index < MAX_BMP_FILES)
      {
        sprintf (Files[index++], "%s", fno.fname);
      }
      /* Search for next item */
      res = f_findnext(&dir, &fno);
    }
    else
    {
      index = 0;
      break;
    }
  }

  f_closedir(&dir);

  return index;
}
void TemplateView::Get_image_name()
{
  /*##-2- Link the SD Card disk I/O driver ###################################*/
    /*##-3- Initialize the Directory Files pointers (heap) ###################*/


}

