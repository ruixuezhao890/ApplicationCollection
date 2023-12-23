/**
*********************************************************************
*********
* @project_name :2048
* @file : game.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/12/9 
*********************************************************************
*********
*/
//

#ifndef INC_2048_GAME_H
#define INC_2048_GAME_H
#include "2048.h"
class Game2048{
public:
    Game2048();
    static uint8_t runner_flag;
    void GameConstruct();
    void GameDestruct();
    ~Game2048();
private:

    lv_obj_t * obj_2048;
    static void new_gameBtnCallBack(lv_event_t * e);
    static void game_eventCallBack(lv_event_t * e);

};




#endif //INC_2048_GAME_H
