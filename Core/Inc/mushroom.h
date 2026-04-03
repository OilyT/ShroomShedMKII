#ifndef __MUSHROOM_H
#define __MUSHROOM_H


#include "shroomshed.h"
#include "main.h"
#include <stdint.h>

typedef enum node_type_e {
    NODE_TYPE_START = 0,
    NODE_TYPE_MID,
    NODE_TYPE_END
}node_type_e;

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
    uint8_t length;
} MGP_data_t;

typedef struct MGP_t {
    char name[20];
    MGP_node_t *head;
    uint16_t duration; 
    uint16_t progress;
} MGP_t;

extern struct MGP_t MGP_list[];

void tick_MGP(void);
void init_mushrooms(void);
void start_profile(MGP_t *profile);

    

#endif /* __MUSHROOM_H */