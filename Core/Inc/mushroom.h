#ifndef __MUSHROOM_H
#define __MUSHROOM_H

#include "shroomshed.h"

#define N_PROFILES 1
#define OYSTER_NODES 3


typedef enum node_type_e {
    NODE_TYPE_START = 0,
    NODE_TYPE_MID,
    NODE_TYPE_END
}node_type_e;

typedef struct MGP_node_t {
    uint8_t humidity_cv;
    uint8_t fan_cv;
    uint16_t time; // hours
    node_type_e type;
    struct MGP_node_t *next;
} MGP_node_t;

typedef struct MGP_t {
    char name[20];
    MGP_node_t *head;
    uint8_t *humidity_cv[];
    uint8_t *fan_cv[];
    uint16_t *time[];
    uint8_t num_nodes;
} MGP_t;


#endif /* __MUSHROOM_H */