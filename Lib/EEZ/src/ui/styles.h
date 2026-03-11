#ifndef EEZ_LVGL_UI_STYLES_H
#define EEZ_LVGL_UI_STYLES_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Style: ShroomShed_Header
lv_style_t *get_style_shroom_shed_header_MAIN_DEFAULT();
void add_style_shroom_shed_header(lv_obj_t *obj);
void remove_style_shroom_shed_header(lv_obj_t *obj);

// Style: ShroomShed_SubHeading
lv_style_t *get_style_shroom_shed_sub_heading_MAIN_DEFAULT();
void add_style_shroom_shed_sub_heading(lv_obj_t *obj);
void remove_style_shroom_shed_sub_heading(lv_obj_t *obj);

// Style: ShroomShed_SmallLabel
lv_style_t *get_style_shroom_shed_small_label_MAIN_DEFAULT();
void add_style_shroom_shed_small_label(lv_obj_t *obj);
void remove_style_shroom_shed_small_label(lv_obj_t *obj);

// Style: blue_container
lv_style_t *get_style_blue_container_MAIN_DEFAULT();
void add_style_blue_container(lv_obj_t *obj);
void remove_style_blue_container(lv_obj_t *obj);

// Style: default_scale
lv_style_t *get_style_default_scale_ITEMS_DEFAULT();
lv_style_t *get_style_default_scale_INDICATOR_DEFAULT();
lv_style_t *get_style_default_scale_MAIN_DEFAULT();
void add_style_default_scale(lv_obj_t *obj);
void remove_style_default_scale(lv_obj_t *obj);

// Style: Std_button
lv_style_t *get_style_std_button_MAIN_DEFAULT();
void add_style_std_button(lv_obj_t *obj);
void remove_style_std_button(lv_obj_t *obj);

// Style: Disco_slider
lv_style_t *get_style_disco_slider_INDICATOR_DEFAULT();
lv_style_t *get_style_disco_slider_KNOB_DEFAULT();
lv_style_t *get_style_disco_slider_MAIN_DEFAULT();
void add_style_disco_slider(lv_obj_t *obj);
void remove_style_disco_slider(lv_obj_t *obj);

// Style: std_button_dark
lv_style_t *get_style_std_button_dark_MAIN_DEFAULT();
lv_style_t *get_style_std_button_dark_MAIN_PRESSED();
void add_style_std_button_dark(lv_obj_t *obj);
void remove_style_std_button_dark(lv_obj_t *obj);

// Style: std_button_matrix_dark
lv_style_t *get_style_std_button_matrix_dark_ITEMS_DEFAULT();
lv_style_t *get_style_std_button_matrix_dark_ITEMS_PRESSED();
lv_style_t *get_style_std_button_matrix_dark_MAIN_DEFAULT();
void add_style_std_button_matrix_dark(lv_obj_t *obj);
void remove_style_std_button_matrix_dark(lv_obj_t *obj);

// Style: disco_button_style
lv_style_t *get_style_disco_button_style_MAIN_DEFAULT();
void add_style_disco_button_style(lv_obj_t *obj);
void remove_style_disco_button_style(lv_obj_t *obj);

// Style: std_slider_dark
lv_style_t *get_style_std_slider_dark_INDICATOR_DEFAULT();
lv_style_t *get_style_std_slider_dark_MAIN_DEFAULT();
void add_style_std_slider_dark(lv_obj_t *obj);
void remove_style_std_slider_dark(lv_obj_t *obj);

// Style: Button_Label_48
lv_style_t *get_style_button_label_48_MAIN_DEFAULT();
lv_style_t *get_style_button_label_48_MAIN_CHECKED_PRESSED();
void add_style_button_label_48(lv_obj_t *obj);
void remove_style_button_label_48(lv_obj_t *obj);

// Style: Button_Label_32
lv_style_t *get_style_button_label_32_MAIN_DEFAULT();
lv_style_t *get_style_button_label_32_MAIN_CHECKED_PRESSED();
void add_style_button_label_32(lv_obj_t *obj);
void remove_style_button_label_32(lv_obj_t *obj);

// Style: Button_Label_24
lv_style_t *get_style_button_label_24_MAIN_DEFAULT();
lv_style_t *get_style_button_label_24_MAIN_CHECKED_PRESSED();
void add_style_button_label_24(lv_obj_t *obj);
void remove_style_button_label_24(lv_obj_t *obj);

// Style: std_switch
lv_style_t *get_style_std_switch_MAIN_DEFAULT();
lv_style_t *get_style_std_switch_KNOB_DEFAULT();
lv_style_t *get_style_std_switch_INDICATOR_CHECKED();
lv_style_t *get_style_std_switch_INDICATOR_DEFAULT();
void add_style_std_switch(lv_obj_t *obj);
void remove_style_std_switch(lv_obj_t *obj);

// Style: std_Label_24
lv_style_t *get_style_std_label_24_MAIN_DEFAULT();
void add_style_std_label_24(lv_obj_t *obj);
void remove_style_std_label_24(lv_obj_t *obj);

// Style: std_Label_32
lv_style_t *get_style_std_label_32_MAIN_DEFAULT();
void add_style_std_label_32(lv_obj_t *obj);
void remove_style_std_label_32(lv_obj_t *obj);

// Style: std_Label_48
lv_style_t *get_style_std_label_48_MAIN_DEFAULT();
void add_style_std_label_48(lv_obj_t *obj);
void remove_style_std_label_48(lv_obj_t *obj);



#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/