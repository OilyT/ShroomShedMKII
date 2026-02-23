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


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/