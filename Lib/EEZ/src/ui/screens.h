#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *splash_screen;
    lv_obj_t *main;
    lv_obj_t *disco_mode;
    lv_obj_t *humidity_bar;
    lv_obj_t *humidity_value_label;
    lv_obj_t *humidity_label;
    lv_obj_t *humidity_scale;
    lv_obj_t *incr_humidity;
    lv_obj_t *dec_humidity;
    lv_obj_t *airflow_scale;
    lv_obj_t *airflow_bar;
    lv_obj_t *dec_airflow;
    lv_obj_t *incr_airflow;
    lv_obj_t *airflow_label;
    lv_obj_t *airflow_value_label;
    lv_obj_t *temperature_scale;
    lv_obj_t *temperature_bar;
    lv_obj_t *temperature_label;
    lv_obj_t *temperature_value_label;
    lv_obj_t *goto_disco_screen;
    lv_obj_t *home_button;
    lv_obj_t *disco_power_slider;
    lv_obj_t *disco_power;
    lv_obj_t *disco_mode_label;
    lv_obj_t *disco_switch;
    lv_obj_t *disco_speed;
    lv_obj_t *disco_power_slider_1;
    lv_obj_t *disco_phase;
    lv_obj_t *disco_power_slider_2;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_SPLASH_SCREEN = 1,
    SCREEN_ID_MAIN = 2,
    SCREEN_ID_DISCO_MODE = 3,
};

void create_screen_splash_screen();
void tick_screen_splash_screen();

void create_screen_main();
void tick_screen_main();

void create_screen_disco_mode();
void tick_screen_disco_mode();

enum Themes {
    THEME_ID_DEFAULT,
};
enum Colors {
    COLOR_ID_DEFAULT_BUTTON,
};
void change_color_theme(uint32_t themeIndex);
extern uint32_t theme_colors[1][1];
extern uint32_t active_theme_index;

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/