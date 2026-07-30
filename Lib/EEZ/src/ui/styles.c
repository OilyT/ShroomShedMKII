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
    lv_style_set_text_font(style, &lv_font_montserrat_32);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
    lv_style_set_text_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][3]));
    lv_style_set_border_width(style, 3);
    lv_style_set_border_side(style, LV_BORDER_SIDE_FULL);
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][1]));
    lv_style_set_radius(style, 5);
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
    lv_style_set_text_font(style, &lv_font_montserrat_24);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
    lv_style_set_outline_width(style, 2);
    lv_style_set_outline_color(style, lv_color_hex(theme_colors[active_theme_index][3]));
    lv_style_set_pad_top(style, 1);
    lv_style_set_pad_bottom(style, 1);
    lv_style_set_pad_left(style, 1);
    lv_style_set_pad_right(style, 1);
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
    lv_style_set_text_font(style, &lv_font_montserrat_16);
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
// Style: blue_container
//

void init_style_blue_container_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][3]));
    lv_style_set_border_opa(style, 255);
    lv_style_set_border_width(style, 3);
    lv_style_set_border_side(style, LV_BORDER_SIDE_FULL);
    lv_style_set_radius(style, 5);
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][1]));
    lv_style_set_bg_opa(style, 255);
};

lv_style_t *get_style_blue_container_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_blue_container_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_blue_container(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_blue_container_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_blue_container(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_blue_container_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: default_scale
//

void init_style_default_scale_ITEMS_DEFAULT(lv_style_t *style) {
    lv_style_set_length(style, 5);
    lv_style_set_line_width(style, 2);
    lv_style_set_line_color(style, lv_color_hex(0xff10bdd8));
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
    lv_style_set_line_color(style, lv_color_hex(0xff10bdd8));
    lv_style_set_radius(style, 0);
    lv_style_set_text_font(style, &lv_font_montserrat_16);
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
    lv_style_set_line_color(style, lv_color_hex(0xff10bdd8));
    lv_style_set_text_font(style, &lv_font_montserrat_16);
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
// Style: Std_button
//

void init_style_std_button_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff00c8d2));
    lv_style_set_text_font(style, &lv_font_montserrat_16);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
};

lv_style_t *get_style_std_button_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_std_button_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_std_button(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_std_button_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_std_button(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_std_button_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: Disco_slider
//

void init_style_disco_slider_INDICATOR_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff0000ff));
    lv_style_set_bg_grad_dir(style, LV_GRAD_DIR_HOR);
    lv_style_set_bg_grad_color(style, lv_color_hex(0xffff0000));
};

lv_style_t *get_style_disco_slider_INDICATOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_disco_slider_INDICATOR_DEFAULT(style);
    }
    return style;
};

void init_style_disco_slider_KNOB_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff00c8d2));
};

lv_style_t *get_style_disco_slider_KNOB_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_disco_slider_KNOB_DEFAULT(style);
    }
    return style;
};

void init_style_disco_slider_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_border_color(style, lv_color_hex(0xff00c6ff));
    lv_style_set_border_width(style, 2);
    lv_style_set_border_opa(style, 100);
};

lv_style_t *get_style_disco_slider_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_disco_slider_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_disco_slider(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_disco_slider_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_disco_slider_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_disco_slider_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_disco_slider(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_disco_slider_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_disco_slider_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_disco_slider_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: std_button_dark
//

void init_style_std_button_dark_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][1]));
    lv_style_set_text_font(style, &lv_font_montserrat_16);
    lv_style_set_text_opa(style, 255);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_bg_opa(style, 255);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_border_width(style, 2);
    lv_style_set_border_opa(style, 255);
    lv_style_set_border_side(style, LV_BORDER_SIDE_FULL);
};

lv_style_t *get_style_std_button_dark_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_std_button_dark_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_std_button_dark_MAIN_PRESSED(lv_style_t *style) {
    lv_style_set_border_width(style, 5);
    lv_style_set_border_side(style, LV_BORDER_SIDE_FULL);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
};

lv_style_t *get_style_std_button_dark_MAIN_PRESSED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_std_button_dark_MAIN_PRESSED(style);
    }
    return style;
};

void add_style_std_button_dark(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_std_button_dark_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_std_button_dark_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
};

void remove_style_std_button_dark(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_std_button_dark_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_std_button_dark_MAIN_PRESSED(), LV_PART_MAIN | LV_STATE_PRESSED);
};

//
// Style: std_button_matrix_dark
//

void init_style_std_button_matrix_dark_ITEMS_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_text_font(style, &lv_font_montserrat_16);
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][1]));
    lv_style_set_outline_width(style, 2);
    lv_style_set_outline_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
};

lv_style_t *get_style_std_button_matrix_dark_ITEMS_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_std_button_matrix_dark_ITEMS_DEFAULT(style);
    }
    return style;
};

void init_style_std_button_matrix_dark_ITEMS_PRESSED(lv_style_t *style) {
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_border_width(style, 10);
    lv_style_set_border_side(style, LV_BORDER_SIDE_FULL);
};

lv_style_t *get_style_std_button_matrix_dark_ITEMS_PRESSED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_std_button_matrix_dark_ITEMS_PRESSED(style);
    }
    return style;
};

void init_style_std_button_matrix_dark_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][2]));
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_border_width(style, 2);
};

lv_style_t *get_style_std_button_matrix_dark_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_std_button_matrix_dark_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_std_button_matrix_dark(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_std_button_matrix_dark_ITEMS_DEFAULT(), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_std_button_matrix_dark_ITEMS_PRESSED(), LV_PART_ITEMS | LV_STATE_PRESSED);
    lv_obj_add_style(obj, get_style_std_button_matrix_dark_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_std_button_matrix_dark(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_std_button_matrix_dark_ITEMS_DEFAULT(), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_std_button_matrix_dark_ITEMS_PRESSED(), LV_PART_ITEMS | LV_STATE_PRESSED);
    lv_obj_remove_style(obj, get_style_std_button_matrix_dark_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: disco_button_style
//

void init_style_disco_button_style_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff21f3b1));
    lv_style_set_bg_grad_dir(style, LV_GRAD_DIR_HOR);
    lv_style_set_bg_grad_color(style, lv_color_hex(0xffed21f3));
    lv_style_set_text_color(style, lv_color_hex(0xff08ff00));
};

lv_style_t *get_style_disco_button_style_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_disco_button_style_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_disco_button_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_disco_button_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_disco_button_style(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_disco_button_style_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: std_slider_dark
//

void init_style_std_slider_dark_INDICATOR_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xff0026ff));
    lv_style_set_border_opa(style, 255);
    lv_style_set_border_width(style, 2);
    lv_style_set_border_side(style, LV_BORDER_SIDE_FULL);
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_bg_opa(style, 100);
};

lv_style_t *get_style_std_slider_dark_INDICATOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_std_slider_dark_INDICATOR_DEFAULT(style);
    }
    return style;
};

void init_style_std_slider_dark_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_border_width(style, 2);
    lv_style_set_border_side(style, LV_BORDER_SIDE_FULL);
    lv_style_set_bg_color(style, lv_color_hex(0xff0d52ff));
    lv_style_set_bg_opa(style, 32);
};

lv_style_t *get_style_std_slider_dark_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_std_slider_dark_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_std_slider_dark(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_std_slider_dark_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_std_slider_dark_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_std_slider_dark(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_std_slider_dark_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_std_slider_dark_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: Button_Label_48
//

void init_style_button_label_48_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_font(style, &lv_font_montserrat_48);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
    lv_style_set_align(style, LV_ALIGN_CENTER);
};

lv_style_t *get_style_button_label_48_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_label_48_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_button_label_48_MAIN_CHECKED_PRESSED(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_text_font(style, &lv_font_montserrat_48);
};

lv_style_t *get_style_button_label_48_MAIN_CHECKED_PRESSED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_label_48_MAIN_CHECKED_PRESSED(style);
    }
    return style;
};

void add_style_button_label_48(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_button_label_48_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_button_label_48_MAIN_CHECKED_PRESSED(), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
};

void remove_style_button_label_48(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_button_label_48_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_button_label_48_MAIN_CHECKED_PRESSED(), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
};

//
// Style: Button_Label_32
//

void init_style_button_label_32_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_font(style, &lv_font_montserrat_32);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
    lv_style_set_align(style, LV_ALIGN_DEFAULT);
};

lv_style_t *get_style_button_label_32_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_label_32_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_button_label_32_MAIN_CHECKED_PRESSED(lv_style_t *style) {
    lv_style_set_text_font(style, &lv_font_montserrat_32);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_align(style, LV_ALIGN_DEFAULT);
};

lv_style_t *get_style_button_label_32_MAIN_CHECKED_PRESSED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_label_32_MAIN_CHECKED_PRESSED(style);
    }
    return style;
};

void add_style_button_label_32(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_button_label_32_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_button_label_32_MAIN_CHECKED_PRESSED(), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
};

void remove_style_button_label_32(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_button_label_32_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_button_label_32_MAIN_CHECKED_PRESSED(), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
};

//
// Style: Button_Label_24
//

void init_style_button_label_24_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
    lv_style_set_text_font(style, &lv_font_montserrat_24);
    lv_style_set_align(style, LV_ALIGN_CENTER);
};

lv_style_t *get_style_button_label_24_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_label_24_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_button_label_24_MAIN_CHECKED_PRESSED(lv_style_t *style) {
    lv_style_set_text_font(style, &lv_font_montserrat_24);
    lv_style_set_text_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
};

lv_style_t *get_style_button_label_24_MAIN_CHECKED_PRESSED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_button_label_24_MAIN_CHECKED_PRESSED(style);
    }
    return style;
};

void add_style_button_label_24(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_button_label_24_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_button_label_24_MAIN_CHECKED_PRESSED(), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
};

void remove_style_button_label_24(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_button_label_24_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_button_label_24_MAIN_CHECKED_PRESSED(), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_PRESSED);
};

//
// Style: std_switch
//

void init_style_std_switch_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_border_color(style, lv_color_hex(theme_colors[active_theme_index][3]));
    lv_style_set_border_width(style, 3);
};

lv_style_t *get_style_std_switch_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_std_switch_MAIN_DEFAULT(style);
    }
    return style;
};

void init_style_std_switch_KNOB_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][0]));
};

lv_style_t *get_style_std_switch_KNOB_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_std_switch_KNOB_DEFAULT(style);
    }
    return style;
};

void init_style_std_switch_INDICATOR_CHECKED(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][4]));
    lv_style_set_bg_opa(style, 255);
};

lv_style_t *get_style_std_switch_INDICATOR_CHECKED() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_std_switch_INDICATOR_CHECKED(style);
    }
    return style;
};

void init_style_std_switch_INDICATOR_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(0xffff0000));
    lv_style_set_bg_opa(style, 192);
};

lv_style_t *get_style_std_switch_INDICATOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_std_switch_INDICATOR_DEFAULT(style);
    }
    return style;
};

void add_style_std_switch(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_std_switch_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_std_switch_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_std_switch_INDICATOR_CHECKED(), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_add_style(obj, get_style_std_switch_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
};

void remove_style_std_switch(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_std_switch_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_std_switch_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_std_switch_INDICATOR_CHECKED(), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_remove_style(obj, get_style_std_switch_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
};

//
// Style: std_Label_24
//

void init_style_std_label_24_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xff11c8da));
    lv_style_set_text_opa(style, 255);
    lv_style_set_text_font(style, &lv_font_montserrat_24);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
    lv_style_set_pad_top(style, 1);
    lv_style_set_pad_bottom(style, 1);
    lv_style_set_pad_left(style, 1);
    lv_style_set_pad_right(style, 1);
};

lv_style_t *get_style_std_label_24_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_std_label_24_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_std_label_24(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_std_label_24_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_std_label_24(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_std_label_24_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: std_Label_32
//

void init_style_std_label_32_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xff11c8da));
    lv_style_set_text_opa(style, 255);
    lv_style_set_text_font(style, &lv_font_montserrat_32);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
    lv_style_set_pad_top(style, 1);
    lv_style_set_pad_bottom(style, 1);
    lv_style_set_pad_left(style, 1);
    lv_style_set_pad_right(style, 1);
};

lv_style_t *get_style_std_label_32_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_std_label_32_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_std_label_32(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_std_label_32_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_std_label_32(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_std_label_32_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: std_Label_48
//

void init_style_std_label_48_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_text_color(style, lv_color_hex(0xff11c8da));
    lv_style_set_text_opa(style, 255);
    lv_style_set_text_font(style, &lv_font_montserrat_48);
    lv_style_set_text_align(style, LV_TEXT_ALIGN_CENTER);
    lv_style_set_pad_top(style, 1);
    lv_style_set_pad_bottom(style, 1);
    lv_style_set_pad_left(style, 1);
    lv_style_set_pad_right(style, 1);
};

lv_style_t *get_style_std_label_48_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = lv_malloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_std_label_48_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_std_label_48(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_std_label_48_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_std_label_48(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_std_label_48_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
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
        add_style_blue_container,
        add_style_default_scale,
        add_style_std_button,
        add_style_disco_slider,
        add_style_std_button_dark,
        add_style_std_button_matrix_dark,
        add_style_disco_button_style,
        add_style_std_slider_dark,
        add_style_button_label_48,
        add_style_button_label_32,
        add_style_button_label_24,
        add_style_std_switch,
        add_style_std_label_24,
        add_style_std_label_32,
        add_style_std_label_48,
    };
    add_style_funcs[styleIndex](obj);
}

void remove_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*RemoveStyleFunc)(lv_obj_t *obj);
    static const RemoveStyleFunc remove_style_funcs[] = {
        remove_style_shroom_shed_header,
        remove_style_shroom_shed_sub_heading,
        remove_style_shroom_shed_small_label,
        remove_style_blue_container,
        remove_style_default_scale,
        remove_style_std_button,
        remove_style_disco_slider,
        remove_style_std_button_dark,
        remove_style_std_button_matrix_dark,
        remove_style_disco_button_style,
        remove_style_std_slider_dark,
        remove_style_button_label_48,
        remove_style_button_label_32,
        remove_style_button_label_24,
        remove_style_std_switch,
        remove_style_std_label_24,
        remove_style_std_label_32,
        remove_style_std_label_48,
    };
    remove_style_funcs[styleIndex](obj);
}

