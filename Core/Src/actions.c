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
#include "vars.h"
#include "shroomshed.h"
#include "lvgl.h"
#include "ui.h"
#include "rgb.h"



// MAIN SCREEN ACTIONS 

void action_load_screen_disco(lv_event_t * e) {
    loadScreen(SCREEN_ID_DISCO_MODE);
}

void action_increment_humidity(lv_event_t * e) {
    shroomShed.humidityControlValue += 5;
    if (shroomShed.humidityControlValue > 100) {
        shroomShed.humidityControlValue = 100;
    }
}

void action_decrement_humidity(lv_event_t * e) {
    shroomShed.humidityControlValue -= 5;
    if (shroomShed.humidityControlValue < 30) {
        shroomShed.humidityControlValue = 30;
    }
}

void action_increment_airflow(lv_event_t * e) {
    shroomShed.fanSpeed += 5;
    if (shroomShed.fanSpeed > 100) {
        shroomShed.fanSpeed = 100;
    }

}

void action_decrement_airflow(lv_event_t *e) {
    shroomShed.fanSpeed -= 5;
    if (shroomShed.fanSpeed < 10) {
        shroomShed.fanSpeed = 10;
    }
}


// DISCO SCREEN ACTIONS
extern RGB_disco_settings_t discoSettings;

void action_load_screen_main(lv_event_t * e) {
    loadScreen(SCREEN_ID_MAIN);
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