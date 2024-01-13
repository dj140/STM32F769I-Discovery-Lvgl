#ifndef __SYSTEM_INFOS_VIEW_H
#define __SYSTEM_INFOS_VIEW_H

#include "../Page.h"

namespace Page
{

class SystemInfosView
{
public:
    void Create(lv_obj_t* root);
    void Delete();

public:
    typedef struct
    {
        lv_obj_t* cont;
        lv_obj_t* icon;
        lv_obj_t* labelInfo;
        lv_obj_t* labelData;
    } item_t;

    struct
    {
        item_t sport;
        item_t gps;
        item_t mag;
        item_t imu;
        item_t rtc;
        item_t battery;
        item_t storage;
        item_t system;
    } ui;
    struct  {
        /* Display data */
        int16_t* dispHor = nullptr;
        int16_t* dispVer = nullptr;
        bool dispModePortrait = false;
        bool is_long_row = true;
        int icon_x = 0;
        int icon_y = 0;
        /* Widget */
        lv_obj_t* screenMain = nullptr;

        lv_obj_t* appPanel = nullptr;
        lv_coord_t appPanelHor = 0;
        lv_coord_t appPanelVer = 0;

        lv_obj_t* infoPanel = nullptr;
        lv_coord_t infoPanelHor = 0;
        lv_coord_t infoPanelVer = 0;
        lv_obj_t* infoClockHour = nullptr;
        lv_obj_t* infoClockMin = nullptr;
        lv_obj_t* infoStepCounter = nullptr;
        lv_obj_t* infoBatLevel = nullptr;
        lv_obj_t* infoBatIcon = nullptr;
        lv_obj_t* infoWifiIcon = nullptr;
        lv_obj_t* infoBleIcon = nullptr;
        lv_obj_t* infoNoteIcon = nullptr;

        uint32_t infoUpdateTickCount = 0;
        char infoUpdateBuffer[24];
    }LauncherData_t;
    struct BubbleConfig_t {
        lv_coord_t iconColMax = 0;
        lv_coord_t iconColNum = 0;
        lv_coord_t iconRowMax = 0;
        lv_coord_t iconSpaceX = 0;
        lv_coord_t iconSpaceY = 0;
        lv_coord_t iconXoffset = 0;
        lv_coord_t iconYoffset = 0;
    };
public:
    void SetSport(
        float trip,
        const char* time,
        float maxSpd
    );
    void SetGPS(
        float lat,
        float lng,
        float alt,
        const char* utc,
        float course,
        float speed
    );
    void SetMAG(
        float dir,
        int x,
        int y,
        int z
    );
    void SetIMU(
        int step,
        const char* info
    );
    void SetRTC(
        const char* dateTime
    );
    void SetBattery(
        int usage,
        float voltage,
        const char* state
    );
    void SetStorage(
        const char* detect,
        const char* size,
        const char* type,
        const char* version
    );
    void SetSystem(
        const char* firmVer,
        const char* authorName,
        const char* lvglVer,
        const char* bootTime,
        const char* compilerName,
        const char* bulidTime
    );

    void SetScrollToY(lv_obj_t* obj, lv_coord_t y, lv_anim_enable_t en);
    void updateAppIconZoom(lv_obj_t* obj);

    static void onFocus(lv_group_t* e);

private:
    struct
    {
        lv_style_t icon;
        lv_style_t focus;
        lv_style_t info;
        lv_style_t data;
    } style;

private:
    void Group_Init();
    BubbleConfig_t _bubble_cfg;
    void create_app_panel(lv_obj_t* par);
    void Style_Init();
    void Style_Reset();
    void Item_Create(
        item_t* item,
        lv_obj_t* par,
        const char* name,
        const char* img_src
    );
};

}

#endif // !__VIEW_H
