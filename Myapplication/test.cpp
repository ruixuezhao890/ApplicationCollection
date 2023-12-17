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

#include "test.h"
#include "FreeRTOS.h"
#include "task.h"
//
#include "LVGLINC.h"
#include "delay.h"
#include <mooncake.h>
#include "MyUsart.h"
using namespace MOONCAKE;
int btn_value = 0;
using namespace lvgl::core;
using namespace lvgl::widgets;
Mooncake mooncake;
class AppExample : public APP_BASE
{
private:
    uint32_t count;
    String m_AppName;
    lv_obj_t* screen;
    int bbb1;
    int bbb2;
    int bbb3;
    uint32_t ticks;

    static void event_handler(lv_event_t * e)
    {
        lv_event_code_t code = lv_event_get_code(e);

        if(code == LV_EVENT_CLICKED) {

            btn_value = *(int*)lv_event_get_user_data(e);

        }

    }
public:
    AppExample(){

    }
    AppExample(const char* name, void* icon = nullptr){
        m_AppName=name;
    }
    void onCreate() override
    {
        Serial0<<getAppName().c_str()<<("onCreate\n");
        setAllowBgRunning(false);
        count = millis();
    }

    void onResume() override
    {
//        printf("[%s] onResume\n", getAppName().c_str());
        Serial0.println(getAppName().c_str());
        Serial0.println("onResume");


        btn_value = 0;


        screen = lv_obj_create(NULL);
        lv_scr_load_anim(screen, LV_SCR_LOAD_ANIM_MOVE_TOP, 50, 0, false);


        lv_obj_t * label;

        lv_obj_t * btn1 = lv_btn_create(screen);
        bbb1 = 1;
        lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, (void*)&bbb1);
        lv_obj_align(btn1, LV_ALIGN_CENTER, 0, -40);

        label = lv_label_create(btn1);
        // lv_obj_add_flag(btn1, LV_OBJ_FLAG_CHECKABLE);
        lv_obj_add_state(btn1, LV_STATE_CHECKED);
        lv_label_set_text(label, "Quit App");
        lv_obj_center(label);



        lv_obj_t * btn2 = lv_btn_create(screen);
        bbb2 = 2;
        lv_obj_add_event_cb(btn2, event_handler, LV_EVENT_ALL, (void*)&bbb2);
        lv_obj_align(btn2, LV_ALIGN_CENTER, 0, 40);

        label = lv_label_create(btn2);
        lv_label_set_text(label, "Run background");
        lv_obj_center(label);

        lv_obj_t * btn3 = lv_btn_create(screen);
        bbb3 = 3;
        lv_obj_add_event_cb(btn3, event_handler, LV_EVENT_ALL, (void*)&bbb3);
        lv_obj_align(btn3, LV_ALIGN_CENTER, 0, 100);

        label = lv_label_create(btn3);
        lv_label_set_text(label, "resume background");
        lv_obj_center(label);

    }

    void onRunning() override
    {
        if (millis() - count > 1000)
        {
            Serial0.println("The application is running");
            count = millis();
        }

        if (btn_value == 1) {
            setAllowBgRunning(false);
            destroyApp();
        }
        else if (btn_value == 2) {
            setAllowBgRunning(true);
            closeApp();
        }

    }
    void onRunningBG() {
        // printf("[%s] onRunningBG\n", getAppName().c_str());

        if ((lv_tick_get() - ticks) > 1000) {
//            printf("[%s] onRunningBG\n", getAppName().c_str());
            Serial0.println(getAppName().c_str());
            Serial0.println("onRunningBG");
            if (btn_value==3){
                startApp();
                resetGoingCloseFlag();
                setAllowBgRunning(false);
            }
            ticks = lv_tick_get();

        }

    }
    void onPause() {
        Serial0.println(getAppName().c_str());
        Serial0.println("onPause");
    }
    void onDestroy() {
        Serial0.println(getAppName().c_str());
        Serial0.println("onDestroy");
    }
};


// A app packer to store static resource and memory management
class AppExample_packer : public APP_PACKER_BASE
{
public:
    std::string getAppName() override { return "AppExample"; }
    void * newApp() override { return new AppExample; }
    void deleteApp(void *app) override { delete (AppExample*)app; }
};


 extern "C" void APPManagerUpData() {
    mooncake.init();
    mooncake.installApp(new AppExample_packer);
//
//    // We can get a list of installed apps from app register
    auto installed_apps_list = mooncake.getAppRegister().getInstalledAppList();
////    spdlog::info("first installed app's name is {}", installed_apps_list[0]->getAppName());
//
//    // Now let create and start an app with the installed app packer
    mooncake.createAndStartApp(installed_apps_list[0]);
    while (1){
//        HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_9);
        mooncake.update();
        vTaskDelay(5);
    }
}