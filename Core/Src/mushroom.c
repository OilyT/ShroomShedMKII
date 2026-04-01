// Mushroom.c
// all source relating to mushrooms is here

#include "shroomshed.h"
#include "mushroom.h"


#define NODE_POOL_SIZE 100


struct MGP_t MGP_list[N_PROFILES];
struct MGP_node_t node_pool[NODE_POOL_SIZE];
uint16_t node_pool_index = 0;

//Mushroom grow profiles

// oyster defaults
humidity



struct MGP_t oyster_profile = {
    .name = "Oyster",
    .head = NULL,
    .humidity_cv = {90, 90, 80},
    .fan_cv = {15, 35, 35},
    .time = {72, 72, 72},
    .num_nodes = OYSTER_NODES
};


// function prototypes
static void init_profile(MGP_t *profile);
static MGP_node_t* add_node(MGP_node_t *base_node, uint8_t humidity_cv, uint8_t fan_cv, uint16_t time);



static void init_profile(MGP_t *profile) {

    MGP_node_t *current_node = NULL;
    for (uint8_t i = 0; i < profile->num_nodes; i++) {
        uint8_t humidity_cv = profile->humidity_cv[i];
        uint8_t fan_cv = profile->fan_cv[i];
        uint16_t time = profile->time[i];
        current_node = add_node(current_node, humidity_cv, fan_cv, time);
        if (i == 0) {
            profile->head = current_node;
        }
    }
    current_node->type = NODE_TYPE_END;
}


static MGP_node_t* add_node(MGP_node_t *base_node, uint8_t humidity_cv, uint8_t fan_cv, uint16_t time) {
    MGP_node_t *newNode = &node_pool[node_pool_index++];
    newNode->humidity_cv = humidity_cv; 
    newNode->fan_cv = fan_cv;
    newNode->time = time;
    newNode->next = NULL;
    if (base_node == NULL) {
        newNode->type = NODE_TYPE_START;
    } else {
        newNode->type = NODE_TYPE_MID;
        base_node->next = newNode;
    }
    return newNode;
}

