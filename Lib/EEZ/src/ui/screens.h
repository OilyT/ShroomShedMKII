#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *splash_screen;
    lv_obj_t *main;
    lv_obj_t *header;
    lv_obj_t *humidity_bar;
    lv_obj_t *humidity_label;
    lv_obj_t *humidity_scale;
    lv_obj_t *temperature_label;
    lv_obj_t *temperature_bar;
    lv_obj_t *temperature_scale;
    lv_obj_t *airflow_value;
    lv_obj_t *airflow_arc;
    lv_obj_t *airflow_scale;
    lv_obj_t *airflow_label;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_SPLASH_SCREEN = 1,
    SCREEN_ID_MAIN = 2,
};

void create_screen_splash_screen();
void tick_screen_splash_screen();

void create_screen_main();
void tick_screen_main();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/