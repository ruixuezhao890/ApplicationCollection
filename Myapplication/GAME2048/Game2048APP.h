/**
*********************************************************************
*********
* @project_name :2048
* @file : Game2048APP.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/12/18 
*********************************************************************
*********
*/
//

#ifndef INC_2048_GAME2048APP_H
#define INC_2048_GAME2048APP_H

#include "app.h"
//#include "core/lv_obj.h"
#include "LVGLINC.h"
#include "game.h"

extern int btnStatus;
class Game2048APP: public MOONCAKE::APP_BASE{
private:
    Button* btn;
    Label* label;
    lv_obj_t* screen;
    int TransmissionVar;
    Game2048 game2048;
protected:
    static void event_handler(lv_event_t * e);
public:
    static APP_BASE * m_APPHandle;

    void onCreate() override;

    void onResume() override;

    void onRunning() override;

    void onRunningBG() override;

    void onPause() override;

    void onDestroy() override;
protected:
    void DrawTheStartIcon();
    void DrawTheStopIcon();
};

#endif //INC_2048_GAME2048APP_H
