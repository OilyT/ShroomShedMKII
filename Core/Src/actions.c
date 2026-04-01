/*
 * actions.c
 *
 * Description: UI actions implementation
 * Author: 
 * Date: 
 */

#include <stdint.h>
#include <stdbool.h>
#include "actions.h"
#include "screens.h"
#include "vars.h"
#include "shroomshed.h"
#include "lvgl.h"
#include "ui.h"
#include "rgb.h"
#include "display_manager.h"


// GENERAL ACTIONS
void action_load_previous_screen(lv_event_t *e) {
    load_previous_screen();
}

// MAIN SCREEN ACTIONS 

inline void action_load_screen_menu(lv_event_t *e) {
    switch_screen(SCREEN_ID_MENU_MAIN);
}

void action_increment_humidity(lv_event_t *e) {
    uint8_t step = (uint8_t)(uintptr_t)lv_event_get_user_data(e);
    shedControl.humidityControlValue += step;
    if (shedControl.humidityControlValue > 100) {
        shedControl.humidityControlValue = 100;
    }
}

void action_decrement_humidity(lv_event_t * e) {
    uint8_t step = (uint8_t)(uintptr_t)lv_event_get_user_data(e);
    shedControl.humidityControlValue -= step;
    if (shedControl.humidityControlValue < 30) {
        shedControl.humidityControlValue = 30;
    }
}

void action_increment_airflow(lv_event_t * e) {
    shedControl.fanControlValue += 5;
    if (shedControl.fanControlValue > 100) {
        shedControl.fanControlValue = 100;
    }

}

void action_decrement_airflow(lv_event_t *e) {
    shedControl.fanControlValue -= 5;
    if (shedControl.fanControlValue < 10) {
        shedControl.fanControlValue = 10;
    }
}

// MAIN MENU ACTIONS
inline void action_load_screen_disco(lv_event_t * e) {
    switch_screen(SCREEN_ID_DISCO_MODE);
}

void action_load_menu_button_matrix(lv_event_t * e) {
    lv_obj_t *ta = lv_event_get_target(e);
    uint16_t id = lv_buttonmatrix_get_selected_button(ta);
    switch (id) {
        case 0:
            switch_screen(SCREEN_ID_DISCO_MODE);
            break;
        case 1:
            switch_screen(SCREEN_ID_MENU_GENERAL);
            break;
        case 2:
            switch_screen(SCREEN_ID_MANUAL_CONTROL);
            break;
        default:
            break;
    }
}



// GENERAL SETTINGS ACTIONS
void action_update_display_brightness(lv_event_t * e) {
    lv_obj_t *ta = lv_event_get_target(e);
    int32_t value = lv_slider_get_value(ta);    
    set_display_brightness((uint8_t)value);
}



// DISCO SCREEN ACTIONS
extern RGB_disco_settings_t discoSettings;

inline void action_load_screen_main(lv_event_t * e) {
    switch_screen(SCREEN_ID_MAIN);
}

void action_disco_switch(lv_event_t * e) {
    lv_obj_t *ta = lv_event_get_target(e);
    if (lv_obj_has_state(ta, LV_STATE_CHECKED)) {
        discoSettings.on = true;
    } else {
        discoSettings.on = false;
    }
}

void action_update_disco_power(lv_event_t * e) {
    lv_obj_t *ta = lv_event_get_target(e);
    int32_t value = lv_slider_get_value(ta);
    discoSettings.discoPower = value;
}

void action_update_disco_speed(lv_event_t * e) {
    lv_obj_t *ta = lv_event_get_target(e);
    int32_t value = lv_slider_get_value(ta);
    discoSettings.discoSpeed = value;
}

void action_update_disco_phase(lv_event_t * e) {
    lv_obj_t *ta = lv_event_get_target(e);
    int32_t value = lv_slider_get_value(ta);
    discoSettings.discoOffset = value;
}