#include "Setting_View.h"
#include <stdarg.h>
#include <stdio.h>

using namespace Page;

void Setting_View::Create(lv_obj_t* root)
{

    lv_obj_t* ui_Setting = lv_obj_create(root);
    lv_obj_remove_style_all(ui_Setting);
    lv_obj_clear_flag(ui_Setting, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_clear_flag(ui_Setting, LV_OBJ_FLAG_GESTURE_BUBBLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Setting, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Setting, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_size(ui_Setting, TFT_HOR_RES, TFT_VER_RES);
    lv_obj_set_align(ui_Setting, LV_ALIGN_CENTER);
    ui.cont = ui_Setting;

    lv_obj_t* image = lv_img_create(ui_Setting);
    lv_img_set_src(image, ResourcePool::GetImage("setting_menu"));
    lv_obj_set_align(image, LV_ALIGN_CENTER);
    ui.bg_img = image;
  
//    static lv_style_t style_indic;
//    lv_style_init(&style_indic);
//    lv_style_set_bg_color(&style_indic, lv_palette_lighten(LV_PALETTE_RED, 3));
//    lv_style_set_bg_grad_color(&style_indic, lv_palette_main(LV_PALETTE_RED));
//    lv_style_set_bg_grad_dir(&style_indic, LV_GRAD_DIR_HOR);

//    static lv_style_t style_indic_pr;
//    lv_style_init(&style_indic_pr);
//    lv_style_set_shadow_color(&style_indic_pr, lv_palette_main(LV_PALETTE_RED));
//    lv_style_set_shadow_width(&style_indic_pr, 10);
//    lv_style_set_shadow_spread(&style_indic_pr, 3);

//    /*Create an object with the new style_pr*/
//    lv_obj_t * slider = lv_slider_create(ui_Setting);
//    lv_obj_add_style(slider, &style_indic, LV_PART_INDICATOR);
//    lv_obj_add_style(slider, &style_indic_pr, LV_PART_INDICATOR | LV_STATE_PRESSED);
//    lv_slider_set_value(slider, 70, LV_ANIM_OFF);
//    lv_obj_center(slider);

}
