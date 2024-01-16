#include "DialplateView.h"
#include <stdarg.h>
#include <stdio.h>

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

using namespace Page;

void DialplateView::Create(lv_obj_t* root)
{
    BottomInfo_Create(root);
        //TopInfo_Create(root);
        //BtnCont_Create(root);

    ui.anim_timeline = lv_anim_timeline_create();

#define ANIM_DEF(start_time, obj, attr, start, end) \
    {start_time, obj, LV_ANIM_EXEC(attr), start, end, 500, lv_anim_path_ease_out, true}

#define ANIM_OPA_DEF(start_time, obj) \
    ANIM_DEF(start_time, obj, opa_scale, LV_OPA_TRANSP, LV_OPA_COVER)

        //lv_coord_t y_tar_top = lv_obj_get_y(ui.topInfo.cont);
    lv_coord_t y_tar_bottom = lv_obj_get_y(ui.bottomInfo.labelClockhour);
    lv_coord_t y_tar_min = lv_obj_get_y(ui.bottomInfo.labelClockmin);

        //lv_coord_t h_tar_btn = lv_obj_get_height(ui.bottomInfo.labelClockhour);

    lv_anim_timeline_wrapper_t wrapper[] =
    {
                //ANIM_DEF(0, ui.topInfo.cont, y, -lv_obj_get_height(ui.topInfo.cont), y_tar_top),

               ANIM_DEF(200, ui.bottomInfo.labelClockhour, y, -lv_obj_get_height(ui.bottomInfo.labelClockhour), y_tar_bottom),
                //ANIM_OPA_DEF(200, ui.bottomInfo.labelClockhour),
                ANIM_DEF(200, ui.bottomInfo.labelClockmin, y, lv_obj_get_height(ui.bottomInfo.labelClockmin)+400, y_tar_min),

                        //ANIM_DEF(500, ui.bottomInfo.labelClockhour, height, 0, h_tar_btn),
          /*              ANIM_DEF(600, ui.btnCont.btnRec, height, 0, h_tar_btn),
                        ANIM_DEF(700, ui.btnCont.btnMenu, height, 0, h_tar_btn),*/
                        LV_ANIM_TIMELINE_WRAPPER_END
    };
    lv_anim_timeline_add_wrapper(ui.anim_timeline, wrapper);
}

void DialplateView::Delete()
{
    if (ui.anim_timeline)
    {
        lv_anim_timeline_del(ui.anim_timeline);
        ui.anim_timeline = nullptr;
    }
}

void DialplateView::TopInfo_Create(lv_obj_t* par)
{
    lv_obj_t* cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, LV_HOR_RES, 142);

    lv_obj_set_style_bg_opa(cont, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(cont, lv_color_hex(0x333333), 0);

    lv_obj_set_style_radius(cont, 27, 0);
    lv_obj_set_y(cont, -36);
    ui.topInfo.cont = cont;

    lv_obj_t* label = lv_label_create(cont);
    lv_obj_set_style_text_font(label, ResourcePool::GetFont("bahnschrift_65"), 0);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_label_set_text(label, "00");
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 63);
    ui.topInfo.labelSpeed = label;

    label = lv_label_create(cont);
    lv_obj_set_style_text_font(label, ResourcePool::GetFont("bahnschrift_17"), 0);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_label_set_text(label, "km/h");
    lv_obj_align_to(label, ui.topInfo.labelSpeed, LV_ALIGN_OUT_BOTTOM_MID, 0, 8);
    ui.topInfo.labelUint = label;
}

void DialplateView::BottomInfo_Create(lv_obj_t* par)
{
  lv_obj_t* cont = lv_obj_create(par);
  lv_obj_remove_style_all(cont);
  lv_obj_set_size(cont, 397, 397);
  lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
  lv_obj_clear_flag(cont, LV_OBJ_FLAG_GESTURE_BUBBLE);      /// Flags
  lv_obj_set_style_bg_color(cont, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(cont, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_align(cont, LV_ALIGN_CENTER);
  ui.bottomInfo.cont = cont;

  //Write codes home_digital
  lv_obj_t* home_digital = lv_obj_create(cont);
  lv_obj_remove_style_all(home_digital);
  lv_obj_clear_flag(home_digital, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
  lv_obj_set_size(home_digital, 397, 397);

//  lv_obj_clear_flag(home_digital, LV_OBJ_FLAG_GESTURE_BUBBLE);      /// Flags
  ui.bottomInfo.bg = home_digital;
  //Write style for home_digital, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_bg_opa(home_digital, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_img_src(home_digital, ResourcePool::GetImage("bg_digital_392x392"), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_img_opa(home_digital, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_arc_step
  //lv_obj_t* home_digital_arc_step = lv_arc_create(home_digital);
  //lv_arc_set_mode(home_digital_arc_step, LV_ARC_MODE_NORMAL);
  //lv_arc_set_range(home_digital_arc_step, 0, 100);
  //lv_arc_set_bg_angles(home_digital_arc_step, 60, 120);
  //lv_arc_set_angles(home_digital_arc_step, 60, 110);
  //lv_arc_set_rotation(home_digital_arc_step, 0);
  //lv_obj_set_pos(home_digital_arc_step, 47, 84);
  //lv_obj_set_size(home_digital_arc_step, 323, 300);

  //Write style for home_digital_arc_step, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  //lv_obj_set_style_bg_opa(home_digital_arc_step, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_border_width(home_digital_arc_step, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_arc_width(home_digital_arc_step, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_arc_opa(home_digital_arc_step, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_arc_color(home_digital_arc_step, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_radius(home_digital_arc_step, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_pad_top(home_digital_arc_step, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_pad_bottom(home_digital_arc_step, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_pad_left(home_digital_arc_step, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_pad_right(home_digital_arc_step, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_shadow_width(home_digital_arc_step, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  ////Write style for home_digital_arc_step, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
  //lv_obj_set_style_arc_width(home_digital_arc_step, 12, LV_PART_INDICATOR | LV_STATE_DEFAULT);
  //lv_obj_set_style_arc_opa(home_digital_arc_step, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
  //lv_obj_set_style_arc_color(home_digital_arc_step, lv_color_hex(0xFF4818), LV_PART_INDICATOR | LV_STATE_DEFAULT);

  ////Write style for home_digital_arc_step, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
  //lv_obj_set_style_bg_opa(home_digital_arc_step, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
  //lv_obj_set_style_pad_all(home_digital_arc_step, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

  //Write codes home_digital_arc_flash
  //lv_obj_t* home_digital_arc_flash = lv_arc_create(home_digital);
  //lv_arc_set_mode(home_digital_arc_flash, LV_ARC_MODE_NORMAL);
  //lv_arc_set_range(home_digital_arc_flash, 0, 100);
  //lv_arc_set_bg_angles(home_digital_arc_flash, 238, 300);
  //lv_arc_set_angles(home_digital_arc_flash, 238, 279);
  //lv_arc_set_rotation(home_digital_arc_flash, 0);
  //lv_obj_set_pos(home_digital_arc_flash, 46, 5);
  //lv_obj_set_size(home_digital_arc_flash, 327, 300);

  ////Write style for home_digital_arc_flash, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  //lv_obj_set_style_bg_opa(home_digital_arc_flash, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_border_width(home_digital_arc_flash, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_arc_width(home_digital_arc_flash, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_arc_opa(home_digital_arc_flash, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_arc_color(home_digital_arc_flash, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_radius(home_digital_arc_flash, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_pad_top(home_digital_arc_flash, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_pad_bottom(home_digital_arc_flash, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_pad_left(home_digital_arc_flash, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_pad_right(home_digital_arc_flash, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  //lv_obj_set_style_shadow_width(home_digital_arc_flash, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  ////Write style for home_digital_arc_flash, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
  //lv_obj_set_style_arc_width(home_digital_arc_flash, 12, LV_PART_INDICATOR | LV_STATE_DEFAULT);
  //lv_obj_set_style_arc_opa(home_digital_arc_flash, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
  //lv_obj_set_style_arc_color(home_digital_arc_flash, lv_color_hex(0x1000ff), LV_PART_INDICATOR | LV_STATE_DEFAULT);

  ////Write style for home_digital_arc_flash, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
  //lv_obj_set_style_bg_opa(home_digital_arc_flash, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
  //lv_obj_set_style_pad_all(home_digital_arc_flash, 0, LV_PART_KNOB | LV_STATE_DEFAULT);


  //Write codes home_digital_img_stepIcon
  lv_obj_t* home_digital_img_stepIcon = lv_img_create(home_digital);
  lv_obj_add_flag(home_digital_img_stepIcon, LV_OBJ_FLAG_CLICKABLE);
  lv_img_set_src(home_digital_img_stepIcon, ResourcePool::GetImage("icn_step_red_alpha_17x21"));
  lv_img_set_pivot(home_digital_img_stepIcon, 50, 50);
  lv_img_set_angle(home_digital_img_stepIcon, 0);
  lv_obj_set_pos(home_digital_img_stepIcon, 156, 338);
  lv_obj_set_size(home_digital_img_stepIcon, 17, 21);

  //Write style for home_digital_img_stepIcon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_img_opa(home_digital_img_stepIcon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_label_stepText
  lv_obj_t* home_digital_label_stepText = lv_label_create(home_digital);
  lv_label_set_text(home_digital_label_stepText, "1526");
  lv_label_set_long_mode(home_digital_label_stepText, LV_LABEL_LONG_WRAP);
  lv_obj_set_pos(home_digital_label_stepText, 186, 338);
  lv_obj_set_size(home_digital_label_stepText, 59, 21);

  //Write style for home_digital_label_stepText, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_border_width(home_digital_label_stepText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(home_digital_label_stepText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(home_digital_label_stepText, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(home_digital_label_stepText, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_letter_space(home_digital_label_stepText, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_line_space(home_digital_label_stepText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(home_digital_label_stepText, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(home_digital_label_stepText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(home_digital_label_stepText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_right(home_digital_label_stepText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(home_digital_label_stepText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_left(home_digital_label_stepText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_width(home_digital_label_stepText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_label_weather1Text
  lv_obj_t* home_digital_label_weather1Text = lv_label_create(home_digital);
  lv_label_set_text(home_digital_label_weather1Text, "26");
  lv_label_set_long_mode(home_digital_label_weather1Text, LV_LABEL_LONG_WRAP);
  lv_obj_set_pos(home_digital_label_weather1Text, 65, 248);
  lv_obj_set_size(home_digital_label_weather1Text, 47, 21);

  //Write style for home_digital_label_weather1Text, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_border_width(home_digital_label_weather1Text, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(home_digital_label_weather1Text, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(home_digital_label_weather1Text, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(home_digital_label_weather1Text, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_letter_space(home_digital_label_weather1Text, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_line_space(home_digital_label_weather1Text, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(home_digital_label_weather1Text, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(home_digital_label_weather1Text, 253, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(home_digital_label_weather1Text, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(home_digital_label_weather1Text, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_right(home_digital_label_weather1Text, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(home_digital_label_weather1Text, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_left(home_digital_label_weather1Text, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_width(home_digital_label_weather1Text, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_label_week
  lv_obj_t* home_digital_label_week = lv_label_create(home_digital);
  lv_label_set_text(home_digital_label_week, "WED");
  lv_label_set_long_mode(home_digital_label_week, LV_LABEL_LONG_WRAP);
  lv_obj_set_pos(home_digital_label_week, 34, 143);
  lv_obj_set_size(home_digital_label_week, 67, 25);

  //Write style for home_digital_label_week, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_border_width(home_digital_label_week, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(home_digital_label_week, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(home_digital_label_week, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(home_digital_label_week, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_letter_space(home_digital_label_week, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_line_space(home_digital_label_week, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(home_digital_label_week, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(home_digital_label_week, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(home_digital_label_week, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_right(home_digital_label_week, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(home_digital_label_week, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_left(home_digital_label_week, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_width(home_digital_label_week, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_label_date
  lv_obj_t* home_digital_label_date = lv_label_create(home_digital);
  lv_label_set_text(home_digital_label_date, "05/15");
  lv_label_set_long_mode(home_digital_label_date, LV_LABEL_LONG_WRAP);
  lv_obj_set_pos(home_digital_label_date, 34, 111);
  lv_obj_set_size(home_digital_label_date, 74, 21);

  //Write style for home_digital_label_date, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_border_width(home_digital_label_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(home_digital_label_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(home_digital_label_date, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(home_digital_label_date, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_letter_space(home_digital_label_date, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_line_space(home_digital_label_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(home_digital_label_date, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(home_digital_label_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(home_digital_label_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_right(home_digital_label_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(home_digital_label_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_left(home_digital_label_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_width(home_digital_label_date, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_img_flash
  lv_obj_t* home_digital_img_flash = lv_img_create(home_digital);
  lv_obj_add_flag(home_digital_img_flash, LV_OBJ_FLAG_CLICKABLE);
  lv_img_set_src(home_digital_img_flash, ResourcePool::GetImage("icn_flash_blue_alpha_17x21"));
  lv_img_set_pivot(home_digital_img_flash, 50, 50);
  lv_img_set_angle(home_digital_img_flash, 0);
  lv_obj_set_pos(home_digital_img_flash, 162, 35);
  lv_obj_set_size(home_digital_img_flash, 17, 21);

  //Write style for home_digital_img_flash, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_img_opa(home_digital_img_flash, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_label_flashText
  lv_obj_t* home_digital_label_flashText = lv_label_create(home_digital);
  lv_label_set_text(home_digital_label_flashText, "86%");
  lv_label_set_long_mode(home_digital_label_flashText, LV_LABEL_LONG_WRAP);
  lv_obj_set_pos(home_digital_label_flashText, 186, 35);
  lv_obj_set_size(home_digital_label_flashText, 59, 21);

  //Write style for home_digital_label_flashText, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_border_width(home_digital_label_flashText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(home_digital_label_flashText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(home_digital_label_flashText, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(home_digital_label_flashText, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_letter_space(home_digital_label_flashText, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_line_space(home_digital_label_flashText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(home_digital_label_flashText, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(home_digital_label_flashText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(home_digital_label_flashText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_right(home_digital_label_flashText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(home_digital_label_flashText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_left(home_digital_label_flashText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_width(home_digital_label_flashText, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_img_dialDot
  lv_obj_t* home_digital_img_dialDot = lv_img_create(home_digital);
  lv_obj_add_flag(home_digital_img_dialDot, LV_OBJ_FLAG_CLICKABLE);
  lv_img_set_src(home_digital_img_dialDot, ResourcePool::GetImage("menu_alpha_11x117"));
  lv_img_set_pivot(home_digital_img_dialDot, 50, 50);
  lv_img_set_angle(home_digital_img_dialDot, 0);
  lv_obj_set_pos(home_digital_img_dialDot, 365, 140);
  lv_obj_set_size(home_digital_img_dialDot, 11, 117);

  //Write style for home_digital_img_dialDot, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_img_opa(home_digital_img_dialDot, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_label_min
  lv_obj_t* home_digital_label_min = lv_label_create(home_digital);
  lv_label_set_text(home_digital_label_min, "32");
  lv_label_set_long_mode(home_digital_label_min, LV_LABEL_LONG_WRAP);
  lv_obj_set_pos(home_digital_label_min, 165, 198);
  lv_obj_set_size(home_digital_label_min, 152, 104);
  ui.bottomInfo.labelClockmin = home_digital_label_min;

  //Write style for home_digital_label_min, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_border_width(home_digital_label_min, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(home_digital_label_min, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(home_digital_label_min, lv_color_hex(0xFF4818), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(home_digital_label_min, ResourcePool::GetFont("montserratMedium_110"), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_letter_space(home_digital_label_min, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_line_space(home_digital_label_min, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(home_digital_label_min, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(home_digital_label_min, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(home_digital_label_min, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_right(home_digital_label_min, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(home_digital_label_min, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_left(home_digital_label_min, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_width(home_digital_label_min, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_label_hour
  lv_obj_t* home_digital_label_hour = lv_label_create(home_digital);
  lv_label_set_text(home_digital_label_hour, "15");
  lv_label_set_long_mode(home_digital_label_hour, LV_LABEL_LONG_WRAP);
  lv_obj_set_pos(home_digital_label_hour, 108, 76);
  lv_obj_set_size(home_digital_label_hour, 150, 122);
  ui.bottomInfo.labelClockhour = home_digital_label_hour;

  //Write style for home_digital_label_hour, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_border_width(home_digital_label_hour, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_radius(home_digital_label_hour, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(home_digital_label_hour, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(home_digital_label_hour, ResourcePool::GetFont("montserratMedium_110"), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_letter_space(home_digital_label_hour, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_line_space(home_digital_label_hour, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_align(home_digital_label_hour, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(home_digital_label_hour, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_top(home_digital_label_hour, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_right(home_digital_label_hour, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(home_digital_label_hour, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_pad_left(home_digital_label_hour, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_shadow_width(home_digital_label_hour, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_img_messageIcon
  lv_obj_t* home_digital_img_messageIcon = lv_img_create(home_digital);
  lv_obj_add_flag(home_digital_img_messageIcon, LV_OBJ_FLAG_CLICKABLE);
  lv_img_set_src(home_digital_img_messageIcon, ResourcePool::GetImage("icn_message_alpha_25x25"));
  lv_img_set_pivot(home_digital_img_messageIcon, 50, 50);
  lv_img_set_angle(home_digital_img_messageIcon, 0);
  lv_obj_set_pos(home_digital_img_messageIcon, 306, 269);
  lv_obj_set_size(home_digital_img_messageIcon, 25, 25);

  //Write style for home_digital_img_messageIcon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_img_opa(home_digital_img_messageIcon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_img_sportIcon
  lv_obj_t* home_digital_img_sportIcon = lv_img_create(home_digital);
  lv_obj_add_flag(home_digital_img_sportIcon, LV_OBJ_FLAG_CLICKABLE);
  lv_img_set_src(home_digital_img_sportIcon, ResourcePool::GetImage("icn_sport_alpha_12x24"));
  lv_img_set_pivot(home_digital_img_sportIcon, 50, 50);
  lv_img_set_angle(home_digital_img_sportIcon, 0);
  lv_obj_set_pos(home_digital_img_sportIcon, 317, 102);
  lv_obj_set_size(home_digital_img_sportIcon, 12, 24);

  //Write style for home_digital_img_sportIcon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_img_opa(home_digital_img_sportIcon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_img_weather1Icon
  lv_obj_t* home_digital_img_weather1Icon = lv_img_create(home_digital);
  lv_obj_add_flag(home_digital_img_weather1Icon, LV_OBJ_FLAG_CLICKABLE);
  lv_img_set_src(home_digital_img_weather1Icon, ResourcePool::GetImage("icn_weather_1_alpha_41x33"));
  lv_img_set_pivot(home_digital_img_weather1Icon, 50, 50);
  lv_img_set_angle(home_digital_img_weather1Icon, 0);
  lv_obj_set_pos(home_digital_img_weather1Icon, 57, 208);
  lv_obj_set_size(home_digital_img_weather1Icon, 41, 33);

  //Write style for home_digital_img_weather1Icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_img_recolor_opa(home_digital_img_weather1Icon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_img_recolor(home_digital_img_weather1Icon, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_img_opa(home_digital_img_weather1Icon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_img_sportText
  lv_obj_t* home_digital_img_sportText = lv_img_create(home_digital);
  lv_obj_add_flag(home_digital_img_sportText, LV_OBJ_FLAG_CLICKABLE);
  lv_img_set_src(home_digital_img_sportText, ResourcePool::GetImage("text_sport_alpha_50x50"));
  lv_img_set_pivot(home_digital_img_sportText, 50, 50);
  lv_img_set_angle(home_digital_img_sportText, 30);
  lv_obj_set_pos(home_digital_img_sportText, 321, 76);
  lv_obj_set_size(home_digital_img_sportText, 50, 50);

  //Write style for home_digital_img_sportText, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_img_opa(home_digital_img_sportText, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_img_messageText
  lv_obj_t* home_digital_img_messageText = lv_img_create(home_digital);
  lv_obj_add_flag(home_digital_img_messageText, LV_OBJ_FLAG_CLICKABLE);
  lv_img_set_src(home_digital_img_messageText, ResourcePool::GetImage("text_message_alpha_70x70"));
  lv_img_set_pivot(home_digital_img_messageText, 50, 50);
  lv_img_set_angle(home_digital_img_messageText, -50);
  lv_obj_set_pos(home_digital_img_messageText, 306, 257);
  lv_obj_set_size(home_digital_img_messageText, 70, 70);

  //Write style for home_digital_img_messageText, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_img_opa(home_digital_img_messageText, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Write codes home_digital_img_dot
  lv_obj_t* home_digital_img_dot = lv_img_create(home_digital);
  lv_obj_add_flag(home_digital_img_dot, LV_OBJ_FLAG_CLICKABLE);
  lv_img_set_src(home_digital_img_dot, ResourcePool::GetImage("dot_alpha_8x8"));
  lv_img_set_pivot(home_digital_img_dot, 50, 50);
  lv_img_set_angle(home_digital_img_dot, 0);
  lv_obj_set_pos(home_digital_img_dot, 365, 140);
  lv_obj_set_size(home_digital_img_dot, 8, 8);

  //Write style for home_digital_img_dot, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
  lv_obj_set_style_img_opa(home_digital_img_dot, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

  //Update current screen layout.
  lv_obj_update_layout(home_digital);
    //lv_obj_t* ui_bg_1 = lv_img_create(cont);
    //lv_img_set_src(ui_bg_1, ResourcePool::GetImage("bg1_png"));
    //lv_obj_set_width(ui_bg_1, LV_SIZE_CONTENT);   /// 1
    //lv_obj_set_height(ui_bg_1, LV_SIZE_CONTENT);    /// 1
    //lv_obj_set_align(ui_bg_1, LV_ALIGN_CENTER);
    //lv_obj_add_flag(ui_bg_1, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    //lv_obj_clear_flag(ui_bg_1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    //lv_obj_t* ui_hour_group = lv_obj_create(cont);
    //lv_obj_set_width(ui_hour_group, 289);
    //lv_obj_set_height(ui_hour_group, 222);
    //lv_obj_clear_flag(ui_hour_group, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    //lv_obj_set_style_bg_color(ui_hour_group, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    //lv_obj_set_style_bg_opa(ui_hour_group, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //lv_obj_t* ui_label_hour_1 = lv_label_create(ui_hour_group);
    //lv_obj_set_width(ui_label_hour_1, LV_SIZE_CONTENT);   /// 1
    //lv_obj_set_height(ui_label_hour_1, LV_SIZE_CONTENT);    /// 1
    //lv_obj_set_x(ui_label_hour_1, -23);
    //lv_obj_set_y(ui_label_hour_1, 60);
    //lv_label_set_text(ui_label_hour_1, "03");
    //lv_obj_set_style_text_color(ui_label_hour_1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    //lv_obj_set_style_text_opa(ui_label_hour_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    //lv_obj_set_style_text_font(ui_label_hour_1, ResourcePool::GetFont("Number_extra"), LV_PART_MAIN | LV_STATE_DEFAULT);
    //ui.bottomInfo.labelClockhour = ui_label_hour_1;

    ////    ui_label_hour_2 = lv_label_create(ui_hour_group);
    ////    lv_obj_set_width(ui_label_hour_2, LV_SIZE_CONTENT);   /// 1
    ////    lv_obj_set_height(ui_label_hour_2, LV_SIZE_CONTENT);    /// 1
    ////    lv_obj_set_x(ui_label_hour_2, 93);
    ////    lv_obj_set_y(ui_label_hour_2, 67);
    ////    lv_label_set_text(ui_label_hour_2, "3");
    ////    lv_obj_set_style_text_color(ui_label_hour_2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    ////    lv_obj_set_style_text_opa(ui_label_hour_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    ////    lv_obj_set_style_text_font(ui_label_hour_2, &ui_font_Number_extra, LV_PART_MAIN | LV_STATE_DEFAULT);

    //lv_obj_t* ui_label_min = lv_label_create(cont);
    //lv_obj_set_width(ui_label_min, LV_SIZE_CONTENT);   /// 1
    //lv_obj_set_height(ui_label_min, LV_SIZE_CONTENT);    /// 1
    //lv_obj_set_x(ui_label_min, 204);
    //lv_obj_set_y(ui_label_min, 156);
    //lv_label_set_text(ui_label_min, "27");
    //lv_obj_set_style_text_color(ui_label_min, lv_color_hex(0xEE1E1E), LV_PART_MAIN | LV_STATE_DEFAULT);
    //lv_obj_set_style_text_opa(ui_label_min, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    //lv_obj_set_style_text_font(ui_label_min, ResourcePool::GetFont("Number_extra"), LV_PART_MAIN | LV_STATE_DEFAULT);
    //ui.bottomInfo.labelClockmin = ui_label_min;

    ////    lv_obj_t* ui_battery_group = ui_batterygroup_create(cont);
    ////    lv_obj_set_x(ui_battery_group, 0);
    ////    lv_obj_set_y(ui_battery_group, 4);

    ////    lv_obj_t* ui_date_group = ui_dategroup_create(cont);
    ////    lv_obj_set_x(ui_date_group, -52);
    ////    lv_obj_set_y(ui_date_group, 194);

    ////    lv_obj_t* ui_step_group = ui_stepgroup_create(cont);
    ////    lv_obj_set_x(ui_step_group, -2);
    ////    lv_obj_set_y(ui_step_group, -5);

    ////    lv_obj_t* ui_button_top = ui_buttontop_create(cont);
    ////    lv_obj_set_x(ui_button_top, 89);
    ////    lv_obj_set_y(ui_button_top, -206);

    ////    lv_obj_t* ui_button_down = ui_buttondown_create(cont);
    ////    lv_obj_set_x(ui_button_down, 92);
    ////    lv_obj_set_y(ui_button_down, 202);

    //lv_obj_t* ui_sec_dot = lv_img_create(cont);
    //lv_img_set_src(ui_sec_dot, ResourcePool::GetImage("sec_dot_png"));
    //lv_obj_set_width(ui_sec_dot, LV_SIZE_CONTENT);   /// 1
    //lv_obj_set_height(ui_sec_dot, LV_SIZE_CONTENT);    /// 1
    //lv_obj_set_x(ui_sec_dot, 0);
    //lv_obj_set_y(ui_sec_dot, -190);

    //lv_obj_set_align(ui_sec_dot, LV_ALIGN_CENTER);
    //lv_obj_add_flag(ui_sec_dot, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    //lv_obj_clear_flag(ui_sec_dot, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    //lv_img_set_pivot(ui_sec_dot, 4, 194);
    //ui.bottomInfo.labelClock = ui_sec_dot;

    //lv_obj_t* ui_weather_dots_group2 = lv_obj_create(cont);
    //lv_obj_set_width(ui_weather_dots_group2, 20);
    //lv_obj_set_height(ui_weather_dots_group2, 50);
    //lv_obj_set_x(ui_weather_dots_group2, -10);
    //lv_obj_set_y(ui_weather_dots_group2, 0);
    //lv_obj_set_align(ui_weather_dots_group2, LV_ALIGN_RIGHT_MID);
    //lv_obj_set_flex_flow(ui_weather_dots_group2, LV_FLEX_FLOW_COLUMN);
    //lv_obj_set_flex_align(ui_weather_dots_group2, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    //lv_obj_clear_flag(ui_weather_dots_group2, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    //lv_obj_set_style_bg_color(ui_weather_dots_group2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    //lv_obj_set_style_bg_opa(ui_weather_dots_group2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    //lv_obj_set_style_pad_row(ui_weather_dots_group2, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    //lv_obj_set_style_pad_column(ui_weather_dots_group2, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    //lv_obj_t* ui_dot14 = lv_obj_create(ui_weather_dots_group2);
    //lv_obj_set_width(ui_dot14, 10);
    //lv_obj_set_height(ui_dot14, 10);
    //lv_obj_set_align(ui_dot14, LV_ALIGN_CENTER);
    //lv_obj_clear_flag(ui_dot14, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    //lv_obj_set_style_radius(ui_dot14, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    //lv_obj_t* ui_dot15 = lv_obj_create(ui_weather_dots_group2);
    //lv_obj_set_width(ui_dot15, 6);
    //lv_obj_set_height(ui_dot15, 6);
    //lv_obj_set_align(ui_dot15, LV_ALIGN_CENTER);
    //lv_obj_clear_flag(ui_dot15, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    //lv_obj_set_style_radius(ui_dot15, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    //lv_obj_set_style_bg_color(ui_dot15, lv_color_hex(0x676767), LV_PART_MAIN | LV_STATE_DEFAULT);
    //lv_obj_set_style_bg_opa(ui_dot15, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    //ui.bottomInfo.cont = cont;
    //ui.bottomInfo.bg = ui_bg_1;

    //    lv_obj_add_event_cb(ui_button_top, ui_event_button_top_buttontop, LV_EVENT_ALL, NULL);
    //    lv_obj_add_event_cb(ui_button_down, ui_event_button_down_buttondown, LV_EVENT_ALL, NULL);
    //    lv_obj_add_event_cb(cont, ui_event_watch_digital, LV_EVENT_ALL, NULL);

}

void DialplateView::SubInfoGrp_Create(lv_obj_t* par, SubInfo_t* info, const char* unitText)
{
    lv_obj_t* cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, 93, 39);

    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(
        cont,
        LV_FLEX_ALIGN_SPACE_AROUND,
        LV_FLEX_ALIGN_CENTER,
        LV_FLEX_ALIGN_CENTER
    );

    lv_obj_t* label = lv_label_create(cont);
    lv_obj_set_style_text_font(label, ResourcePool::GetFont("bahnschrift_17"), 0);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    info->lableValue = label;

    label = lv_label_create(cont);
    lv_obj_set_style_text_font(label, ResourcePool::GetFont("bahnschrift_13"), 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0xb3b3b3), 0);
    lv_label_set_text(label, unitText);
    info->lableUnit = label;

    info->cont = cont;
}

void DialplateView::BtnCont_Create(lv_obj_t* par)
{
    lv_obj_t* cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);
    lv_obj_set_size(cont, LV_HOR_RES, 40);
    lv_obj_align_to(cont, ui.bottomInfo.cont, LV_ALIGN_OUT_TOP_MID, 0, 100);

    /*lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_place(
        cont,
        LV_FLEX_PLACE_SPACE_AROUND,
        LV_FLEX_PLACE_CENTER,
        LV_FLEX_PLACE_CENTER
    );*/

    ui.btnCont.cont = cont;

    ui.btnCont.btnMap = Btn_Create(cont, ResourcePool::GetImage("locate"), -80);
    ui.btnCont.btnRec = Btn_Create(cont, ResourcePool::GetImage("start"), 0);
    ui.btnCont.btnMenu = Btn_Create(cont, ResourcePool::GetImage("menu"), 80);
}

lv_obj_t* DialplateView::Btn_Create(lv_obj_t* par, const void* img_src, lv_coord_t x_ofs)
{
    lv_obj_t* obj = lv_obj_create(par);
    lv_obj_remove_style_all(obj);
    lv_obj_set_size(obj, 40, 31);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_align(obj, LV_ALIGN_CENTER, x_ofs, 0);
    lv_obj_set_style_bg_img_src(obj, img_src, 0);

    lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, 0);
    lv_obj_set_style_width(obj, 45, LV_STATE_PRESSED);
    lv_obj_set_style_height(obj, 25, LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x666666), 0);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xbbbbbb), LV_STATE_PRESSED);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff931e), LV_STATE_FOCUSED);
    lv_obj_set_style_radius(obj, 9, 0);

    static lv_style_transition_dsc_t tran;
    static const lv_style_prop_t prop[] = { LV_STYLE_WIDTH, LV_STYLE_HEIGHT, LV_STYLE_PROP_INV };
    lv_style_transition_dsc_init(
        &tran,
        prop,
        lv_anim_path_ease_out,
        200,
        0,
        nullptr
    );
    lv_obj_set_style_transition(obj, &tran, LV_STATE_PRESSED);
    lv_obj_set_style_transition(obj, &tran, LV_STATE_FOCUSED);

    lv_obj_update_layout(obj);

    return obj;
}

void DialplateView::AppearAnimStart(bool reverse)
{
    lv_anim_timeline_set_reverse(ui.anim_timeline, reverse);
    lv_anim_timeline_start(ui.anim_timeline);
}
