#include "styles.h"
#include "images.h"
#include "fonts.h"

#include "ui.h"
#include "screens.h"

//
// Style: ShroomShed_Header
//

void init_style_shroom_shed_header_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xff11c8da));
    lv_style_set_text_font(style, &lv_font_montserrat_18);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
};

lv_style_t *get_style_shroom_shed_header_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_shroom_shed_header_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_shroom_shed_header(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_shroom_shed_header_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_shroom_shed_header(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_shroom_shed_header_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: ShroomShed_SubHeading
//

void init_style_shroom_shed_sub_heading_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xff11c8da));
    lv_style_set_text_opa(style, 255);
    lv_style_set_text_font(style, &lv_font_montserrat_14);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
};

lv_style_t *get_style_shroom_shed_sub_heading_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_shroom_shed_sub_heading_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_shroom_shed_sub_heading(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_shroom_shed_sub_heading_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_shroom_shed_sub_heading(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_shroom_shed_sub_heading_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: ShroomShed_SmallLabel
//

void init_style_shroom_shed_small_label_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xff11c8da));
    lv_style_set_text_opa(style, 255);
    lv_style_set_text_font(style, &lv_font_montserrat_10);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
};

lv_style_t *get_style_shroom_shed_small_label_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_shroom_shed_small_label_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_shroom_shed_small_label(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_shroom_shed_small_label_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_shroom_shed_small_label(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_shroom_shed_small_label_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: default_container
//

void init_style_default_container_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_border_color(style, lv_color_hex(0xff3500ff));
    lv_style_set_border_opa(style, 255);
    lv_style_set_border_width(style, 3);
    lv_style_set_border_side(style, LV_BORDER_SIDE_FULL);
    lv_style_set_border_post(style, true);
    lv_style_set_bg_color(style, lv_color_hex(0xffffffff));
    lv_style_set_bg_opa(style, 50);
};

lv_style_t *get_style_default_container_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_default_container_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_default_container(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_default_container_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_default_container(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_default_container_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: default_scale
//

void init_style_default_scale_ITEMS_DEFAULT(lv_style_t *style) {
    lv_style_set_length(style, 5);
    lv_style_set_line_width(style, 2);
    lv_style_set_line_color(style, lv_color_hex(0xff5da0aa));
};

lv_style_t *get_style_default_scale_ITEMS_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_default_scale_ITEMS_DEFAULT(style);
    }
    return style;
};

void init_style_default_scale_INDICATOR_DEFAULT(lv_style_t *style) {
    lv_style_set_length(style, 10);
    lv_style_set_line_width(style, 2);
    lv_style_set_line_color(style, lv_color_hex(0xff5da0aa));
    lv_style_set_radius(style, 0);
};

lv_style_t *get_style_default_scale_INDICATOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_default_scale_INDICATOR_DEFAULT(style);
    }
    return style;
};

void init_style_default_scale_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xff10bdd8));
    lv_style_set_line_color(style, lv_color_hex(0xff5da0aa));
    lv_style_set_text_font(style, &lv_font_montserrat_10);
};

lv_style_t *get_style_default_scale_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_default_scale_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_default_scale(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_default_scale_ITEMS_DEFAULT(), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_default_scale_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_default_scale_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_default_scale(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_default_scale_ITEMS_DEFAULT(), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_default_scale_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_default_scale_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
//
//

void add_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*AddStyleFunc)(lv_obj_t *obj);
    static const AddStyleFunc add_style_funcs[] = {
        add_style_shroom_shed_header,
        add_style_shroom_shed_sub_heading,
        add_style_shroom_shed_small_label,
        add_style_default_container,
        add_style_default_scale,
    };
    add_style_funcs[styleIndex](obj);
}

void remove_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*RemoveStyleFunc)(lv_obj_t *obj);
    static const RemoveStyleFunc remove_style_funcs[] = {
        remove_style_shroom_shed_header,
        remove_style_shroom_shed_sub_heading,
        remove_style_shroom_shed_small_label,
        remove_style_default_container,
        remove_style_default_scale,
    };
    remove_style_funcs[styleIndex](obj);
}

