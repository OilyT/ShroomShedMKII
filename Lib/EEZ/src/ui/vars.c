#include "vars.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>

float display_humidity = 0;
float display_temperature = 0;
int32_t display_airflow_int = 50;
char display_airflow_string[10] = { 0 };

float get_var_display_humidity() {
    return display_humidity;
}

void set_var_display_humidity(float value) {
    display_humidity = value;
}

float get_var_display_temperature() {
    return display_temperature;
}

void set_var_display_temperature(float value) {
    display_temperature = value;
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
