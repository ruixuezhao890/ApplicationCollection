/**
*********************************************************************
*********
* @project_name :2048
* @file : Game2048_paker.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/12/18 
*********************************************************************
*********
*/
//

#ifndef INC_2048_GAME2048_PAKER_H
#define INC_2048_GAME2048_PAKER_H
#include "MyUsart.h"
#include "app.h"
#include "core/lv_obj.h"

class Game2048_paker :public MOONCAKE::APP_PACKER_BASE{
private:
    String name;
    void * icon;
public:
    Game2048_paker();
    Game2048_paker( String name,void * icon);
    std::string getAppName() override;

    void *getAppIcon() override;

    void *newApp() override;

    void deleteApp(void *app) override;
};


#endif //INC_2048_GAME2048_PAKER_H
