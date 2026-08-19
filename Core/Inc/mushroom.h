#ifndef __MUSHROOM_H
#define __MUSHROOM_H


#include "shroomshed.h"
#include "main.h"
#include <stdint.h>
#include <stdbool.h>

typedef enum node_type_e {
    NODE_TYPE_START = 0, // primordia formation
    NODE_TYPE_MID,
    NODE_TYPE_END
} node_type_e;

typedef struct MGP_node_t {
    uint8_t humidity_cv;
    uint8_t fan_cv;
    uint16_t time; // hours
    uint16_t progress; // hours
    node_type_e type;
    struct MGP_node_t *next;
} MGP_node_t;

typedef struct MGP_data_t {
    uint8_t *humidity_cv;
    uint8_t *fan_cv;
    uint16_t *time;
    bool wait_for_pinning;
    uint8_t length;
    uint8_t minimum_temperature; // degrees C
    uint8_t maximum_temperature; // degrees C
    const char *display_data;
} MGP_data_t;



typedef struct MGP_t {
    char name[20];
    MGP_node_t *head;
    MGP_data_t *data;
    uint16_t duration; 
    uint16_t progress;
    uint8_t stage; // 0 = waiting for pinning, 1 = fruitbody development
} MGP_t;

typedef struct mushroom_settings_t {
    MGP_t *current_profile;
    MGP_node_t *current_node;
} mushroom_settings_t;

extern struct MGP_t MGP_list[];
extern struct mushroom_settings_t mushroom_settings;


void tick_MGP(void);
void init_mushrooms(void);
void start_grow(uint8_t profile_index);

    

#endif /* __MUSHROOM_H */