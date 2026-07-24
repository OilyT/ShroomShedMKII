// Mushroom.c
// all source relating to mushrooms

#include "main.h"
#include "shroomshed.h"
#include "mushroom.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "display_manager.h"

#define MGP_LIST_SIZE 10
#define NODE_POOL_SIZE MGP_LIST_SIZE * 10
#define TICK_PERIOD 1000*60*60 // 1 hour
#define GROW_SPEED_MULTIPLIER 1 // 10000ish for debugging

MGP_t MGP_list[MGP_LIST_SIZE];
uint8_t MGP_list_index = 0;
MGP_node_t node_pool[NODE_POOL_SIZE];
static uint16_t node_pool_index = 0;


// State structs
MGP_t *current_profile = NULL;
MGP_node_t *current_node = NULL;
 
/* Mushroom settings struct 
mushroom_settings_t mushroom_settings = {
    .current_profile = &current_profile,
    .current_node = &current_node
};
*/

static uint32_t last_mpg_tick;

// oyster
static uint8_t oyster_default_h[] = {95, 90, 85};
static uint8_t oyster_default_f[] = {20, 30, 35};
static uint16_t oyster_default_t[] = {96, 72, 72};

MGP_data_t oyster_data = {
    .humidity_cv = oyster_default_h,
    .fan_cv = oyster_default_f,
    .time = oyster_default_t,
    .length = 3
};

// shiitake
static uint8_t shiitake_default_h[] = {95, 95, 90, 75};
static uint8_t shiitake_default_f[] = {20, 20, 20, 20};
static uint16_t shiitake_default_t[] = {48, 24, 96, 96};

MGP_data_t shiitake_data = {
    .humidity_cv = shiitake_default_h,
    .fan_cv = shiitake_default_f,
    .time = shiitake_default_t,
    .length = 4
};


// function prototypes
static void grow_process(void);
static void add_profile(char *name, MGP_data_t *data, uint16_t estimatedHarvestWindow);
static void init_profile(MGP_t *profile, MGP_data_t *data);
static MGP_node_t* add_node(MGP_node_t *base_node, uint8_t humidity_cv, uint8_t fan_cv, uint16_t time);


void init_mushrooms(void) {
    add_profile("Oyster", &oyster_data, 5);
    add_profile("Shiitake", &shiitake_data, 6);
}


static void grow_process(void) {
    // check progress through current node
    if (current_node->progress >= current_node->time) {
        if (current_node->type == NODE_TYPE_END) {
            // profile complete
            shedControl.manualHumidityControlValue = current_node->humidity_cv;
            shedControl.manualFanControlValue = current_node->fan_cv;

            current_profile = NULL;
            current_node = NULL;
            return;
        } else {
            // move to next node
            current_node = current_node->next;
            current_node->progress = 0;
        }
    }  

    if (current_node->type != NODE_TYPE_END) {    
        uint8_t normalised_progress = (current_node->progress * 100) / current_node->time;

        int8_t humidity_cv_delta = current_node->humidity_cv - current_node->next->humidity_cv;
        int16_t newHumidityCV = current_node->humidity_cv - ((humidity_cv_delta * normalised_progress) / 100);
        shedControl.humidityControlValue = newHumidityCV;

        int8_t fan_cv_delta = current_node->fan_cv - current_node->next->fan_cv;
        int16_t newFanCV = current_node->fan_cv - ((fan_cv_delta * normalised_progress) / 100);
        shedControl.fanControlValue = newFanCV;
    } else {
        shedControl.humidityControlValue = current_node->humidity_cv;
        shedControl.fanControlValue = current_node->fan_cv;
    }

    // calculate new cv's
}


void tick_MGP(void) {

    if (current_profile == NULL) {
        shedControl.controlMode = MODE_MANUAL;
        return;
    }

    uint32_t now = HAL_GetTick();
    if (now - last_mpg_tick >= (TICK_PERIOD / GROW_SPEED_MULTIPLIER)) {
        last_mpg_tick = now;
        current_node->progress++;
        current_profile->progress++;
    }
    grow_process();
}

void start_grow(uint8_t profile_index) {
    if (profile_index >= MGP_list_index) {
        return;
    }
    shedControl.controlMode = MODE_AUTOMATIC;

    MGP_t *profile = &MGP_list[profile_index];

    current_profile = profile;
    profile->progress = 0;
    current_node = profile->head;
    current_node->progress = 0;
    last_mpg_tick = HAL_GetTick();
    grow_process();
}


// profile and init functions

static void add_profile(char *name, MGP_data_t *data, uint16_t estimatedHarvestWindow) {
    if (MGP_list_index >= MGP_LIST_SIZE) return;
    MGP_t *new_profile = &MGP_list[MGP_list_index++];
    strncpy(new_profile->name, name, 20);
    init_profile(new_profile, data);
    new_profile->estimatedHarvestWindow = estimatedHarvestWindow;
}


static void init_profile(MGP_t *profile, MGP_data_t *data) {
    MGP_node_t *new_node = NULL;
    uint16_t duration = 0;
    for (uint8_t i = 0; i < data->length; i++) {
        uint8_t humidity_cv = data->humidity_cv[i];
        uint8_t fan_cv = data->fan_cv[i];
        uint16_t time = data->time[i];
        duration += time;
        new_node = add_node(new_node, humidity_cv, fan_cv, time);
        if (i == 0) {
            profile->head = new_node;
            new_node->type = NODE_TYPE_START;
        } else {
            new_node->type = NODE_TYPE_MID;
        }
    }
    new_node->type = NODE_TYPE_END;
    profile->duration = duration;
    profile->progress = 0;
}


static MGP_node_t* add_node(MGP_node_t *base_node, uint8_t humidity_cv, uint8_t fan_cv, uint16_t time) {
    if (node_pool_index >= NODE_POOL_SIZE) return NULL;
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


// var funcs
int32_t get_var_grow_progress_int(void) {
    if (current_profile == NULL) {
        return 0;
    }
    float progress = (float)current_profile->progress / (float)current_profile->duration;
    return (int32_t)(progress * 100);
}

const char *get_var_mushroom_grow_label() {
    if (current_profile == NULL) {
        return "";
    }
    return current_profile->name;
}

const char *get_var_grow_status(void) {
    if (current_profile == NULL) return "";

    static char status_str[20];

    static uint16_t refresh_delay_counter = 100;
    refresh_delay_counter++;
    if (refresh_delay_counter < 100) {
        return status_str;
    }
    refresh_delay_counter = 0;

    if (current_profile->progress / 24 >= current_profile->estimatedHarvestWindow) {
        strncpy(status_str, "Ready To Harvest!", sizeof(status_str) - 1);
        status_str[sizeof(status_str) - 1] = '\0';
    } else {
        static uint8_t counter = 0;
        if (counter++ >= 3) counter = 0;
        strncpy(status_str, "Shrooming", sizeof(status_str) - 1);
        for (uint8_t i = 0; i < counter; i++) {
            status_str[9 + i] = '.';
        }
        status_str[9 + counter] = '\0';
    }
    return status_str;
}

// action funcs
void action_stop_grow(void) {
    current_profile = NULL;
    current_node = NULL;
    shedControl.controlMode = MODE_MANUAL;
}