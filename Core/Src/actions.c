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
#include "mushroom.h"
#include "shroomshed_hal.h"

#define MAX_HUMIDITY 95
#define MIN_HUMIDITY 0
#define MAX_FAN 100
#define MIN_FAN 10


// LOAD SCREEN
inline void action_load_previous_screen(lv_event_t *e) {
    load_previous_screen();
}

inline void action_load_screen_menu(lv_event_t *e) {
    loadScreen(SCREEN_ID_MENU_MAIN);
}

inline void action_load_screen_menu_2(lv_event_t *e) {
    loadScreen(SCREEN_ID_MENU_MAIN_2);
}

inline void action_load_screen_main(lv_event_t * e) {
    loadScreen(SCREEN_ID_MAIN);
}

// MAIN SCREEN ACTIONS 

void action_set_output_mode(lv_event_t * e) {
    lv_obj_t *ta = lv_event_get_target(e);
    if (lv_obj_has_state(ta, LV_STATE_CHECKED)) {
        enable_shed();
    } else {
        disable_shed();
    }
}


// MAIN MENU ACTIONS

void action_load_menu_button_matrix(lv_event_t * e) {
    lv_obj_t *ta = lv_event_get_target(e);
    uint16_t id = lv_buttonmatrix_get_selected_button(ta);
    switch (id) {
        case 0:
            loadScreen(SCREEN_ID_LIGHTING);
            break;
        case 1:
            loadScreen(SCREEN_ID_MENU_GENERAL);
            break;
        case 2:
            loadScreen(SCREEN_ID_MANUAL_CONTROL);
            break;
        case 3:
            loadScreen(SCREEN_ID_GROW_MENU);
            break;
        default:
            break;
    }
}


// MAIN MENU PAGE 2

void action_load_menu_button_matrix_2(lv_event_t * e) {
    lv_obj_t *ta = lv_event_get_target(e);
    uint16_t id = lv_buttonmatrix_get_selected_button(ta);
    switch (id) {
        case 0:
            loadScreen(SCREEN_ID_DEBUG);
            break;
        case 1:
            loadScreen(SCREEN_ID_GROW_KITS_QR);
            break;
        case 2:
            break;
        case 3:
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


// LIGHTING SCREEN ACTIONS

void action_rgb_switch(lv_event_t * e) {
    lv_obj_t *ta = lv_event_get_target(e);
    if (lv_obj_has_state(ta, LV_STATE_CHECKED)) {
        rgbSettings.enabled = true;
    } else {
        rgbSettings.enabled = false;
    }
}

void action_load_screen_static_colour(lv_event_t * e) {
    loadScreen(SCREEN_ID_SINGLE_COLOUR);
    rgbSettings.currentMode = RGB_mode_static_colour;
}

void action_load_screen_disco(lv_event_t * e) {
    loadScreen(SCREEN_ID_DISCO_MODE);
    rgbSettings.currentMode = RGB_mode_disco;
}

// SINGLE COLOUR SCREEN ACTIONS

void action_load_screen_lighting(lv_event_t *e) {
    loadScreen(SCREEN_ID_LIGHTING);
}

void action_increase_red(lv_event_t * e) {
    if (rgbSettings.staticRed < 10) {
        rgbSettings.staticRed++;
    }
}

void action_decrease_red(lv_event_t * e) {
    if (rgbSettings.staticRed > 0) {
        rgbSettings.staticRed--;
    }
}

void action_increase_green(lv_event_t * e) {
    if (rgbSettings.staticGreen < 10) {
        rgbSettings.staticGreen++;
    }
}

void action_decrease_green(lv_event_t * e) {
    if (rgbSettings.staticGreen > 0) {
        rgbSettings.staticGreen--;
    }
}

void action_increase_blue(lv_event_t * e) {
    if (rgbSettings.staticBlue < 10) {
        rgbSettings.staticBlue++;
    }
}

void action_decrease_blue(lv_event_t * e) {
    if (rgbSettings.staticBlue > 0) {
        rgbSettings.staticBlue--;
    }
}



// DISCO SCREEN ACTIONS

void action_update_disco_power(lv_event_t * e) {
    lv_obj_t *ta = lv_event_get_target(e);
    int32_t value = lv_slider_get_value(ta);
    rgbSettings.discoPower = value;
}

void action_update_disco_speed(lv_event_t * e) {
    lv_obj_t *ta = lv_event_get_target(e);
    int32_t value = lv_slider_get_value(ta);
    rgbSettings.discoSpeed = value;
}

void action_update_disco_phase(lv_event_t * e) {
    lv_obj_t *ta = lv_event_get_target(e);
    int32_t value = lv_slider_get_value(ta);
    rgbSettings.discoOffset = value;
}

// MANUAL CONTROL ACTIONS
void action_increment_humidity(lv_event_t *e) {
    uint8_t step = (uint8_t)(uintptr_t)lv_event_get_user_data(e);
    shedControl.manualHumidityControlValue += step;
    if (shedControl.manualHumidityControlValue > MAX_HUMIDITY) {
        shedControl.manualHumidityControlValue = MAX_HUMIDITY;
    } else {
        //save_settings();
    }
}

void action_decrement_humidity(lv_event_t * e) {
    uint8_t step = (uint8_t)(uintptr_t)lv_event_get_user_data(e);
    shedControl.manualHumidityControlValue -= step;
    if (shedControl.manualHumidityControlValue < MIN_HUMIDITY) {
        shedControl.manualHumidityControlValue = MIN_HUMIDITY;
    } else {
        //save_settings();
    }
}

void action_increment_airflow(lv_event_t * e) {
    shedControl.manualFanControlValue += 5;
    if (shedControl.manualFanControlValue > MAX_FAN) {
        shedControl.manualFanControlValue = MAX_FAN;
    } else {
        //save_settings();
    }

}

void action_decrement_airflow(lv_event_t *e) {
    shedControl.manualFanControlValue -= 5;
    if (shedControl.manualFanControlValue < MIN_FAN) {
        shedControl.manualFanControlValue = MIN_FAN;
    } else {
        //save_settings();
    }
}

void action_set_control_mode(lv_event_t * e) {
    lv_obj_t *ta = lv_event_get_target(e);
    if (lv_obj_has_state(ta, LV_STATE_CHECKED)) {
        shedControl.controlMode = MODE_MANUAL;
    } else {
        shedControl.controlMode = MODE_AUTOMATIC;
    }
}


// GROW MENU ACTIONS
void action_start_grow(lv_event_t *e) {
    uint8_t index = (uint8_t)get_var_mushroom_list_index();
    start_grow(index);
    loadScreen(SCREEN_ID_MAIN);
}
