#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint32_t active_theme_index = 0;

static void event_handler_cb_disco_mode_disco_power_slider(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_disco_power_int(value);
        }
    }
}

static void event_handler_cb_disco_mode_disco_power_slider_1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_disco_speed_int(value);
        }
    }
}

static void event_handler_cb_disco_mode_disco_power_slider_2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_disco_phase_int(value);
        }
    }
}

static void event_handler_cb_menu_general_display_brightness_slider(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_display_brightness(value);
        }
    }
}

void create_screen_splash_screen() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.splash_screen = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 40, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_image_set_src(obj, &img_shroom_shed_logo_240);
        }
    }
    
    tick_screen_splash_screen();
}

void tick_screen_splash_screen() {
}

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // humidity_bar
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.humidity_bar = obj;
            lv_obj_set_pos(obj, 42, 17);
            lv_obj_set_size(obj, 131, 28);
            lv_bar_set_range(obj, 30, 100);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_max_width(obj, 536870911, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0000ff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff11c8da), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 2, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_BOTTOM|LV_BORDER_SIDE_TOP|LV_BORDER_SIDE_LEFT, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff11c8da), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // humidity_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.humidity_value_label = obj;
            lv_obj_set_pos(obj, 48, 17);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_shroom_shed_sub_heading(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // humidity_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.humidity_label = obj;
            lv_obj_set_pos(obj, -3, 17);
            lv_obj_set_size(obj, 46, LV_SIZE_CONTENT);
            add_style_shroom_shed_sub_heading(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff11c8da), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "RH");
        }
        {
            // humidity_scale
            lv_obj_t *obj = lv_scale_create(parent_obj);
            objects.humidity_scale = obj;
            lv_obj_set_pos(obj, 43, 44);
            lv_obj_set_size(obj, 130, 15);
            lv_scale_set_mode(obj, LV_SCALE_MODE_HORIZONTAL_BOTTOM);
            lv_scale_set_range(obj, 30, 100);
            lv_scale_set_total_tick_count(obj, 8);
            lv_scale_set_major_tick_every(obj, 2);
            lv_scale_set_label_show(obj, true);
            add_style_default_scale(obj);
        }
        {
            // incr_humidity
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.incr_humidity = obj;
            lv_obj_set_pos(obj, 254, 5);
            lv_obj_set_size(obj, 61, 50);
            lv_obj_add_event_cb(obj, action_increment_humidity, LV_EVENT_PRESSED, (void *)1);
            lv_obj_add_event_cb(obj, action_increment_humidity, LV_EVENT_LONG_PRESSED, (void *)9);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00c8d2), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "+");
                }
            }
        }
        {
            // dec_humidity
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.dec_humidity = obj;
            lv_obj_set_pos(obj, 181, 6);
            lv_obj_set_size(obj, 61, 50);
            lv_obj_add_event_cb(obj, action_decrement_humidity, LV_EVENT_PRESSED, (void *)1);
            lv_obj_add_event_cb(obj, action_decrement_humidity, LV_EVENT_LONG_PRESSED, (void *)9);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00c8d2), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "-");
                }
            }
        }
        {
            // airflow_scale
            lv_obj_t *obj = lv_scale_create(parent_obj);
            objects.airflow_scale = obj;
            lv_obj_set_pos(obj, 43, 105);
            lv_obj_set_size(obj, 130, 15);
            lv_scale_set_mode(obj, LV_SCALE_MODE_HORIZONTAL_BOTTOM);
            lv_scale_set_range(obj, 0, 100);
            lv_scale_set_total_tick_count(obj, 6);
            lv_scale_set_major_tick_every(obj, 2);
            lv_scale_set_label_show(obj, true);
            add_style_default_scale(obj);
        }
        {
            // airflow_bar
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.airflow_bar = obj;
            lv_obj_set_pos(obj, 42, 78);
            lv_obj_set_size(obj, 131, 28);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_max_width(obj, 536870911, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00c000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff11c8da), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 2, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_BOTTOM|LV_BORDER_SIDE_TOP|LV_BORDER_SIDE_LEFT, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff10bdd8), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // dec_airflow
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.dec_airflow = obj;
            lv_obj_set_pos(obj, 181, 69);
            lv_obj_set_size(obj, 61, 50);
            lv_obj_add_event_cb(obj, action_decrement_airflow, LV_EVENT_CLICKED, (void *)0);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00c8d2), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, -3);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "-");
                }
            }
        }
        {
            // incr_airflow
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.incr_airflow = obj;
            lv_obj_set_pos(obj, 254, 70);
            lv_obj_set_size(obj, 61, 50);
            lv_obj_add_event_cb(obj, action_increment_airflow, LV_EVENT_CLICKED, (void *)0);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00c8d2), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, -1);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "+");
                }
            }
        }
        {
            // Airflow_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.airflow_label = obj;
            lv_obj_set_pos(obj, 0, 79);
            lv_obj_set_size(obj, 43, LV_SIZE_CONTENT);
            add_style_shroom_shed_sub_heading(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff11c8da), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Air");
        }
        {
            // airflow_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.airflow_value_label = obj;
            lv_obj_set_pos(obj, 84, 79);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_shroom_shed_sub_heading(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // temperature_scale
            lv_obj_t *obj = lv_scale_create(parent_obj);
            objects.temperature_scale = obj;
            lv_obj_set_pos(obj, 43, 179);
            lv_obj_set_size(obj, 130, 15);
            lv_scale_set_mode(obj, LV_SCALE_MODE_HORIZONTAL_BOTTOM);
            lv_scale_set_range(obj, 10, 30);
            lv_scale_set_total_tick_count(obj, 9);
            lv_scale_set_major_tick_every(obj, 2);
            lv_scale_set_label_show(obj, true);
            add_style_default_scale(obj);
        }
        {
            // temperature_bar
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.temperature_bar = obj;
            lv_obj_set_pos(obj, 42, 152);
            lv_obj_set_size(obj, 131, 28);
            lv_bar_set_range(obj, 10, 30);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_max_width(obj, 536870911, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0000ff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff11c8da), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 2, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_BOTTOM|LV_BORDER_SIDE_TOP|LV_BORDER_SIDE_LEFT, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_HOR, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xffff0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_stop(obj, 222, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_main_stop(obj, 32, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff10bdd8), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // temperature_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.temperature_label = obj;
            lv_obj_set_pos(obj, 0, 153);
            lv_obj_set_size(obj, 43, LV_SIZE_CONTENT);
            add_style_shroom_shed_sub_heading(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff11c8da), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "T");
        }
        {
            // Temperature_value_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.temperature_value_label = obj;
            lv_obj_set_pos(obj, 86, 153);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_shroom_shed_sub_heading(obj);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // menu_button
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.menu_button = obj;
            lv_obj_set_pos(obj, 205, 144);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_load_screen_menu, LV_EVENT_PRESSED, (void *)0);
            add_style_std_button_dark(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Menu");
                }
            }
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
    {
        int32_t new_val = get_var_humidity_fp();
        int32_t cur_val = lv_bar_get_value(objects.humidity_bar);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.humidity_bar;
            lv_bar_set_value(objects.humidity_bar, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_humidity_display_str();
        const char *cur_val = lv_label_get_text(objects.humidity_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.humidity_value_label;
            lv_label_set_text(objects.humidity_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_airflow_int();
        int32_t cur_val = lv_bar_get_value(objects.airflow_bar);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.airflow_bar;
            lv_bar_set_value(objects.airflow_bar, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_airflow_string();
        const char *cur_val = lv_label_get_text(objects.airflow_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.airflow_value_label;
            lv_label_set_text(objects.airflow_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_temperature_fp();
        int32_t cur_val = lv_bar_get_value(objects.temperature_bar);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.temperature_bar;
            lv_bar_set_value(objects.temperature_bar, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_temperature_str();
        const char *cur_val = lv_label_get_text(objects.temperature_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.temperature_value_label;
            lv_label_set_text(objects.temperature_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_disco_mode() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.disco_mode = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // Home_button
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.home_button = obj;
            lv_obj_set_pos(obj, 1, 1);
            lv_obj_set_size(obj, 64, 48);
            lv_obj_add_event_cb(obj, action_load_previous_screen, LV_EVENT_PRESSED, (void *)0);
            add_style_std_button_dark(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 5, -6);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_shroom_shed_header(obj);
                    lv_label_set_text(obj, "<");
                }
            }
        }
        {
            // disco_power_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.disco_power_slider = obj;
            lv_obj_set_pos(obj, 25, 94);
            lv_obj_set_size(obj, 273, 17);
            lv_slider_set_range(obj, 1, 100);
            lv_obj_add_event_cb(obj, action_update_disco_power, LV_EVENT_VALUE_CHANGED, (void *)0);
            lv_obj_add_event_cb(obj, event_handler_cb_disco_mode_disco_power_slider, LV_EVENT_ALL, 0);
            add_style_disco_slider(obj);
        }
        {
            // disco_power
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.disco_power = obj;
            lv_obj_set_pos(obj, 121, 67);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_shroom_shed_sub_heading(obj);
            lv_label_set_text(obj, "Power");
        }
        {
            // Disco_mode_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.disco_mode_label = obj;
            lv_obj_set_pos(obj, 107, 12);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xff1e00ff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_color(obj, lv_color_hex(0xff00f4ff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff00fb), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff1eff00), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_outline_pad(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "DISCO");
        }
        {
            // disco_switch
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.disco_switch = obj;
            lv_obj_set_pos(obj, 243, 9);
            lv_obj_set_size(obj, 62, 38);
            lv_obj_add_event_cb(obj, action_disco_switch, LV_EVENT_CLICKED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff0000), LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 176, LV_PART_KNOB | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff1eff00), LV_PART_KNOB | LV_STATE_CHECKED);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_KNOB | LV_STATE_CHECKED);
        }
        {
            // disco_speed
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.disco_speed = obj;
            lv_obj_set_pos(obj, 122, 122);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_shroom_shed_sub_heading(obj);
            lv_label_set_text(obj, "Speed");
        }
        {
            // disco_power_slider_1
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.disco_power_slider_1 = obj;
            lv_obj_set_pos(obj, 26, 149);
            lv_obj_set_size(obj, 273, 17);
            lv_obj_add_event_cb(obj, action_update_disco_speed, LV_EVENT_VALUE_CHANGED, (void *)0);
            lv_obj_add_event_cb(obj, event_handler_cb_disco_mode_disco_power_slider_1, LV_EVENT_ALL, 0);
            add_style_disco_slider(obj);
        }
        {
            // disco_phase
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.disco_phase = obj;
            lv_obj_set_pos(obj, 123, 177);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_shroom_shed_sub_heading(obj);
            lv_label_set_text(obj, "Phase");
        }
        {
            // disco_power_slider_2
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.disco_power_slider_2 = obj;
            lv_obj_set_pos(obj, 25, 204);
            lv_obj_set_size(obj, 273, 17);
            lv_slider_set_range(obj, 0, 75);
            lv_obj_add_event_cb(obj, action_update_disco_phase, LV_EVENT_VALUE_CHANGED, (void *)0);
            lv_obj_add_event_cb(obj, event_handler_cb_disco_mode_disco_power_slider_2, LV_EVENT_ALL, 0);
            add_style_disco_slider(obj);
        }
    }
    
    tick_screen_disco_mode();
}

void tick_screen_disco_mode() {
    {
        int32_t new_val = get_var_disco_power_int();
        int32_t cur_val = lv_slider_get_value(objects.disco_power_slider);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.disco_power_slider;
            lv_slider_set_value(objects.disco_power_slider, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_disco_speed_int();
        int32_t cur_val = lv_slider_get_value(objects.disco_power_slider_1);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.disco_power_slider_1;
            lv_slider_set_value(objects.disco_power_slider_1, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_disco_phase_int();
        int32_t cur_val = lv_slider_get_value(objects.disco_power_slider_2);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.disco_power_slider_2;
            lv_slider_set_value(objects.disco_power_slider_2, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_menu_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.menu_main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // main_menu_header
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.main_menu_header = obj;
            lv_obj_set_pos(obj, 32, 0);
            lv_obj_set_size(obj, LV_PCT(80), LV_PCT(20));
            add_style_shroom_shed_header(obj);
            lv_label_set_text(obj, "Menu\n");
        }
        {
            // menu_buttons
            lv_obj_t *obj = lv_buttonmatrix_create(parent_obj);
            objects.menu_buttons = obj;
            lv_obj_set_pos(obj, 0, 50);
            lv_obj_set_size(obj, LV_PCT(100), LV_PCT(79));
            static const char *map[6] = {
                "Disco settings",
                "General Settings",
                "\n",
                "Btn",
                "Btn",
                NULL,
            };
            lv_buttonmatrix_set_map(obj, map);
            lv_obj_add_event_cb(obj, action_load_menu_button_matrix, LV_EVENT_PRESSED, (void *)0);
            add_style_std_button_matrix_dark(obj);
        }
        {
            // back_button
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.back_button = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_PCT(20), LV_PCT(20));
            lv_obj_add_event_cb(obj, action_load_screen_main, LV_EVENT_PRESSED, (void *)0);
            add_style_std_button_dark(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 8, -3);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_shroom_shed_header(obj);
                    lv_label_set_text(obj, "<");
                }
            }
        }
    }
    
    tick_screen_menu_main();
}

void tick_screen_menu_main() {
}

void create_screen_menu_general() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.menu_general = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // back_button_1
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.back_button_1 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_PCT(20), LV_PCT(20));
            lv_obj_add_event_cb(obj, action_load_previous_screen, LV_EVENT_PRESSED, (void *)0);
            add_style_std_button_dark(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 8, -3);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_shroom_shed_header(obj);
                    lv_label_set_text(obj, "<");
                }
            }
        }
        {
            // display_brightness_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.display_brightness_slider = obj;
            lv_obj_set_pos(obj, 33, 105);
            lv_obj_set_size(obj, LV_PCT(80), 15);
            lv_slider_set_range(obj, 5, 100);
            lv_obj_add_event_cb(obj, action_update_display_brightness, LV_EVENT_VALUE_CHANGED, (void *)0);
            lv_obj_add_event_cb(obj, event_handler_cb_menu_general_display_brightness_slider, LV_EVENT_ALL, 0);
            add_style_std_slider_dark(obj);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 42, 70);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_shroom_shed_sub_heading(obj);
            lv_label_set_text(obj, "Display Brightness");
        }
    }
    
    tick_screen_menu_general();
}

void tick_screen_menu_general() {
    {
        int32_t new_val = get_var_display_brightness();
        int32_t cur_val = lv_slider_get_value(objects.display_brightness_slider);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.display_brightness_slider;
            lv_slider_set_value(objects.display_brightness_slider, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
}

void change_color_theme(uint32_t theme_index) {
    active_theme_index = theme_index;
    
    lv_style_set_bg_color(get_style_std_button_dark_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][1]));
    
    lv_style_set_text_color(get_style_std_button_dark_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_border_color(get_style_std_button_dark_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_border_color(get_style_std_button_dark_MAIN_PRESSED(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_text_color(get_style_std_button_matrix_dark_ITEMS_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_bg_color(get_style_std_button_matrix_dark_ITEMS_DEFAULT(), lv_color_hex(theme_colors[theme_index][1]));
    
    lv_style_set_outline_color(get_style_std_button_matrix_dark_ITEMS_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_border_color(get_style_std_button_matrix_dark_ITEMS_PRESSED(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_bg_color(get_style_std_button_matrix_dark_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
    lv_style_set_border_color(get_style_std_button_matrix_dark_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_border_color(get_style_std_slider_dark_INDICATOR_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_border_color(get_style_std_slider_dark_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_obj_set_style_bg_color(objects.disco_switch, lv_color_hex(theme_colors[theme_index][1]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.disco_switch, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.menu_general, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_invalidate(objects.splash_screen);
    lv_obj_invalidate(objects.main);
    lv_obj_invalidate(objects.disco_mode);
    lv_obj_invalidate(objects.menu_main);
    lv_obj_invalidate(objects.menu_general);
}

uint32_t theme_colors[1][3] = {
    { 0xff00c8d2, 0xff000a0a, 0xff000000 },
};


typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_splash_screen,
    tick_screen_main,
    tick_screen_disco_mode,
    tick_screen_menu_main,
    tick_screen_menu_general,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_splash_screen();
    create_screen_main();
    create_screen_disco_mode();
    create_screen_menu_main();
    create_screen_menu_general();
}
