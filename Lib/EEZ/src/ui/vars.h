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
    FLOW_GLOBAL_VARIABLE_MUSHROOM_LIST_INDEX = 11,
    FLOW_GLOBAL_VARIABLE_MANUAL_HUMIDITY_STR = 12,
    FLOW_GLOBAL_VARIABLE_MANUAL_AIRFLOW_STR = 13,
    FLOW_GLOBAL_VARIABLE_GROW_PROGRESS_INT = 14,
    FLOW_GLOBAL_VARIABLE_GROW_PROGRESS_STR = 15,
    FLOW_GLOBAL_VARIABLE_MUSHROOM_GROW_LABEL = 16,
    FLOW_GLOBAL_VARIABLE_SHED_MANUAL_MODE = 17,
    FLOW_GLOBAL_VARIABLE_SHED_AUTO_MODE = 18,
    FLOW_GLOBAL_VARIABLE_GROW_STATUS = 19,
    FLOW_GLOBAL_VARIABLE_SHED_OUTPUT_NORMAL = 20,
    FLOW_GLOBAL_VARIABLE_H_PID_P = 21,
    FLOW_GLOBAL_VARIABLE_H_PID_I = 22,
    FLOW_GLOBAL_VARIABLE_H_PID_D = 23,
    FLOW_GLOBAL_VARIABLE_H_PID_POWER = 24
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
extern const char *get_var_manual_humidity_str();
extern void set_var_manual_humidity_str(const char *value);
extern const char *get_var_manual_airflow_str();
extern void set_var_manual_airflow_str(const char *value);
extern int32_t get_var_grow_progress_int();
extern void set_var_grow_progress_int(int32_t value);
extern const char *get_var_grow_progress_str();
extern void set_var_grow_progress_str(const char *value);
extern const char *get_var_mushroom_grow_label();
extern void set_var_mushroom_grow_label(const char *value);
extern bool get_var_shed_manual_mode();
extern void set_var_shed_manual_mode(bool value);
extern bool get_var_shed_auto_mode();
extern void set_var_shed_auto_mode(bool value);
extern const char *get_var_grow_status();
extern void set_var_grow_status(const char *value);
extern bool get_var_shed_output_normal();
extern void set_var_shed_output_normal(bool value);
extern const char *get_var_h_pid_p();
extern void set_var_h_pid_p(const char *value);
extern const char *get_var_h_pid_i();
extern void set_var_h_pid_i(const char *value);
extern const char *get_var_h_pid_d();
extern void set_var_h_pid_d(const char *value);
extern const char *get_var_h_pid_power();
extern void set_var_h_pid_power(const char *value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/