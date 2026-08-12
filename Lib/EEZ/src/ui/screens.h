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
    lv_obj_t *menu_main_2;
    lv_obj_t *menu_general;
    lv_obj_t *manual_control;
    lv_obj_t *grow_menu;
    lv_obj_t *debug;
    lv_obj_t *grow_kits_qr;
    lv_obj_t *lighting;
    lv_obj_t *single_colour;
    lv_obj_t *grow_progress_bar;
    lv_obj_t *mushroom_label;
    lv_obj_t *output_mode_switch;
    lv_obj_t *manual_control_switch;
    lv_obj_t *menu_button;
    lv_obj_t *humidity_label;
    lv_obj_t *humidity_bar;
    lv_obj_t *humidity_value_label;
    lv_obj_t *airflow_label;
    lv_obj_t *airflow_bar;
    lv_obj_t *airflow_value_label;
    lv_obj_t *temperature_label;
    lv_obj_t *temperature_bar;
    lv_obj_t *temperature_value_label;
    lv_obj_t *grow_progres_value_label;
    lv_obj_t *manual_indicatorr;
    lv_obj_t *auto_indicator;
    lv_obj_t *home_button;
    lv_obj_t *disco_power_slider;
    lv_obj_t *disco_power;
    lv_obj_t *disco_mode_label;
    lv_obj_t *disco_speed;
    lv_obj_t *disco_power_slider_1;
    lv_obj_t *disco_phase;
    lv_obj_t *disco_power_slider_2;
    lv_obj_t *main_menu_header_2;
    lv_obj_t *menu_buttons_2;
    lv_obj_t *next_button;
    lv_obj_t *home_button__3;
    lv_obj_t *home_button_label_3;
    lv_obj_t *main_menu_header;
    lv_obj_t *menu_buttons;
    lv_obj_t *back_button;
    lv_obj_t *home_button__4;
    lv_obj_t *home_button_label_4;
    lv_obj_t *back_button_1;
    lv_obj_t *display_brightness_slider;
    lv_obj_t *home_button__2;
    lv_obj_t *home_button_label_2;
    lv_obj_t *manual_control_header;
    lv_obj_t *back_button_2;
    lv_obj_t *humidity_control_container;
    lv_obj_t *manual_humidity_label;
    lv_obj_t *humidity_value_label_1;
    lv_obj_t *dec_humidity_cv;
    lv_obj_t *dec_humidity_cv_label;
    lv_obj_t *incr_humidity_cv;
    lv_obj_t *incr_humidity_cv_label;
    lv_obj_t *airflow_container;
    lv_obj_t *airflow_value_label_1;
    lv_obj_t *manual_airflow_label;
    lv_obj_t *dec_airflow;
    lv_obj_t *dec_humidity_cv_label_1;
    lv_obj_t *incr_airflow;
    lv_obj_t *incr_humidity_cv_label_1;
    lv_obj_t *home_button__5;
    lv_obj_t *home_button_label_5;
    lv_obj_t *back_button_3;
    lv_obj_t *mushroom_roller;
    lv_obj_t *start_grow_button;
    lv_obj_t *start_grow_button_label;
    lv_obj_t *stop_grow_button;
    lv_obj_t *stop_grow_button_label;
    lv_obj_t *h_pid_p_label;
    lv_obj_t *back_button_5;
    lv_obj_t *main_menu_header_1;
    lv_obj_t *h_pid_prefix_label;
    lv_obj_t *h_pid_i_label;
    lv_obj_t *h_pid_d_label;
    lv_obj_t *h_pid_power_label;
    lv_obj_t *home_button__1;
    lv_obj_t *home_button_label_1;
    lv_obj_t *back_button_6;
    lv_obj_t *home_button_;
    lv_obj_t *home_button_label;
    lv_obj_t *grow_kit_qr_label;
    lv_obj_t *checkout_comment_label;
    lv_obj_t *back_button_4;
    lv_obj_t *lighting_label;
    lv_obj_t *home_button__6;
    lv_obj_t *home_button_label_6;
    lv_obj_t *lighting_master_switch;
    lv_obj_t *static_colour_button;
    lv_obj_t *disco_mode_button;
    lv_obj_t *home_button__7;
    lv_obj_t *home_button_label_7;
    lv_obj_t *red_value_label;
    lv_obj_t *back_button_7;
    lv_obj_t *green_value_label;
    lv_obj_t *blue_value_label;
    lv_obj_t *increase_red_button;
    lv_obj_t *increase_green_button;
    lv_obj_t *increase_blue_button;
    lv_obj_t *decrease_red_button;
    lv_obj_t *decrease_green;
    lv_obj_t *decrease_blue_button;
    lv_obj_t *single_color_header;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_SPLASH_SCREEN = 1,
    SCREEN_ID_MAIN = 2,
    SCREEN_ID_DISCO_MODE = 3,
    SCREEN_ID_MENU_MAIN = 4,
    SCREEN_ID_MENU_MAIN_2 = 5,
    SCREEN_ID_MENU_GENERAL = 6,
    SCREEN_ID_MANUAL_CONTROL = 7,
    SCREEN_ID_GROW_MENU = 8,
    SCREEN_ID_DEBUG = 9,
    SCREEN_ID_GROW_KITS_QR = 10,
    SCREEN_ID_LIGHTING = 11,
    SCREEN_ID_SINGLE_COLOUR = 12,
};

void create_screen_splash_screen();
void tick_screen_splash_screen();

void create_screen_main();
void tick_screen_main();

void create_screen_disco_mode();
void tick_screen_disco_mode();

void create_screen_menu_main();
void tick_screen_menu_main();

void create_screen_menu_main_2();
void tick_screen_menu_main_2();

void create_screen_menu_general();
void tick_screen_menu_general();

void create_screen_manual_control();
void tick_screen_manual_control();

void create_screen_grow_menu();
void tick_screen_grow_menu();

void create_screen_debug();
void tick_screen_debug();

void create_screen_grow_kits_qr();
void tick_screen_grow_kits_qr();

void create_screen_lighting();
void tick_screen_lighting();

void create_screen_single_colour();
void tick_screen_single_colour();

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