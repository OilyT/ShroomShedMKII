#include "vars.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "display_manager.h"
#include "shroomshed.h"
#include "rgb.h"

static float display_humidity = 40;
static float display_temperature = 20;
static int32_t display_airflow_int = 50;
char display_airflow_string[10] = { 0 };
char humidity_display_string[11] = { 0 };


// MAIN SCREEN VARS

float get_var_humidity_fp(void) {
    return display_humidity;
}

void set_var_humidity_fp(float value) {
    
    if (fabs(display_humidity - value) < 0.25) {
        display_humidity = value;
        return;
    } else {
        if (display_humidity < value) {
            display_humidity += 0.25;
            if (display_humidity > value) {
                display_humidity = value;
            }
        } else if (display_humidity > value) {
            display_humidity -= 0.25;
            if (display_humidity < value) {
                display_humidity = value;
            }
        }
    }
}

float get_var_temperature_fp() {
    return display_temperature;
}

void set_var_temperature_fp(float value) {
    if (fabs(display_temperature - value) < 0.05) {
        display_temperature = value;
        return;
    } else {
        if (display_temperature < value) {
            display_temperature += 0.05;
            if (display_temperature > value) {
                display_temperature = value;
            }
        } else if (display_temperature > value) {
            display_temperature -= 0.05;
            if (display_temperature < value) {
                display_temperature = value;
            }
        }
    }
}

const char *get_var_temperature_str() {
    static char temp_str[10];
    snprintf(temp_str, sizeof(temp_str), "%.1f°C", display_temperature);
    return temp_str;
}

int32_t get_var_airflow_int() {
    return display_airflow_int;
}

void set_var_airflow_int(int32_t value) {
    display_airflow_int = value;
}

const char *get_var_airflow_string() {
    sprintf(display_airflow_string, "%d%%", (int)display_airflow_int);
    return display_airflow_string;
}

void set_var_airflow_string(const char *value) {
    strncpy(display_airflow_string, value, sizeof(display_airflow_string) / sizeof(char));
    display_airflow_string[sizeof(display_airflow_string) / sizeof(char) - 1] = 0;
}

const char *get_var_humidity_display_str(void) {
    snprintf(humidity_display_string, sizeof(humidity_display_string),"%.1f/%d%%", display_humidity, shedControl.humidityControlValue);
    return humidity_display_string;
}

void set_var_humidity_display_str(const char *value) {
    // not used
}


// DISCO SCREEN VARS
static uint8_t disco_power = 75;
static uint8_t disco_speed = 25;
static uint8_t disco_phase = 25;


int32_t get_var_disco_power_int() {
    return disco_power;
}

void set_var_disco_power_int(int32_t value) {
    disco_power = value;
}

int32_t get_var_disco_speed_int() {
    return disco_speed;
}

void set_var_disco_speed_int(int32_t value) {
    disco_speed = value;
}

int32_t get_var_disco_phase_int() {
    return disco_phase;
}

void set_var_disco_phase_int(int32_t value) {
    disco_phase = value;
}

// GENERAL SETTINGS VARS
extern uint8_t display_brightness;

int32_t get_var_display_brightness() {
    return display_brightness;
}

void set_var_display_brightness(int32_t value) {
    display_brightness = value;
}