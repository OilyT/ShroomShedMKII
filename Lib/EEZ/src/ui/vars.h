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
    FLOW_GLOBAL_VARIABLE_HUMIDITY_DISPLAY_STR = 1,
    FLOW_GLOBAL_VARIABLE_AIRFLOW_STRING = 2,
    FLOW_GLOBAL_VARIABLE_AIRFLOW_INT = 3,
    FLOW_GLOBAL_VARIABLE_TEMPERATURE_FP = 4,
    FLOW_GLOBAL_VARIABLE_TEMPERATURE_STR = 5,
    FLOW_GLOBAL_VARIABLE_DISCO_POWER_INT = 6,
    FLOW_GLOBAL_VARIABLE_DISCO_SPEED_INT = 7,
    FLOW_GLOBAL_VARIABLE_DISCO_PHASE_INT = 8,
    FLOW_GLOBAL_VARIABLE_DISPLAY_BRIGHTNESS = 9,
    FLOW_GLOBAL_VARIABLE_MUSHROOM_NAMES_LIST = 10,
    FLOW_GLOBAL_VARIABLE_MUSHROOM_LIST_INDEX = 11
};

// Native global variables

extern float get_var_humidity_fp();
extern void set_var_humidity_fp(float value);
extern const char *get_var_humidity_display_str();
extern void set_var_humidity_display_str(const char *value);
extern const char *get_var_airflow_string();
extern void set_var_airflow_string(const char *value);
extern int32_t get_var_airflow_int();
extern void set_var_airflow_int(int32_t value);
extern float get_var_temperature_fp();
extern void set_var_temperature_fp(float value);
extern const char *get_var_temperature_str();
extern void set_var_temperature_str(const char *value);
extern int32_t get_var_disco_power_int();
extern void set_var_disco_power_int(int32_t value);
extern int32_t get_var_disco_speed_int();
extern void set_var_disco_speed_int(int32_t value);
extern int32_t get_var_disco_phase_int();
extern void set_var_disco_phase_int(int32_t value);
extern int32_t get_var_display_brightness();
extern void set_var_display_brightness(int32_t value);
extern const char *get_var_mushroom_names_list();
extern void set_var_mushroom_names_list(const char *value);
extern int32_t get_var_mushroom_list_index();
extern void set_var_mushroom_list_index(int32_t value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/