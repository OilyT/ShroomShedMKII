#include "vars.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>

float get_var_display_humidity() {
    return 95.0; // placeholder value, replace with actual humidity reading
}

void set_var_display_humidity(float value) {
    // Placeholder function, replace with actual implementation
}


float get_var_display_temperaure() {
    return 25.0; // placeholder value, replace with actual temperature reading
}

void set_var_display_temperaure(float value) {
    // Placeholder function, replace with actual implementation
}

int32_t display_airflow_int = 25;

int32_t get_var_display_airflow_int() {
    return display_airflow_int;
}

void set_var_display_airflow_int(int32_t value) {
    display_airflow_int = value;
}

char display_airflow_string[10] = { 0 };

const char *get_var_display_airflow_string() {
    sprintf(display_airflow_string, "%d%%", display_airflow_int);
    return display_airflow_string;
}

void set_var_display_airflow_string(const char *value) {
    strncpy(display_airflow_string, value, sizeof(display_airflow_string) / sizeof(char));
    display_airflow_string[sizeof(display_airflow_string) / sizeof(char) - 1] = 0;
}
