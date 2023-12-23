/**
*********************************************************************
*********
* @project_name :2048
* @file : test.h
* @author : zen3
* @brief : None
* @attention : None
* @date : 2023/12/14
*********************************************************************
*********
*/
//

#ifndef INC_2048_MANAGEAPP_H
#define INC_2048_MANAGEAPP_H
#include <mooncake.h>
#define StatusbarWidth  480
#define StatusbarHigh   50
using namespace MOONCAKE;
#ifdef __cplusplus
extern "C"
{
#endif
/*______________________类的声明在这下面________________:*/
    enum Transfer_APP_statu{
        StartAPP=1,
        CloseAPP,
        DestoryAPP,
    };
class DesktopInitiator:public Mooncake{
    protected:
    static void DrawStatusbar();
    void DrawAPPIcon();
    public:
    };
extern DesktopInitiator mooncake;
#ifdef __cplusplus
}
#endif

#endif //INC_2048_MANAGEAPP_H
