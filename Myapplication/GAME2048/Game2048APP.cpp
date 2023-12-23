/**
*********************************************************************
*********
* @project_name :2048
* @file : Game2048APP.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/12/18 
*********************************************************************
*********
*/
//

#include "Game2048APP.h"
#include "ManageApp.h"
#include "MyUsart.h"
#include "delay.h"

int btnStatus=0;
MOONCAKE::APP_BASE* Game2048APP::m_APPHandle= nullptr;
uint32_t ticks;
void Game2048APP::onCreate() {
    Serial0<<getAppName().c_str()<<endl;
    btn= nullptr;label= nullptr;
    DrawTheStartIcon();
    setAllowBgRunning(false);
}

void Game2048APP::onResume() {
//创建关闭按钮
    DrawTheStopIcon();
    game2048.GameConstruct();
    Serial0<<"resume"<<endl;
}

void Game2048APP::onRunning() {
    if ((HAL_GetTick() - ticks) > 1000) {
        if (Game2048::runner_flag) {
            Serial0 << "RUN" << endl;
            Serial0.print("[%s] onRunning\n", getAppName().c_str());
            ticks = HAL_GetTick();
        }
    }
}

void Game2048APP::onRunningBG() {

    if ((HAL_GetTick() - ticks) > 1000) {
        printf("[%s] onRunningBG\n", getAppName().c_str());
        ticks = HAL_GetTick();
    }
}

void Game2048APP::onPause() {
    Serial0<<"onPause"<<endl;
    DrawTheStartIcon();
    game2048.GameDestruct();
}

void Game2048APP::onDestroy() {
    Serial0<<"Destroy"<<endl;

}

void Game2048APP::event_handler(lv_event_t *e) {
    auto code= lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) {
        btnStatus=*(int*)lv_event_get_user_data(e);
    }
    if (btnStatus==1){
        mooncake.startApp(m_APPHandle);
        Serial0<<"software RUN"<<endl;
    }
    if(btnStatus==2){
        mooncake.closeApp(m_APPHandle);
        Serial0<<"software CLOSE"<<endl;
    }
}

void Game2048APP::DrawTheStartIcon() {
    auto getNowScreen=lv_scr_act();
    lv_obj_clean(getNowScreen);
    if(btn&&label){
        delete label;
        delete btn;
        btn= nullptr;
        label= nullptr;
    }
    btn=new Button(scr_act());
    label=new Label(*btn);
    btn->set_style_bg_color(palette::main(Color::Blue),LV_STATE_DEFAULT);
    btn->set_size(100,100);
    btn->set_pos(20,20);
    TransmissionVar=1;
    btn->add_event_cb(event_handler,LV_EVENT_CLICKED,TransmissionVar);
    label->set_text(getAppName());
    label->align(LV_ALIGN_CENTER,0,0);

}

void Game2048APP::DrawTheStopIcon() {
    auto getNowScreen=lv_scr_act();
    lv_obj_clean(getNowScreen);
    if(btn&&label){  delete label;
        delete btn;

        btn= nullptr;
        label= nullptr;
    }
    btn=new Button(scr_act());
    label=new Label(*btn);
    btn->set_style_bg_color(palette::main(Color::Blue),LV_STATE_DEFAULT);
    btn->set_size(80,40);
    btn->set_pos(20,20);
    TransmissionVar=2;
    btn->add_event_cb(event_handler,LV_EVENT_CLICKED,TransmissionVar);
    label->set_text("close");
    label->align(LV_ALIGN_CENTER,0,0);
}




