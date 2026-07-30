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

int compareRollerOptions(lv_roller_t *roller, const char *new_val, const char *cur_val, lv_roller_mode_t mode) {
    (void)(mode);

    uint32_t new_option_count = 1;

    for (int i = 0; ; i++) {
        if (new_val[i] == '\0') {
            if (cur_val[i] != '\0' && cur_val[i] != '\n') {
                return 1;
            }
            break;
        }

        if (new_val[i] != cur_val[i]) {
            return 1;
        }
 
        if (new_val[i] == '\n') {
            new_option_count++;
        }
    }

#if LVGL_VERSION_MAJOR >= 9
    return lv_roller_get_option_count((const lv_obj_t *)roller) == new_option_count ? 0 : 1;    
#else
    return lv_roller_get_option_cnt((const lv_obj_t *)roller) == new_option_count ? 0 : 1;    
#endif
}

static void event_handler_cb_main_grow_progress_bar(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
}

static void event_handler_cb_main_mushroom_label(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
}

static void event_handler_cb_main_output_mode_switch(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            set_var_shed_output_normal(value);
        }
    }
}

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

static void event_handler_cb_manual_control_manual_control_switch(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            set_var_shed_manual_mode(value);
        }
    }
}

static void event_handler_cb_grow_menu_mushroom_roller(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_roller_get_selected(ta);
            set_var_mushroom_list_index(value);
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
            // menu_button
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.menu_button = obj;
            lv_obj_set_pos(obj, 210, 0);
            lv_obj_set_size(obj, 110, 50);
            lv_obj_add_event_cb(obj, action_load_screen_menu, LV_EVENT_PRESSED, (void *)0);
            add_style_std_button_dark(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_button_label_32(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Menu");
                }
            }
        }
        {
            // humidity_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.humidity_label = obj;
            lv_obj_set_pos(obj, 0, 8);
            lv_obj_set_size(obj, 46, LV_SIZE_CONTENT);
            add_style_std_label_24(obj);
            lv_label_set_text(obj, "H");
        }
        {
            // humidity_bar
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.humidity_bar = obj;
            lv_obj_set_pos(obj, 44, 8);
            lv_obj_set_size(obj, 156, 32);
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
            {
                lv_obj_t *parent_obj = obj;
                {
                    // humidity_value_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.humidity_value_label = obj;
                    lv_obj_set_pos(obj, 15, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_std_label_24(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            // airflow_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.airflow_label = obj;
            lv_obj_set_pos(obj, 1, 43);
            lv_obj_set_size(obj, 43, LV_SIZE_CONTENT);
            add_style_std_label_24(obj);
            lv_label_set_text(obj, "Air");
        }
        {
            // airflow_bar
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.airflow_bar = obj;
            lv_obj_set_pos(obj, 44, 43);
            lv_obj_set_size(obj, 156, 32);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_max_width(obj, 536870911, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff00c000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff11c8da), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 2, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_BOTTOM|LV_BORDER_SIDE_TOP|LV_BORDER_SIDE_LEFT, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff11c8da), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // airflow_value_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.airflow_value_label = obj;
                    lv_obj_set_pos(obj, 51, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_std_label_24(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_align(obj, LV_ALIGN_OUT_LEFT_MID, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            // temperature_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.temperature_label = obj;
            lv_obj_set_pos(obj, 1, 83);
            lv_obj_set_size(obj, 43, LV_SIZE_CONTENT);
            add_style_std_label_24(obj);
            lv_label_set_text(obj, "T");
        }
        {
            // temperature_bar
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.temperature_bar = obj;
            lv_obj_set_pos(obj, 44, 83);
            lv_obj_set_size(obj, 156, 29);
            lv_bar_set_range(obj, 0, 35);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_max_width(obj, 536870911, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0000ff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff11c8da), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 2, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_BOTTOM|LV_BORDER_SIDE_TOP|LV_BORDER_SIDE_LEFT, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_HOR, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xffff0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff11c8da), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // Temperature_value_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.temperature_value_label = obj;
                    lv_obj_set_pos(obj, 50, -2);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_std_label_24(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            // grow_progress_bar
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.grow_progress_bar = obj;
            lv_obj_set_pos(obj, 8, 191);
            lv_obj_set_size(obj, 304, 29);
            lv_obj_add_event_cb(obj, event_handler_cb_main_grow_progress_bar, LV_EVENT_ALL, 0);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_max_width(obj, 536870911, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffa700ff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff11c8da), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 2, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_BOTTOM|LV_BORDER_SIDE_TOP|LV_BORDER_SIDE_LEFT, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(0xff11c8da), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // grow_progres_value_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.grow_progres_value_label = obj;
                    lv_obj_set_pos(obj, 111, -2);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_std_label_24(obj);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "");
                }
            }
        }
        {
            // mushroom_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.mushroom_label = obj;
            lv_obj_set_pos(obj, 85, 154);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_add_event_cb(obj, event_handler_cb_main_mushroom_label, LV_EVENT_ALL, 0);
            add_style_std_label_32(obj);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 0, 220);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_std_label_24(obj);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "ShroomOS                                                 V0.2");
        }
        {
            // Manual_indicatorr
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.manual_indicatorr = obj;
            lv_obj_set_pos(obj, 237, 132);
            lv_obj_set_size(obj, 41, LV_SIZE_CONTENT);
            add_style_shroom_shed_header(obj);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "M");
        }
        {
            // Auto_indicator
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.auto_indicator = obj;
            lv_obj_set_pos(obj, 237, 132);
            lv_obj_set_size(obj, 41, LV_SIZE_CONTENT);
            add_style_shroom_shed_header(obj);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "A");
        }
        {
            // output_mode_switch
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.output_mode_switch = obj;
            lv_obj_set_pos(obj, 218, 58);
            lv_obj_set_size(obj, 79, 54);
            lv_obj_add_event_cb(obj, action_set_output_mode, LV_EVENT_CLICKED, (void *)0);
            lv_obj_add_event_cb(obj, event_handler_cb_main_output_mode_switch, LV_EVENT_ALL, 0);
            add_style_std_switch(obj);
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
    {
        bool new_val = get_var_shed_manual_mode();
        bool cur_val = lv_obj_has_state(objects.grow_progress_bar, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.grow_progress_bar;
            if (new_val) lv_obj_add_state(objects.grow_progress_bar, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.grow_progress_bar, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_shed_manual_mode();
        bool cur_val = lv_obj_has_flag(objects.grow_progress_bar, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.grow_progress_bar;
            if (new_val) lv_obj_add_flag(objects.grow_progress_bar, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.grow_progress_bar, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_grow_progress_int();
        int32_t cur_val = lv_bar_get_value(objects.grow_progress_bar);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.grow_progress_bar;
            lv_bar_set_value(objects.grow_progress_bar, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_grow_progress_str();
        const char *cur_val = lv_label_get_text(objects.grow_progres_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.grow_progres_value_label;
            lv_label_set_text(objects.grow_progres_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_shed_manual_mode();
        bool cur_val = lv_obj_has_state(objects.mushroom_label, LV_STATE_DISABLED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.mushroom_label;
            if (new_val) lv_obj_add_state(objects.mushroom_label, LV_STATE_DISABLED);
            else lv_obj_clear_state(objects.mushroom_label, LV_STATE_DISABLED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_shed_manual_mode();
        bool cur_val = lv_obj_has_flag(objects.mushroom_label, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.mushroom_label;
            if (new_val) lv_obj_add_flag(objects.mushroom_label, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.mushroom_label, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_mushroom_grow_label();
        const char *cur_val = lv_label_get_text(objects.mushroom_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.mushroom_label;
            lv_label_set_text(objects.mushroom_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_shed_auto_mode();
        bool cur_val = lv_obj_has_flag(objects.manual_indicatorr, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.manual_indicatorr;
            if (new_val) lv_obj_add_flag(objects.manual_indicatorr, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.manual_indicatorr, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_shed_manual_mode();
        bool cur_val = lv_obj_has_flag(objects.auto_indicator, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.auto_indicator;
            if (new_val) lv_obj_add_flag(objects.auto_indicator, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.auto_indicator, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_shed_output_normal();
        bool cur_val = lv_obj_has_state(objects.output_mode_switch, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.output_mode_switch;
            if (new_val) lv_obj_add_state(objects.output_mode_switch, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.output_mode_switch, LV_STATE_CHECKED);
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
                    lv_obj_set_pos(obj, 8, -3);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_button_label_32(obj);
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
            add_style_std_label_24(obj);
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
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_std_switch(obj);
        }
        {
            // disco_speed
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.disco_speed = obj;
            lv_obj_set_pos(obj, 122, 122);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_std_label_24(obj);
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
            add_style_std_label_24(obj);
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
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // main_menu_header_2
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.main_menu_header_2 = obj;
            lv_obj_set_pos(obj, 111, 5);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_shroom_shed_header(obj);
            lv_label_set_text(obj, "Menu");
        }
        {
            // menu_buttons_2
            lv_obj_t *obj = lv_buttonmatrix_create(parent_obj);
            objects.menu_buttons_2 = obj;
            lv_obj_set_pos(obj, 0, 54);
            lv_obj_set_size(obj, LV_PCT(100), LV_PCT(60));
            static const char *map[6] = {
                "DISCO MODE",
                "General Settings",
                "\n",
                "Manual Controls",
                "Grow",
                NULL,
            };
            lv_buttonmatrix_set_map(obj, map);
            lv_obj_add_event_cb(obj, action_load_menu_button_matrix, LV_EVENT_PRESSED, (void *)0);
            add_style_std_button_matrix_dark(obj);
        }
        {
            // back_button_4
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.back_button_4 = obj;
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
                    add_style_button_label_32(obj);
                    lv_label_set_text(obj, "<");
                }
            }
        }
        {
            // next_button
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.next_button = obj;
            lv_obj_set_pos(obj, 256, 0);
            lv_obj_set_size(obj, LV_PCT(20), LV_PCT(20));
            lv_obj_add_event_cb(obj, action_load_screen_menu_2, LV_EVENT_PRESSED, (void *)0);
            add_style_std_button_dark(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 8, -3);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_button_label_32(obj);
                    lv_label_set_text(obj, ">");
                }
            }
        }
        {
            // home_button__3
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.home_button__3 = obj;
            lv_obj_set_pos(obj, 131, 201);
            lv_obj_set_size(obj, 60, 40);
            lv_obj_add_event_cb(obj, action_load_screen_main, LV_EVENT_PRESSED, (void *)0);
            add_style_std_button(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // home_button_label_3
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.home_button_label_3 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "HOME");
                }
            }
        }
    }
    
    tick_screen_menu_main();
}

void tick_screen_menu_main() {
}

void create_screen_menu_main_2() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.menu_main_2 = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // main_menu_header
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.main_menu_header = obj;
            lv_obj_set_pos(obj, 111, 5);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_shroom_shed_header(obj);
            lv_label_set_text(obj, "Menu");
        }
        {
            // menu_buttons
            lv_obj_t *obj = lv_buttonmatrix_create(parent_obj);
            objects.menu_buttons = obj;
            lv_obj_set_pos(obj, 0, 54);
            lv_obj_set_size(obj, LV_PCT(100), LV_PCT(60));
            static const char *map[6] = {
                "DEBUG",
                "Get Grow Kits",
                "\n",
                "placeholder",
                "placeholder",
                NULL,
            };
            lv_buttonmatrix_set_map(obj, map);
            lv_obj_add_event_cb(obj, action_load_menu_button_matrix_2, LV_EVENT_PRESSED, (void *)0);
            add_style_std_button_matrix_dark(obj);
        }
        {
            // back_button
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.back_button = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_PCT(20), LV_PCT(20));
            lv_obj_add_event_cb(obj, action_load_screen_menu, LV_EVENT_PRESSED, (void *)0);
            add_style_std_button_dark(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 8, -3);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_button_label_32(obj);
                    lv_label_set_text(obj, "<");
                }
            }
        }
        {
            // home_button__4
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.home_button__4 = obj;
            lv_obj_set_pos(obj, 131, 201);
            lv_obj_set_size(obj, 60, 40);
            lv_obj_add_event_cb(obj, action_load_screen_main, LV_EVENT_PRESSED, (void *)0);
            add_style_std_button(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // home_button_label_4
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.home_button_label_4 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "HOME");
                }
            }
        }
    }
    
    tick_screen_menu_main_2();
}

void tick_screen_menu_main_2() {
}

void create_screen_menu_general() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.menu_general = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
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
                    add_style_button_label_32(obj);
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
            add_style_std_label_24(obj);
            lv_label_set_text(obj, "Display Brightness");
        }
        {
            // home_button__2
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.home_button__2 = obj;
            lv_obj_set_pos(obj, 130, 200);
            lv_obj_set_size(obj, 60, 40);
            lv_obj_add_event_cb(obj, action_load_screen_main, LV_EVENT_PRESSED, (void *)0);
            add_style_std_button(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // home_button_label_2
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.home_button_label_2 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "HOME");
                }
            }
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

void create_screen_manual_control() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.manual_control = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_SNAPPABLE|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // manual_control_header
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.manual_control_header = obj;
            lv_obj_set_pos(obj, 96, 5);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_shroom_shed_header(obj);
            lv_label_set_text(obj, "Manual");
        }
        {
            // back_button_2
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.back_button_2 = obj;
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
                    add_style_button_label_32(obj);
                    lv_label_set_text(obj, "<");
                }
            }
        }
        {
            // manual_control_switch
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.manual_control_switch = obj;
            lv_obj_set_pos(obj, 242, 5);
            lv_obj_set_size(obj, 60, 40);
            lv_obj_add_event_cb(obj, action_set_control_mode, LV_EVENT_CLICKED, (void *)0);
            lv_obj_add_event_cb(obj, event_handler_cb_manual_control_manual_control_switch, LV_EVENT_ALL, 0);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_std_switch(obj);
        }
        {
            // humidity_control_container
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.humidity_control_container = obj;
            lv_obj_set_pos(obj, 0, 51);
            lv_obj_set_size(obj, 320, 78);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            add_style_blue_container(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // manual_humidity_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.manual_humidity_label = obj;
                    lv_obj_set_pos(obj, 26, 10);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_std_label_24(obj);
                    lv_label_set_text(obj, "Humidity");
                }
                {
                    // humidity_value_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.humidity_value_label_1 = obj;
                    lv_obj_set_pos(obj, 20, 42);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
                    add_style_std_label_24(obj);
                    lv_label_set_text(obj, "");
                }
                {
                    // dec_humidity_cv
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.dec_humidity_cv = obj;
                    lv_obj_set_pos(obj, 156, 17);
                    lv_obj_set_size(obj, 65, 50);
                    lv_obj_add_event_cb(obj, action_decrement_humidity, LV_EVENT_PRESSED, (void *)1);
                    lv_obj_add_event_cb(obj, action_decrement_humidity, LV_EVENT_LONG_PRESSED, (void *)9);
                    add_style_std_button_dark(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dec_humidity_cv_label
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dec_humidity_cv_label = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_button_label_48(obj);
                            lv_label_set_text(obj, "-");
                        }
                    }
                }
                {
                    // incr_humidity_cv
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.incr_humidity_cv = obj;
                    lv_obj_set_pos(obj, 238, 17);
                    lv_obj_set_size(obj, 65, 50);
                    lv_obj_add_event_cb(obj, action_increment_humidity, LV_EVENT_PRESSED, (void *)1);
                    lv_obj_add_event_cb(obj, action_increment_humidity, LV_EVENT_LONG_PRESSED, (void *)9);
                    add_style_std_button_dark(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // incr_humidity_cv_label
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.incr_humidity_cv_label = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_button_label_48(obj);
                            lv_label_set_text(obj, "+");
                        }
                    }
                }
            }
        }
        {
            // airflow_container
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.airflow_container = obj;
            lv_obj_set_pos(obj, 0, 129);
            lv_obj_set_size(obj, 320, 79);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            add_style_blue_container(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // airflow_value_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.airflow_value_label_1 = obj;
                    lv_obj_set_pos(obj, 50, 29);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_button_label_32(obj);
                    lv_label_set_text(obj, "");
                }
                {
                    // manual_airflow_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.manual_airflow_label = obj;
                    lv_obj_set_pos(obj, 32, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_std_label_24(obj);
                    lv_label_set_text(obj, "Airflow");
                }
                {
                    // dec_airflow
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.dec_airflow = obj;
                    lv_obj_set_pos(obj, 156, 4);
                    lv_obj_set_size(obj, 65, 50);
                    lv_obj_add_event_cb(obj, action_decrement_airflow, LV_EVENT_PRESSED, (void *)1);
                    lv_obj_add_event_cb(obj, action_decrement_airflow, LV_EVENT_LONG_PRESSED, (void *)9);
                    add_style_std_button_dark(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // dec_humidity_cv_label_1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.dec_humidity_cv_label_1 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_button_label_48(obj);
                            lv_label_set_text(obj, "-");
                        }
                    }
                }
                {
                    // incr_airflow
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.incr_airflow = obj;
                    lv_obj_set_pos(obj, 238, 4);
                    lv_obj_set_size(obj, 65, 50);
                    lv_obj_add_event_cb(obj, action_increment_airflow, LV_EVENT_PRESSED, (void *)1);
                    lv_obj_add_event_cb(obj, action_increment_airflow, LV_EVENT_LONG_PRESSED, (void *)9);
                    add_style_std_button_dark(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            // incr_humidity_cv_label_1
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.incr_humidity_cv_label_1 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            add_style_button_label_48(obj);
                            lv_label_set_text(obj, "+");
                        }
                    }
                }
            }
        }
        {
            // home_button__5
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.home_button__5 = obj;
            lv_obj_set_pos(obj, 130, 201);
            lv_obj_set_size(obj, 60, 40);
            lv_obj_add_event_cb(obj, action_load_screen_main, LV_EVENT_PRESSED, (void *)0);
            add_style_std_button(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // home_button_label_5
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.home_button_label_5 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "HOME");
                }
            }
        }
    }
    
    tick_screen_manual_control();
}

void tick_screen_manual_control() {
    {
        bool new_val = get_var_shed_manual_mode();
        bool cur_val = lv_obj_has_state(objects.manual_control_switch, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.manual_control_switch;
            if (new_val) lv_obj_add_state(objects.manual_control_switch, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.manual_control_switch, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_manual_humidity_str();
        const char *cur_val = lv_label_get_text(objects.humidity_value_label_1);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.humidity_value_label_1;
            lv_label_set_text(objects.humidity_value_label_1, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_manual_airflow_str();
        const char *cur_val = lv_label_get_text(objects.airflow_value_label_1);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.airflow_value_label_1;
            lv_label_set_text(objects.airflow_value_label_1, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_grow_menu() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.grow_menu = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_SNAPPABLE|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER);
    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // back_button_3
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.back_button_3 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_PCT(20), LV_PCT(20));
            lv_obj_add_event_cb(obj, action_load_screen_menu, LV_EVENT_PRESSED, (void *)0);
            add_style_std_button_dark(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 8, -3);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_button_label_32(obj);
                    lv_label_set_text(obj, "<");
                }
            }
        }
        {
            // mushroom_roller
            lv_obj_t *obj = lv_roller_create(parent_obj);
            objects.mushroom_roller = obj;
            lv_obj_set_pos(obj, 0, 84);
            lv_obj_set_size(obj, LV_PCT(100), LV_PCT(65));
            lv_roller_set_options(obj, "", LV_ROLLER_MODE_NORMAL);
            lv_obj_add_event_cb(obj, event_handler_cb_grow_menu_mushroom_roller, LV_EVENT_ALL, 0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][1]), LV_PART_SELECTED | LV_STATE_DEFAULT);
            lv_obj_set_style_border_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_SELECTED | LV_STATE_DEFAULT);
            lv_obj_set_style_border_opa(obj, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 4, LV_PART_SELECTED | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_SELECTED | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][0]), LV_PART_SELECTED | LV_STATE_DEFAULT);
        }
        {
            // Start_grow_button
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.start_grow_button = obj;
            lv_obj_set_pos(obj, 118, 10);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_start_grow, LV_EVENT_CLICKED, (void *)0);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_std_button(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // start_grow_button_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.start_grow_button_label = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_button_label_32(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Start");
                }
            }
        }
        {
            // stop_grow_button
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.stop_grow_button = obj;
            lv_obj_set_pos(obj, 118, 10);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_stop_grow, LV_EVENT_CLICKED, (void *)0);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_ON_FOCUS|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_std_button(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // stop_grow_button_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.stop_grow_button_label = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_button_label_32(obj);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(theme_colors[active_theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Stop");
                }
            }
        }
    }
    
    tick_screen_grow_menu();
}

void tick_screen_grow_menu() {
    {
        const char *new_val = get_var_mushroom_names_list();
        const char *cur_val = lv_roller_get_options(objects.mushroom_roller);
        if (compareRollerOptions((lv_roller_t *)objects.mushroom_roller, new_val, cur_val, LV_ROLLER_MODE_NORMAL) != 0) {
            tick_value_change_obj = objects.mushroom_roller;
            lv_roller_set_options(objects.mushroom_roller, new_val, LV_ROLLER_MODE_NORMAL);
            tick_value_change_obj = NULL;
        }
    }
    {
        if (!(lv_obj_get_state(objects.mushroom_roller) & LV_STATE_EDITED)) {
            int32_t new_val = get_var_mushroom_list_index();
            int32_t cur_val = lv_roller_get_selected(objects.mushroom_roller);
            if (new_val != cur_val) {
                tick_value_change_obj = objects.mushroom_roller;
                lv_roller_set_selected(objects.mushroom_roller, new_val, LV_ANIM_OFF);
                tick_value_change_obj = NULL;
            }
        }
    }
    {
        bool new_val = get_var_shed_auto_mode();
        bool cur_val = lv_obj_has_flag(objects.start_grow_button, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.start_grow_button;
            if (new_val) lv_obj_add_flag(objects.start_grow_button, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.start_grow_button, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_shed_manual_mode();
        bool cur_val = lv_obj_has_flag(objects.stop_grow_button, LV_OBJ_FLAG_HIDDEN);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.stop_grow_button;
            if (new_val) lv_obj_add_flag(objects.stop_grow_button, LV_OBJ_FLAG_HIDDEN);
            else lv_obj_clear_flag(objects.stop_grow_button, LV_OBJ_FLAG_HIDDEN);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_debug() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.debug = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // h_pid_p_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.h_pid_p_label = obj;
            lv_obj_set_pos(obj, 42, 58);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_std_label_32(obj);
            lv_label_set_text(obj, "");
        }
        {
            // back_button_5
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.back_button_5 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_PCT(20), LV_PCT(20));
            lv_obj_add_event_cb(obj, action_load_screen_menu_2, LV_EVENT_PRESSED, (void *)0);
            add_style_std_button_dark(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 8, -3);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_button_label_32(obj);
                    lv_label_set_text(obj, "<");
                }
            }
        }
        {
            // main_menu_header_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.main_menu_header_1 = obj;
            lv_obj_set_pos(obj, 97, 0);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_shroom_shed_header(obj);
            lv_label_set_text(obj, "DEBUG");
        }
        {
            // H_PID_PREFIX_LABEL
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.h_pid_prefix_label = obj;
            lv_obj_set_pos(obj, 6, 58);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_std_label_32(obj);
            lv_label_set_text(obj, "P:\nI:\nD:\nO:");
        }
        {
            // h_pid_i_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.h_pid_i_label = obj;
            lv_obj_set_pos(obj, 43, 92);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_std_label_32(obj);
            lv_label_set_text(obj, "");
        }
        {
            // h_pid_d_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.h_pid_d_label = obj;
            lv_obj_set_pos(obj, 43, 129);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_std_label_32(obj);
            lv_label_set_text(obj, "");
        }
        {
            // h_pid_power_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.h_pid_power_label = obj;
            lv_obj_set_pos(obj, 43, 163);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_std_label_32(obj);
            lv_label_set_text(obj, "");
        }
        {
            // home_button__1
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.home_button__1 = obj;
            lv_obj_set_pos(obj, 130, 200);
            lv_obj_set_size(obj, 60, 40);
            lv_obj_add_event_cb(obj, action_load_screen_main, LV_EVENT_PRESSED, (void *)0);
            add_style_std_button(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // home_button_label_1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.home_button_label_1 = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "HOME");
                }
            }
        }
    }
    
    tick_screen_debug();
}

void tick_screen_debug() {
    {
        const char *new_val = get_var_h_pid_p();
        const char *cur_val = lv_label_get_text(objects.h_pid_p_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.h_pid_p_label;
            lv_label_set_text(objects.h_pid_p_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_h_pid_i();
        const char *cur_val = lv_label_get_text(objects.h_pid_i_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.h_pid_i_label;
            lv_label_set_text(objects.h_pid_i_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_h_pid_d();
        const char *cur_val = lv_label_get_text(objects.h_pid_d_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.h_pid_d_label;
            lv_label_set_text(objects.h_pid_d_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_h_pid_power();
        const char *cur_val = lv_label_get_text(objects.h_pid_power_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.h_pid_power_label;
            lv_label_set_text(objects.h_pid_power_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_grow_kits_qr() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.grow_kits_qr = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 320, 240);
    lv_obj_set_style_bg_color(obj, lv_color_hex(theme_colors[active_theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // back_button_6
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.back_button_6 = obj;
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, LV_PCT(20), LV_PCT(20));
            lv_obj_add_event_cb(obj, action_load_screen_menu, LV_EVENT_PRESSED, (void *)0);
            add_style_std_button_dark(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 8, -3);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    add_style_button_label_32(obj);
                    lv_label_set_text(obj, "<");
                }
            }
        }
        {
            // home_button_
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.home_button_ = obj;
            lv_obj_set_pos(obj, 130, 200);
            lv_obj_set_size(obj, 60, 40);
            lv_obj_add_event_cb(obj, action_load_screen_main, LV_EVENT_PRESSED, (void *)0);
            add_style_std_button(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // home_button_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.home_button_label = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "HOME");
                }
            }
        }
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 23, 72);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_sporeshift_kit_qr);
        }
        {
            // grow_kit_QR_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.grow_kit_qr_label = obj;
            lv_obj_set_pos(obj, 97, 7);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_shroom_shed_sub_heading(obj);
            lv_label_set_text(obj, "Sporeshift\nGrow kits");
        }
        {
            // checkout_comment_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.checkout_comment_label = obj;
            lv_obj_set_pos(obj, 150, 78);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_shroom_shed_small_label(obj);
            lv_label_set_text(obj, "Make sure to leave a\ncomment at\ncheckout saying\nOli from\nShroomShed\nsent you :)");
        }
    }
    
    tick_screen_grow_kits_qr();
}

void tick_screen_grow_kits_qr() {
}

void change_color_theme(uint32_t theme_index) {
    active_theme_index = theme_index;
    
    lv_style_set_border_color(get_style_shroom_shed_header_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    
    lv_style_set_bg_color(get_style_shroom_shed_header_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][1]));
    
    lv_style_set_outline_color(get_style_shroom_shed_sub_heading_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    
    lv_style_set_border_color(get_style_blue_container_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    
    lv_style_set_bg_color(get_style_blue_container_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][1]));
    
    lv_style_set_text_color(get_style_std_button_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][2]));
    
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
    
    lv_style_set_text_color(get_style_button_label_48_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_text_color(get_style_button_label_48_MAIN_CHECKED_PRESSED(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_text_color(get_style_button_label_32_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_text_color(get_style_button_label_32_MAIN_CHECKED_PRESSED(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_text_color(get_style_button_label_24_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_text_color(get_style_button_label_24_MAIN_CHECKED_PRESSED(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_border_color(get_style_std_switch_MAIN_DEFAULT(), lv_color_hex(theme_colors[theme_index][3]));
    
    lv_style_set_bg_color(get_style_std_switch_KNOB_DEFAULT(), lv_color_hex(theme_colors[theme_index][0]));
    
    lv_style_set_bg_color(get_style_std_switch_INDICATOR_CHECKED(), lv_color_hex(theme_colors[theme_index][4]));
    
    lv_obj_set_style_text_color(objects.humidity_value_label, lv_color_hex(theme_colors[theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.airflow_value_label, lv_color_hex(theme_colors[theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.temperature_value_label, lv_color_hex(theme_colors[theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.grow_progres_value_label, lv_color_hex(theme_colors[theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.auto_indicator, lv_color_hex(theme_colors[theme_index][4]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.menu_general, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.manual_control, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.grow_menu, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.mushroom_roller, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.mushroom_roller, lv_color_hex(theme_colors[theme_index][0]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.mushroom_roller, lv_color_hex(theme_colors[theme_index][1]), LV_PART_SELECTED | LV_STATE_DEFAULT);
    
    lv_obj_set_style_border_color(objects.mushroom_roller, lv_color_hex(theme_colors[theme_index][0]), LV_PART_SELECTED | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.mushroom_roller, lv_color_hex(theme_colors[theme_index][0]), LV_PART_SELECTED | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.start_grow_button_label, lv_color_hex(theme_colors[theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_text_color(objects.stop_grow_button_label, lv_color_hex(theme_colors[theme_index][6]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(objects.grow_kits_qr, lv_color_hex(theme_colors[theme_index][2]), LV_PART_MAIN | LV_STATE_DEFAULT);
    
    lv_obj_invalidate(objects.splash_screen);
    lv_obj_invalidate(objects.main);
    lv_obj_invalidate(objects.disco_mode);
    lv_obj_invalidate(objects.menu_main);
    lv_obj_invalidate(objects.menu_main_2);
    lv_obj_invalidate(objects.menu_general);
    lv_obj_invalidate(objects.manual_control);
    lv_obj_invalidate(objects.grow_menu);
    lv_obj_invalidate(objects.debug);
    lv_obj_invalidate(objects.grow_kits_qr);
}

uint32_t theme_colors[1][7] = {
    { 0xff00c8d2, 0xff000a0a, 0xff000000, 0xff0055ff, 0xff05ff05, 0xffff0000, 0xffffffff },
};


typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_splash_screen,
    tick_screen_main,
    tick_screen_disco_mode,
    tick_screen_menu_main,
    tick_screen_menu_main_2,
    tick_screen_menu_general,
    tick_screen_manual_control,
    tick_screen_grow_menu,
    tick_screen_debug,
    tick_screen_grow_kits_qr,
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
    create_screen_menu_main_2();
    create_screen_menu_general();
    create_screen_manual_control();
    create_screen_grow_menu();
    create_screen_debug();
    create_screen_grow_kits_qr();
}
