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

// Style: default_container
lv_style_t *get_style_default_container_MAIN_DEFAULT();
void add_style_default_container(lv_obj_t *obj);
void remove_style_default_container(lv_obj_t *obj);

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



#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/