/**
*********************************************************************
*********
* @project_name :2048
* @file : Game2048_paker.cpp
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/12/18 
*********************************************************************
*********
*/
//

#include "Game2048_paker.h"
#include "Game2048APP.h"

std::string Game2048_paker::getAppName() {
    return name.c_str();
}

void *Game2048_paker::getAppIcon() {
    return icon;
}

void *Game2048_paker::newApp() {

    auto temp=new Game2048APP ;
    temp->setAppPacker(this);
    return temp;
}

void Game2048_paker::deleteApp(void *app) {
    delete (Game2048APP *)app;
}

Game2048_paker::Game2048_paker(String name, void *icon) {
    this->name=name;
    this->icon=icon;
}

Game2048_paker::Game2048_paker() {

}
