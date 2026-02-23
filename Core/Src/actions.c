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

/* Function declarations */


void action_increment_humidity(lv_event_t * e) {
    shroomShed.humidityControlvalue += 5;
    if (shroomShed.humidityControlvalue > 100) {
        shroomShed.humidityControlvalue = 100;
    }
}

void action_decrement_humidity(lv_event_t * e) {
    shroomShed.humidityControlvalue -= 5;
    if (shroomShed.humidityControlvalue < 30) {
        shroomShed.humidityControlvalue = 30;
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