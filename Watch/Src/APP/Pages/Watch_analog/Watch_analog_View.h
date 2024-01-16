#ifndef __WATCH_ANALOG_VIEW_H
#define __WATCH_ANALOG_VIEW_H

#include "../Page.h"

namespace Page
{

class Watch_analog_View
{
public:
    void Create(lv_obj_t* root);
    void _ui_anim_callback_set_image_angle(lv_anim_t* a, int32_t v);
    void hour_Animation(lv_obj_t* TargetObject, int delay);
    int32_t _ui_anim_callback_get_image_angle(lv_anim_t* a);

public:
    struct
    {
        lv_obj_t* labelTitle;
        lv_obj_t* labelTick;
        lv_obj_t* cont;
        lv_obj_t* image;
        lv_obj_t* ui_bg_2;
        lv_obj_t* ui_clock;
        lv_obj_t* ui_dots;
        lv_obj_t* ui_sec;
        lv_obj_t* ui_min;
        lv_obj_t* ui_hour;

    } ui;

private:

};

}

#endif // !__VIEW_H
