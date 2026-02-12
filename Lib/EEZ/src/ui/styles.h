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



#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/