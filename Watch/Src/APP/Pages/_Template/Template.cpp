#include "Template.h"
#include "stdio.h"
#include "stm32f7xx_hal.h"

using namespace Page;
extern DSI_HandleTypeDef hdsi_discovery;

//char* imagepath[100];                /* 保存当前扫描路径 */
uint32_t counter = 0;
uint8_t  ubNumberOfFiles = 0;
uint8_t str[100];
#define MAX_BMP_FILES     50
#define MAX_BMP_FILE_NAME 100
char* pDirectoryFiles[MAX_BMP_FILES];
uint8_t num = 0;

Template::Template()
    : timer(nullptr)
{
}

Template::~Template()
{

}

void Template::onCustomAttrConfig()
{
    LV_LOG_USER("begin");
    SetCustomCacheEnable(true);
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 1000, lv_anim_path_bounce);
}

void Template::onViewLoad()
{
    printf("Template begin \n");
    View.Create(_root);
//    lv_label_set_text(View.ui.labelTitle, _Name);

    AttachEvent(_root);
    AttachEvent(View.ui.cont);
      for (counter = 0; counter < MAX_BMP_FILES; counter++)
    {

      pDirectoryFiles[counter] = new char[MAX_BMP_FILE_NAME];
      if(pDirectoryFiles[counter] == NULL)
      {

        printf("Cannot allocate memory \n");

      }
    }
    ubNumberOfFiles = View.Storage_GetDirectoryBitmapFiles("/Media", pDirectoryFiles);
    if (ubNumberOfFiles == 0)
    {
      for (counter = 0; counter < MAX_BMP_FILES; counter++)
      {
        free(pDirectoryFiles[counter]);
      }
    }
//    Model.TickSave = Model.GetData();
}

void Template::onViewDidLoad()
{
    LV_LOG_USER("begin");
}

void Template::onViewWillAppear()
{
    LV_LOG_USER("begin");

//    lv_obj_set_style_bg_color(_root, param.color, LV_PART_MAIN);
//    lv_obj_set_style_bg_opa(_root, LV_OPA_COVER, LV_PART_MAIN);
    timer = lv_timer_create(onTimerUpdate, 5500, this);


}

void Template::onViewDidAppear()
{
    LV_LOG_USER("begin");
//    lv_obj_del(View.ui.Spinner);

}

void Template::onViewWillDisappear()
{
    LV_LOG_USER("begin");
}

void Template::onViewDidDisappear()
{
    LV_LOG_USER("begin");
    lv_timer_del(timer);

}

void Template::onViewUnload()
{
    LV_LOG_USER("begin");
}

void Template::onViewDidUnload()
{
    LV_LOG_USER("begin"); 
    for (counter = 0; counter < MAX_BMP_FILES; counter++)
    {
      free(pDirectoryFiles[counter]);
    }
}

void Template::AttachEvent(lv_obj_t* obj)
{
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void Template::Update()
{
//    lv_label_set_text_fmt(View.ui.labelTick, "tick = %d save = %d", Model.GetData(), Model.TickSave);
    if(num == ubNumberOfFiles)
    {
      num = 0;
    }
    sprintf ((char*)str, "0:Media/%s", pDirectoryFiles[num]);
    lv_img_set_src(View.ui.image, (char*)str);
    
    for(uint8_t i=0; i < 255; i++)
    {
      HAL_DSI_ShortWrite(&(hdsi_discovery), 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x51, i);
       HAL_Delay(10);
    }

    for(uint8_t i=255; i > 0; i--)
    {
      HAL_DSI_ShortWrite(&(hdsi_discovery), 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x51, i);
      HAL_Delay(10);
    }
     
//     lv_opa_t opa;
//   opa = lv_obj_get_style_opa(View.ui.image, 0);
////   LV_LOG_USER("opa: %d", opa);
//   if (opa < 10)
//   {
//       //TRANSP -> Bright
////       lv_obj_fade_in(View.ui.image, 1000, 0);
//    lv_img_set_src(View.ui.image, (char*)str);
//     for(uint8_t i=0; i < 255; i++)
//     {
//        HAL_DSI_ShortWrite(&(hdsi_discovery), 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x51, i);
//         HAL_Delay(10);
//     }

//   }
//   else
//   {   
//          for(uint8_t i=255; i > 0; i--)
//     {
//        HAL_DSI_ShortWrite(&(hdsi_discovery), 0, DSI_DCS_SHORT_PKT_WRITE_P1, 0x51, i);
//        HAL_Delay(10);
//     }
//       //Bright -> TRANSP
////       lv_obj_fade_out(View.ui.image, 1000, 0); 
//   }
//    lv_img_set_src(View.ui.image, (char*)str);
//    lv_obj_fade_in(View.ui.image, 3000, 0);
    printf("%d: %s\r\n", num, (char*)str);
    num++;
}

void Template::onTimerUpdate(lv_timer_t* timer)
{
    Template* instance = (Template*)timer->user_data;

    instance->Update();
}

void Template::onEvent(lv_event_t* event)
{
    Template* instance = (Template*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj = lv_event_get_current_target(event);
    lv_event_code_t code = lv_event_get_code(event);
//  printf("lv_event_code_t: %d ", code);

    if (code == LV_EVENT_PRESSED)
    {    

        instance->_Manager->Push("Pages/Dialplate");
    }

    if (code == LV_EVENT_GESTURE)
    {
//      LV_LOG_USER("LV_EVENT_GESTURE %d", code);

      if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
          instance->_Manager->Push("Pages/Dialplate");
      }
    }

}
