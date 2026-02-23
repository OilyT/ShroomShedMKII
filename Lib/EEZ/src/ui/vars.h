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
    FLOW_GLOBAL_VARIABLE_HUMIDITY_FP = 0,
    FLOW_GLOBAL_VARIABLE_TEMP_FP = 1,
    FLOW_GLOBAL_VARIABLE_AIRFLOW_STRING = 2,
    FLOW_GLOBAL_VARIABLE_AIRFLOW_INT = 3,
    FLOW_GLOBAL_VARIABLE_HUMIDITY_DISPLAY_STR = 4
};

// Native global variables

extern float get_var_humidity_fp();
extern void set_var_humidity_fp(float value);
extern float get_var_temp_fp();
extern void set_var_temp_fp(float value);
extern const char *get_var_airflow_string();
extern void set_var_airflow_string(const char *value);
extern int32_t get_var_airflow_int();
extern void set_var_airflow_int(int32_t value);
extern const char *get_var_humidity_display_str();
extern void set_var_humidity_display_str(const char *value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/