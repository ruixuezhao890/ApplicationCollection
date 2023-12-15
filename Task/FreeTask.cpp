/**
*********************************************************************
*********
* @project_name :2048
* @file : FreeTask.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/12/14 
*********************************************************************
*********
*/
//

#include "FreeTask.h"
#include "task.h"
//

#define START_TASK_PRIO 1                   /* 任务优先级 */
#define START_STK_SIZE  128                 /* 任务堆栈大小 */
TaskHandle_t            StartTask_Handler;  /* 任务句柄 */
void start_task(void *pvParameters);        /* 任务函数 */

#define TASK1_PRIO      3                   /* 任务优先级 */
#define TASK1_STK_SIZE  128                 /* 任务堆栈大小 */
TaskHandle_t            Task1Task_Handler;  /* 任务句柄 */
void LVGLUpData(void *pvParameters);             /* 任务函数 */

/* TASK2 任务 配置
 * 包括: 任务句柄 任务优先级 堆栈大小 创建任务
 */
#define TASK2_PRIO      2                   /* 任务优先级 */
#define TASK2_STK_SIZE  512                 /* 任务堆栈大小 */
TaskHandle_t            Task2Task_Handler;  /* 任务句柄 */
extern void APPManagerUpData(void *pvParameters);             /* 任务函数 */


void startFreertos(){
    xTaskCreate((TaskFunction_t )start_task,            /* 任务函数 */
                (const char*    )"start_task",          /* 任务名称 */
                (uint16_t       )START_STK_SIZE,        /* 任务堆栈大小 */
                (void*          )NULL,                  /* 传入给任务函数的参数 */
                (UBaseType_t    )START_TASK_PRIO,       /* 任务优先级 */
                (TaskHandle_t*  )&StartTask_Handler);   /* 任务句柄 */
    vTaskStartScheduler();
}

void start_task(void *pvParameters){
    taskENTER_CRITICAL();           /* 进入临界区 */
    /* 创建任务1 */
    Serial0.println("enter task");
    xTaskCreate((TaskFunction_t )LVGLUpData,                 /* 任务函数 */
                (const char*    )"LVGLUpData",               /* 任务名称 */
                (uint16_t       )TASK1_STK_SIZE,        /* 任务堆栈大小 */
                (void*          )NULL,                  /* 传入给任务函数的参数 */
                (UBaseType_t    )TASK1_PRIO,            /* 任务优先级 */
                (TaskHandle_t*  )&Task1Task_Handler);   /* 任务句柄 */
    /* 创建任务2 */
    xTaskCreate((TaskFunction_t )APPManagerUpData,                 /* 任务函数 */
                (const char*    )"APPManagerUpData",               /* 任务名称 */
                (uint16_t       )TASK2_STK_SIZE,        /* 任务堆栈大小 */
                (void*          )NULL,                  /* 传入给任务函数的参数 */
                (UBaseType_t    )TASK2_PRIO,            /* 任务优先级 */
                (TaskHandle_t*  )&Task2Task_Handler);   /* 任务句柄 */
    vTaskDelete(StartTask_Handler); /* 删除开始任务 */
    taskEXIT_CRITICAL();            /* 退出临界区 */
}
void button_1();
void LVGLUpData(void *pvParameters){
//    button_1();
    for (;;) {
        lv_timer_handler();
        vTaskDelay(5);
    }

}

void button_1() {
    auto root = scr_act();
    static auto button1 = Button(root);
    static auto label1 = Label(button1);

    auto event_handler = [](Event & e) {
        auto code = e.get_code();

        if(code == LV_EVENT_CLICKED) {
            Serial0<<("Clicked")<<endl;
        }
        else if(code == LV_EVENT_VALUE_CHANGED) {
            Serial0<<("Toggled")<<endl;
        }
    };
    button1.add_event_cb(event_handler, LV_EVENT_ALL);
    button1.align(LV_ALIGN_CENTER, 0, -40);

    label1.set_text("Button");
    label1.center();

    static auto button2 = Button(root);
    static auto label2 = Label(button2);
    button2.add_event_cb(event_handler, LV_EVENT_ALL);
    button2.align(LV_ALIGN_CENTER, 0, 40);
    button2.add_flag(LV_OBJ_FLAG_CHECKABLE);
    button2.set_height(LV_SIZE_CONTENT);

    label2.set_text("Toggle");
    label2.center();
}