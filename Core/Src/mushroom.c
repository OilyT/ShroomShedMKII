// Mushroom.c
// all source relating to mushrooms

#include "main.h"
#include "shroomshed.h"
#include "mushroom.h"
#include "vars.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "display_manager.h"

#define MGP_LIST_SIZE 10
#define NODE_POOL_SIZE MGP_LIST_SIZE * 10
#define TICK_PERIOD 1000*60*60 // 1 hour
#define GROW_SPEED_MULTIPLIER 10000 // 10000ish for debugging

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
static uint8_t oyster_default_h[] = {90, 90, 80};
static uint8_t oyster_default_f[] = {15, 20, 35};
static uint16_t oyster_default_t[] = {24, 144, 72};

MGP_data_t oyster_data = {
    .humidity_cv = oyster_default_h,
    .fan_cv = oyster_default_f,
    .time = oyster_default_t,
    .wait_for_pinning = true,
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
    .wait_for_pinning = false,
    .length = 4
};


// nz lions mane
static uint8_t lions_mane_default_h[] = {95, 95, 90, 80};
static uint8_t lions_mane_default_f[] = {20, 20, 20, 20};
static uint16_t lions_mane_default_t[] = {24, 48, 300, 96};

MGP_data_t lions_mane_data = {
    .humidity_cv = lions_mane_default_h,
    .fan_cv = lions_mane_default_f,
    .time = lions_mane_default_t,
    .wait_for_pinning = false,
    .length = 4
};

// function prototypes
static void grow_process(void);
static void add_profile(char *name, MGP_data_t *data);
static void init_profile(MGP_t *profile, MGP_data_t *data);
static MGP_node_t* add_node(MGP_node_t *base_node, uint8_t humidity_cv, uint8_t fan_cv, uint16_t time);


void init_mushrooms(void) {
    add_profile("Oyster", &oyster_data);
    add_profile("Shiitake", &shiitake_data);
    add_profile("Lions Mane", &lions_mane_data);

    set_var_mushroom_names_list(NULL);
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
        if (current_profile->stage > 0) {
            current_node->progress++;
            current_profile->progress++;
        }
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
    if (current_profile->data->wait_for_pinning) {
        current_profile->stage = 0;
    } else {
        current_profile->stage = 1;
    }
    last_mpg_tick = HAL_GetTick();
    grow_process();
}


// profile and init functions

static void add_profile(char *name, MGP_data_t *data) {
    if (MGP_list_index >= MGP_LIST_SIZE) return;
    MGP_t *new_profile = &MGP_list[MGP_list_index++];
    strncpy(new_profile->name, name, 20);
    init_profile(new_profile, data);
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
    profile->stage = data->wait_for_pinning ? 0 : 1;
    profile->data = data;
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


const char *get_var_grow_progress_str(void) {
    if (current_profile == NULL) {
        return "";
    }

    if (current_profile->stage == 0) {
        return "waiting...";
    }

    int32_t progress = get_var_grow_progress_int();
    static char progress_str[10];
    snprintf(progress_str, sizeof(progress_str), "%d%%", (int)(progress));
    return progress_str;
}


const char *get_var_mushroom_grow_label(void) {
    if (current_profile == NULL) {
        return "";
    }
    return current_profile->name;
}

bool get_var_hide_progress_grow_button(void) {
    if (current_profile == NULL) {
        return true;
    }

    return current_profile->stage;
}

const char *get_var_progress_grow_button_label(void) {
    return "Growing";
}


// action funcs
void action_stop_grow(void) {
    current_profile = NULL;
    current_node = NULL;
    shedControl.controlMode = MODE_MANUAL;
}

void action_next_grow_stage(lv_event_t *e) {
    if (current_profile == NULL) {
        return;
    }
    if (current_profile->stage == 0) {
        current_profile->stage = 1;
    }
}
