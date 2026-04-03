// Mushroom.c
// all source relating to mushrooms

#include "main.h"
#include "mushroom.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define MGP_LIST_SIZE 10
#define NODE_POOL_SIZE MGP_LIST_SIZE * 10
#define TICK_PERIOD 100*60*60 // 1 hour

struct MGP_t MGP_list[MGP_LIST_SIZE];
uint8_t MGP_list_index = 0;
struct MGP_node_t node_pool[NODE_POOL_SIZE];
uint16_t node_pool_index = 0;


//Mushroom grow profiles
struct MGP_t *current_profile = NULL;
struct MGP_node_t *current_node = NULL;
uint32_t last_mpg_tick;

// oyster
static uint8_t oyster_default_h[] = {90, 90, 80};
static uint8_t oyster_default_f[] = {15, 35, 35};
static uint16_t oyster_default_t[] = {72, 72, 72};

MGP_data_t oyster_data = {
    .humidity_cv = oyster_default_h,
    .fan_cv = oyster_default_f,
    .time = oyster_default_t,
    .length = 3
};

// shiitake
static uint8_t shiitake_default_h[] = {95, 95, 90, 85};
static uint8_t shiitake_default_f[] = {15, 20, 25, 25};
static uint16_t shiitake_default_t[] = {24, 24, 72, 48};

MGP_data_t shiitake_data = {
    .humidity_cv = shiitake_default_h,
    .fan_cv = shiitake_default_f,
    .time = shiitake_default_t,
    .length = 4
};


// function prototypes
static void grow_process(MGP_t *profile);
static void add_profile(char *name, MGP_data_t *data);
static void init_profile(MGP_t *profile, MGP_data_t *data);
static MGP_node_t* add_node(MGP_node_t *base_node, uint8_t humidity_cv, uint8_t fan_cv, uint16_t time);


static void grow_process(MGP_t *profile) {
    // check progress through current node
    if (current_node->progress >= current_node->time) {
        if (current_node->type == NODE_TYPE_END) {
            // profile complete
            current_profile = NULL;
            current_node = NULL;
        } else {
            // move to next node
            current_node = current_node->next;
            current_node->progress = 0;
        }
    }  

    // calculate new cv's
    uint8_t normalised_progress = (current_node->progress * 100) / current_node->time;

    int8_t humidity_cv_delta = current_node->humidity_cv - current_node->next->humidity_cv;
    shedControl.humidityControlValue = current_node->humidity_cv + ((humidity_cv_delta * normalised_progress) / 100);

    int8_t fan_cv_delta = current_node->fan_cv - current_node->next->fan_cv;
    shedControl.fanControlValue = current_node->fan_cv + ((fan_cv_delta * normalised_progress) / 100);
}


void tick_MGP(void) {

    if (current_profile == NULL) {
        return;
    }

    uint32_t now = HAL_GetTick();
    if (now - last_mpg_tick >= TICK_PERIOD) {
        last_mpg_tick = now;
        current_node->progress++;
        grow_process(current_profile);
    }
}

void start_grow(uint8_t profile_index) {
    if (profile_index >= MGP_list_index) {
        return;
    }
    MGP_t *profile = &MGP_list[profile_index];

    current_profile = profile;
    profile->progress = 0;
    current_node = profile->head;
    last_mpg_tick = HAL_GetTick();
    grow_process(current_profile);
}


void init_mushrooms(void) {
    add_profile("Oyster", &oyster_data);
    add_profile("Shiitake", &shiitake_data);
}


static void add_profile(char *name, MGP_data_t *data) {
    MGP_t *new_profile = &MGP_list[MGP_list_index++];
    strncpy(new_profile->name, name, 20);
    init_profile(new_profile, data);
}

static void init_profile(MGP_t *profile, MGP_data_t *data) {

    MGP_node_t *current_node = NULL;
    uint16_t duration = 0;
    for (uint8_t i = 0; i < data->length; i++) {
        uint8_t humidity_cv = data->humidity_cv[i];
        uint8_t fan_cv = data->fan_cv[i];
        uint16_t time = data->time[i];
        duration += time;
        current_node = add_node(current_node, humidity_cv, fan_cv, time);
        if (i == 0) {
            profile->head = current_node;
            current_node->type = NODE_TYPE_START;
        } else {
            current_node->type = NODE_TYPE_MID;
        }
    }
    current_node->type = NODE_TYPE_END;
    profile->duration = duration;
    profile->progress = 0;
}

static MGP_node_t* add_node(MGP_node_t *base_node, uint8_t humidity_cv, uint8_t fan_cv, uint16_t time) {
    MGP_node_t *newNode = &node_pool[node_pool_index++];
    newNode->humidity_cv = humidity_cv; 
    newNode->fan_cv = fan_cv;
    newNode->time = time;
    newNode->progress = 0;
    newNode->next = NULL;
    if (base_node != NULL) {
        base_node->next = newNode;
    } 
    return newNode;
}

