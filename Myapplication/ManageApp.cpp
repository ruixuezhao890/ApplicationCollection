/**
*********************************************************************
*********
* @project_name :2048
* @file : test.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/12/14
*********************************************************************
*********
*/
//

#include "ManageApp.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Game2048_paker.h"
#include "Game2048APP.h"
DesktopInitiator mooncake;//todo 将图标绘制交给这个类！！


 extern "C" void APPManagerUpData() {
    mooncake.init();
    Game2048APP::m_APPHandle=mooncake.createApp(new Game2048_paker("2048", nullptr));
    while (1){
        mooncake.update();
        vTaskDelay(5);
    }
}

void DesktopInitiator::DrawAPPIcon() {
   auto getAPPList=getInstalledAppList();
    for (auto temp:getAPPList) {
        if (temp->getAppName() != "") {
            if (temp->getAppIcon() == nullptr) {

            } else {
                auto getNowScreen = lv_scr_act();
                lv_obj_clean(getNowScreen);//清除所有部件
            }
        }
    }
}
