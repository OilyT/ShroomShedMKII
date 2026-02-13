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

static void event_handler_cb_main_airflow_arc(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_arc_get_value(ta);
            set_var_display_airflow_int(value);
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
            lv_obj_set_pos(obj, 88, 0);
            lv_obj_set_size(obj, 240, 240);
            lv_image_set_src(obj, &img_shroom_shed_logo_240);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 8, 20);
            lv_obj_set_size(obj, 160, 70);
            add_style_shroom_shed_sub_heading(obj);
            lv_label_set_text(obj, "ShroomShed V2.1");
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
            lv_obj_set_pos(obj, 10, 27);
            lv_obj_set_size(obj, 150, 15);
            lv_bar_set_range(obj, 40, 99);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_max_width(obj, 536870911, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff0020ff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // humidity_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.humidity_label = obj;
            lv_obj_set_pos(obj, 13, 0);
            lv_obj_set_size(obj, 144, LV_SIZE_CONTENT);
            add_style_shroom_shed_sub_heading(obj);
            lv_label_set_text(obj, "Humidity %");
        }
        {
            // humidity_scale
            lv_obj_t *obj = lv_scale_create(parent_obj);
            objects.humidity_scale = obj;
            lv_obj_set_pos(obj, 10, 42);
            lv_obj_set_size(obj, 150, 15);
            lv_scale_set_mode(obj, LV_SCALE_MODE_HORIZONTAL_BOTTOM);
            lv_scale_set_range(obj, 40, 100);
            lv_scale_set_total_tick_count(obj, 7);
            lv_scale_set_major_tick_every(obj, 2);
            lv_scale_set_label_show(obj, true);
            add_style_default_scale(obj);
        }
        {
            // temperature_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.temperature_label = obj;
            lv_obj_set_pos(obj, 7, 83);
            lv_obj_set_size(obj, 150, LV_SIZE_CONTENT);
            add_style_shroom_shed_sub_heading(obj);
            lv_label_set_text(obj, "Temp C");
        }
        {
            // temperature_bar
            lv_obj_t *obj = lv_bar_create(parent_obj);
            objects.temperature_bar = obj;
            lv_obj_set_pos(obj, 10, 110);
            lv_obj_set_size(obj, 150, 15);
            lv_bar_set_range(obj, 10, 35);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            lv_obj_set_style_max_width(obj, 536870911, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff003dff), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_dir(obj, LV_GRAD_DIR_HOR, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xffff0101), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_stop(obj, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_main_stop(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // temperature_scale
            lv_obj_t *obj = lv_scale_create(parent_obj);
            objects.temperature_scale = obj;
            lv_obj_set_pos(obj, 10, 125);
            lv_obj_set_size(obj, 150, 15);
            lv_scale_set_mode(obj, LV_SCALE_MODE_HORIZONTAL_BOTTOM);
            lv_scale_set_range(obj, 10, 35);
            lv_scale_set_total_tick_count(obj, 26);
            lv_scale_set_major_tick_every(obj, 5);
            lv_scale_set_label_show(obj, true);
            add_style_default_scale(obj);
        }
        {
            // airflow_value
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.airflow_value = obj;
            lv_obj_set_pos(obj, 118, 187);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE|LV_OBJ_FLAG_GESTURE_BUBBLE|LV_OBJ_FLAG_PRESS_LOCK|LV_OBJ_FLAG_SCROLLABLE|LV_OBJ_FLAG_SCROLL_CHAIN_HOR|LV_OBJ_FLAG_SCROLL_CHAIN_VER|LV_OBJ_FLAG_SCROLL_ELASTIC|LV_OBJ_FLAG_SCROLL_MOMENTUM|LV_OBJ_FLAG_SCROLL_WITH_ARROW|LV_OBJ_FLAG_SNAPPABLE);
            add_style_shroom_shed_sub_heading(obj);
            lv_label_set_text(obj, "");
        }
        {
            // airflow_arc
            lv_obj_t *obj = lv_arc_create(parent_obj);
            objects.airflow_arc = obj;
            lv_obj_set_pos(obj, 102, 160);
            lv_obj_set_size(obj, 80, 80);
            lv_obj_add_event_cb(obj, event_handler_cb_main_airflow_arc, LV_EVENT_ALL, 0);
            lv_obj_set_style_arc_width(obj, 6, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_color(obj, lv_color_hex(0xff01ff32), LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_rounded(obj, false, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_opa(obj, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            // airflow_scale
            lv_obj_t *obj = lv_scale_create(parent_obj);
            objects.airflow_scale = obj;
            lv_obj_set_pos(obj, 102, 160);
            lv_obj_set_size(obj, 80, 80);
            lv_scale_set_mode(obj, LV_SCALE_MODE_ROUND_INNER);
            lv_scale_set_range(obj, 0, 100);
            lv_scale_set_total_tick_count(obj, 11);
            lv_scale_set_major_tick_every(obj, 2);
            lv_scale_set_label_show(obj, false);
            add_style_default_scale(obj);
            lv_obj_set_style_length(obj, 5, LV_PART_ITEMS | LV_STATE_DEFAULT);
            lv_obj_set_style_length(obj, 10, LV_PART_INDICATOR | LV_STATE_DEFAULT);
        }
        {
            // airflow_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.airflow_label = obj;
            lv_obj_set_pos(obj, 7, 187);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            add_style_shroom_shed_sub_heading(obj);
            lv_label_set_text(obj, "Airflow");
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
    {
        int32_t new_val = get_var_display_humidity();
        int32_t cur_val = lv_bar_get_value(objects.humidity_bar);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.humidity_bar;
            lv_bar_set_value(objects.humidity_bar, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_display_temperature();
        int32_t cur_val = lv_bar_get_value(objects.temperature_bar);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.temperature_bar;
            lv_bar_set_value(objects.temperature_bar, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_display_airflow_string();
        const char *cur_val = lv_label_get_text(objects.airflow_value);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.airflow_value;
            lv_label_set_text(objects.airflow_value, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_display_airflow_int();
        int32_t cur_val = lv_arc_get_value(objects.airflow_arc);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.airflow_arc;
            lv_arc_set_value(objects.airflow_arc, new_val);
            tick_value_change_obj = NULL;
        }
    }
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_splash_screen,
    tick_screen_main,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_splash_screen();
    create_screen_main();
}
