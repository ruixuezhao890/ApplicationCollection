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
Mooncake mooncake;
 extern "C" void APPManagerUpData() {
    mooncake.init();
    Game2048APP::m_APPHandle=mooncake.createApp(new Game2048_paker("2048", nullptr));
    while (1){
        mooncake.update();
        vTaskDelay(5);
    }
}