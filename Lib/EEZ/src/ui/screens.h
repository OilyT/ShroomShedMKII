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
    lv_obj_t *menu_main;
    lv_obj_t *menu_general;
    lv_obj_t *manual_control;
    lv_obj_t *grow_menu;
    lv_obj_t *humidity_bar;
    lv_obj_t *humidity_value_label;
    lv_obj_t *humidity_label;
    lv_obj_t *humidity_scale;
    lv_obj_t *airflow_scale;
    lv_obj_t *airflow_bar;
    lv_obj_t *airflow_label;
    lv_obj_t *airflow_value_label;
    lv_obj_t *temperature_scale;
    lv_obj_t *temperature_bar;
    lv_obj_t *temperature_label;
    lv_obj_t *temperature_value_label;
    lv_obj_t *menu_button;
    lv_obj_t *home_button;
    lv_obj_t *disco_power_slider;
    lv_obj_t *disco_power;
    lv_obj_t *disco_mode_label;
    lv_obj_t *disco_switch;
    lv_obj_t *disco_speed;
    lv_obj_t *disco_power_slider_1;
    lv_obj_t *disco_phase;
    lv_obj_t *disco_power_slider_2;
    lv_obj_t *main_menu_header;
    lv_obj_t *menu_buttons;
    lv_obj_t *back_button;
    lv_obj_t *back_button_1;
    lv_obj_t *display_brightness_slider;
    lv_obj_t *manual_control_header;
    lv_obj_t *back_button_2;
    lv_obj_t *manual_control_switch;
    lv_obj_t *humidity_control_container;
    lv_obj_t *manual_humidity_label;
    lv_obj_t *humidity_value_label_1;
    lv_obj_t *dec_humidity_cv;
    lv_obj_t *dec_humidity_cv_label;
    lv_obj_t *incr_humidity_cv;
    lv_obj_t *incr_humidity_cv_label;
    lv_obj_t *humidity_control_container_1;
    lv_obj_t *airflow_value_label_1;
    lv_obj_t *manual_airflow_label;
    lv_obj_t *dec_airflow;
    lv_obj_t *dec_humidity_cv_label_1;
    lv_obj_t *incr_airflow;
    lv_obj_t *incr_humidity_cv_label_1;
    lv_obj_t *back_button_3;
    lv_obj_t *mushroom_roller;
    lv_obj_t *start_grow_button;
    lv_obj_t *start_grow_button_label;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_SPLASH_SCREEN = 1,
    SCREEN_ID_MAIN = 2,
    SCREEN_ID_DISCO_MODE = 3,
    SCREEN_ID_MENU_MAIN = 4,
    SCREEN_ID_MENU_GENERAL = 5,
    SCREEN_ID_MANUAL_CONTROL = 6,
    SCREEN_ID_GROW_MENU = 7,
};

void create_screen_splash_screen();
void tick_screen_splash_screen();

void create_screen_main();
void tick_screen_main();

void create_screen_disco_mode();
void tick_screen_disco_mode();

void create_screen_menu_main();
void tick_screen_menu_main();

void create_screen_menu_general();
void tick_screen_menu_general();

void create_screen_manual_control();
void tick_screen_manual_control();

void create_screen_grow_menu();
void tick_screen_grow_menu();

enum Themes {
    THEME_ID_DEFAULT,
};
enum Colors {
    COLOR_ID_TEAL_1,
    COLOR_ID_DARK_GREY,
    COLOR_ID_BLACK,
    COLOR_ID_DARK_BLUE,
    COLOR_ID_LIGHT_GREEN,
    COLOR_ID_RED,
    COLOR_ID_WHITE,
};
void change_color_theme(uint32_t themeIndex);
extern uint32_t theme_colors[1][7];
extern uint32_t active_theme_index;

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/