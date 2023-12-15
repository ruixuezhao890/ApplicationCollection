/** \file lvglpp.h
 *  \brief Base header for LVGL C++ wrapper.
 *
 *  Author: Vincent Paeder
 *  License: MIT
 */
#pragma once
#include "lvgl.h"
#include "lv_port_disp_template.h"
#include "lv_port_indev_template.h"
/** \namespace lvgl
 *  \brief LVGL C++ wrappers.
 */
namespace lvgl {
    bool lv_is_initialized(){

        return true;
    }
    /** \fn void init()
     *  \brief Initializes LVGL.
     */
    void init() {

        lv_init();
        lv_port_disp_init();
        lv_port_indev_init();
    }

    /** \fn bool is_initialized()
     *  \brief Tells if LVGL is initialized.
     *  \returns true if LVGL is initialized, false otherwise.
     */
    bool is_initialized() {
        return lv_is_initialized();
    }

    /** \fn void deinit()
     *  \brief De-initializes LVGL.
     */
    void deinit() {
        lv_deinit();
    }

}
