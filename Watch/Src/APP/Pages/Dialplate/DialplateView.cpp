#include "DialplateView.h"
#include <stdarg.h>
#include <stdio.h>

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

using namespace Page;

void DialplateView::Create(lv_obj_t* root)
{
    BottomInfo_Create(root);
//    TopInfo_Create(root);
//    BtnCont_Create(root);

    ui.anim_timeline = lv_anim_timeline_create();

#define ANIM_DEF(start_time, obj, attr, start, end) \
    {start_time, obj, LV_ANIM_EXEC(attr), start, end, 500, lv_anim_path_ease_out, true}

#define ANIM_OPA_DEF(start_time, obj) \
    ANIM_DEF(start_time, obj, opa_scale, LV_OPA_TRANSP, LV_OPA_COVER)

//    lv_coord_t y_tar_top = lv_obj_get_y(ui.topInfo.cont);
    lv_coord_t y_tar_bottom = lv_obj_get_y(ui.bottomInfo.cont);
//    lv_coord_t h_tar_btn = lv_obj_get_height(ui.btnCont.btnRec);

    lv_anim_timeline_wrapper_t wrapper[] =
    {
//        ANIM_DEF(0, ui.topInfo.cont, y, -lv_obj_get_height(ui.topInfo.cont), y_tar_top),

        ANIM_DEF(200, ui.bottomInfo.cont, y, -lv_obj_get_height(ui.bottomInfo.cont), y_tar_bottom),
        ANIM_OPA_DEF(200, ui.bottomInfo.cont),

//        ANIM_DEF(500, ui.btnCont.btnMap, height, 0, h_tar_btn),
//        ANIM_DEF(600, ui.btnCont.btnRec, height, 0, h_tar_btn),
//        ANIM_DEF(700, ui.btnCont.btnMenu, height, 0, h_tar_btn),
        LV_ANIM_TIMELINE_WRAPPER_END
    };
    lv_anim_timeline_add_wrapper(ui.anim_timeline, wrapper);
}

void DialplateView::Delete()
{
    if(ui.anim_timeline)
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
    lv_obj_clear_flag(cont, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_set_style_bg_color(cont, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cont, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* ui_bg_1 = lv_img_create(cont);
    lv_img_set_src(ui_bg_1, ResourcePool::GetImage("bg1_png"));
    lv_obj_set_width(ui_bg_1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_bg_1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_bg_1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_bg_1, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_bg_1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

//    lv_obj_t* ui_hour_group = lv_obj_create(cont);
//    lv_obj_set_width(ui_hour_group, 289);
//    lv_obj_set_height(ui_hour_group, 222);
//    lv_obj_clear_flag(ui_hour_group, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
//    lv_obj_set_style_bg_color(ui_hour_group, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_opa(ui_hour_group, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* ui_label_hour_1 =lv_label_create(cont);
    lv_obj_set_width(ui_label_hour_1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_label_hour_1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_label_hour_1, -23);
    lv_obj_set_y(ui_label_hour_1, 60);
    lv_label_set_text(ui_label_hour_1, "03");
    lv_obj_set_style_text_color(ui_label_hour_1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_label_hour_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_label_hour_1, ResourcePool::GetFont("Number_extra"), LV_PART_MAIN | LV_STATE_DEFAULT);

//    ui_label_hour_2 = lv_label_create(ui_hour_group);
//    lv_obj_set_width(ui_label_hour_2, LV_SIZE_CONTENT);   /// 1
//    lv_obj_set_height(ui_label_hour_2, LV_SIZE_CONTENT);    /// 1
//    lv_obj_set_x(ui_label_hour_2, 93);
//    lv_obj_set_y(ui_label_hour_2, 67);
//    lv_label_set_text(ui_label_hour_2, "3");
//    lv_obj_set_style_text_color(ui_label_hour_2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_text_opa(ui_label_hour_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_text_font(ui_label_hour_2, &ui_font_Number_extra, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t* ui_label_min = lv_label_create(cont);
    lv_obj_set_width(ui_label_min, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_label_min, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_label_min, 204);
    lv_obj_set_y(ui_label_min, 156);
    lv_label_set_text(ui_label_min, "27");
    lv_obj_set_style_text_color(ui_label_min, lv_color_hex(0xEE1E1E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_label_min, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_label_min, ResourcePool::GetFont("Number_extra"), LV_PART_MAIN | LV_STATE_DEFAULT);

//    lv_obj_t* ui_battery_group = ui_batterygroup_create(cont);
//    lv_obj_set_x(ui_battery_group, 0);
//    lv_obj_set_y(ui_battery_group, 4);

//    lv_obj_t* ui_date_group = ui_dategroup_create(cont);
//    lv_obj_set_x(ui_date_group, -52);
//    lv_obj_set_y(ui_date_group, 194);

//    lv_obj_t* ui_step_group = ui_stepgroup_create(cont);
//    lv_obj_set_x(ui_step_group, -2);
//    lv_obj_set_y(ui_step_group, -5);

//    lv_obj_t* ui_button_top = ui_buttontop_create(cont);
//    lv_obj_set_x(ui_button_top, 89);
//    lv_obj_set_y(ui_button_top, -206);

//    lv_obj_t* ui_button_down = ui_buttondown_create(cont);
//    lv_obj_set_x(ui_button_down, 92);
//    lv_obj_set_y(ui_button_down, 202);

    lv_obj_t* ui_sec_dot = lv_img_create(cont);
    lv_img_set_src(ui_sec_dot, ResourcePool::GetImage("sec_dot_png"));
    lv_obj_set_width(ui_sec_dot, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_sec_dot, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_sec_dot, 0);
    lv_obj_set_y(ui_sec_dot, -190);
    lv_obj_set_align(ui_sec_dot, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_sec_dot, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_sec_dot, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_pivot(ui_sec_dot, 4, 194);
    ui.bottomInfo.cont = cont;

//    lv_obj_t* ui_weather_dots_group2 = lv_obj_create(cont);
//    lv_obj_set_width(ui_weather_dots_group2, 20);
//    lv_obj_set_height(ui_weather_dots_group2, 50);
//    lv_obj_set_x(ui_weather_dots_group2, -10);
//    lv_obj_set_y(ui_weather_dots_group2, 0);
//    lv_obj_set_align(ui_weather_dots_group2, LV_ALIGN_RIGHT_MID);
//    lv_obj_set_flex_flow(ui_weather_dots_group2, LV_FLEX_FLOW_COLUMN);
//    lv_obj_set_flex_align(ui_weather_dots_group2, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
//    lv_obj_clear_flag(ui_weather_dots_group2, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
//    lv_obj_set_style_bg_color(ui_weather_dots_group2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_opa(ui_weather_dots_group2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_pad_row(ui_weather_dots_group2, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_pad_column(ui_weather_dots_group2, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

//    lv_obj_t* ui_dot14 = lv_obj_create(ui_weather_dots_group2);
//    lv_obj_set_width(ui_dot14, 10);
//    lv_obj_set_height(ui_dot14, 10);
//    lv_obj_set_align(ui_dot14, LV_ALIGN_CENTER);
//    lv_obj_clear_flag(ui_dot14, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
//    lv_obj_set_style_radius(ui_dot14, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

//    lv_obj_t* ui_dot15 = lv_obj_create(ui_weather_dots_group2);
//    lv_obj_set_width(ui_dot15, 6);
//    lv_obj_set_height(ui_dot15, 6);
//    lv_obj_set_align(ui_dot15, LV_ALIGN_CENTER);
//    lv_obj_clear_flag(ui_dot15, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
//    lv_obj_set_style_radius(ui_dot15, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_color(ui_dot15, lv_color_hex(0x676767), LV_PART_MAIN | LV_STATE_DEFAULT);
//    lv_obj_set_style_bg_opa(ui_dot15, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

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
    lv_obj_align_to(cont, ui.bottomInfo.cont, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

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
    static const lv_style_prop_t prop[] = { LV_STYLE_WIDTH, LV_STYLE_HEIGHT, LV_STYLE_PROP_INV};
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
