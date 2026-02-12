#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations



// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_DISPLAY_HUMIDITY = 0,
    FLOW_GLOBAL_VARIABLE_DISPLAY_TEMPERAURE = 1,
    FLOW_GLOBAL_VARIABLE_DISPLAY_AIRFLOW_STRING = 2,
    FLOW_GLOBAL_VARIABLE_DISPLAY_AIRFLOW_INT = 3
};

// Native global variables

extern float get_var_display_humidity();
extern void set_var_display_humidity(float value);
extern float get_var_display_temperaure();
extern void set_var_display_temperaure(float value);
extern const char *get_var_display_airflow_string();
extern void set_var_display_airflow_string(const char *value);
extern int32_t get_var_display_airflow_int();
extern void set_var_display_airflow_int(int32_t value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/