#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_increment_humidity(lv_event_t * e);
extern void action_decrement_humidity(lv_event_t * e);
extern void action_increment_airflow(lv_event_t * e);
extern void action_decrement_airflow(lv_event_t * e);
extern void action_load_screen_disco(lv_event_t * e);
extern void action_disco_settings(lv_event_t * e);
extern void action_load_screen_main(lv_event_t * e);
extern void action_disco_switch(lv_event_t * e);
extern void action_update_disco_power(lv_event_t * e);
extern void action_update_disco_speed(lv_event_t * e);
extern void action_update_disco_phase(lv_event_t * e);
extern void action_load_screen_menu(lv_event_t * e);
extern void action_load_menu_button_matrix(lv_event_t * e);
extern void action_load_previous_screen(lv_event_t * e);
extern void action_update_display_brightness(lv_event_t * e);
extern void action_set_control_mode(lv_event_t * e);
extern void action_start_grow(lv_event_t * e);
extern void action_stop_grow(lv_event_t * e);
extern void action_set_output_mode(lv_event_t * e);
extern void action_load_menu_button_matrix_2(lv_event_t * e);
extern void action_load_screen_menu_2(lv_event_t * e);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/