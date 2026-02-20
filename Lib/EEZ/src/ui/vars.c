#include "vars.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

static float display_humidity = 40;
static float display_temperature = 15;
static int32_t display_airflow_int = 50;
static char display_airflow_string[10] = { 0 };

float get_var_display_humidity() {
    return display_humidity;
}

void set_var_display_humidity(float value) {
    
    if (fabs(display_humidity - value) < 0.5) {
        display_humidity = value;
        return;
    } else {
        if (display_humidity < value) {
            display_humidity += 0.5;
            if (display_humidity > value) {
                display_humidity = value;
            }
        } else if (display_humidity > value) {
            display_humidity -= 0.5;
            if (display_humidity < value) {
                display_humidity = value;
            }
        }
    }


}

float get_var_display_temperature() {
    return display_temperature;
}

void set_var_display_temperature(float value) {
    if (fabs(display_temperature - value) < 0.5) {
        display_temperature = value;
        return;
    } else {
        if (display_temperature < value) {
            display_temperature += 0.5;
            if (display_temperature > value) {
                display_temperature = value;
            }
        } else if (display_temperature > value) {
            display_temperature -= 0.5;
            if (display_temperature < value) {
                display_temperature = value;
            }
        }
    }
}


int32_t get_var_display_airflow_int() {
    return display_airflow_int;
}

void set_var_display_airflow_int(int32_t value) {
    display_airflow_int = value;
}


const char *get_var_display_airflow_string() {
    sprintf(display_airflow_string, "%d%%", display_airflow_int);
    return display_airflow_string;
}

void set_var_display_airflow_string(const char *value) {
    strncpy(display_airflow_string, value, sizeof(display_airflow_string) / sizeof(char));
    display_airflow_string[sizeof(display_airflow_string) / sizeof(char) - 1] = 0;
}
