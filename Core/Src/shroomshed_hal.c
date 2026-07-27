/**
 * @file shroomshed_hal.c
 * @brief shroomshed hardware abstraction layer
 * @author yolo swaggins
 * @date with your mum
 */

#include "shroomshed_hal.h"
#include "stm32h5xx_hal.h"
#include "stm32h5xx_hal_gpio.h"
#include "main.h"
#include "shroomshed.h"
#include <stdint.h>
#include <math.h>
#include "stm32h5xx_hal_flash.h"
#include "eeprom_emul.h"

// humidity PID
#define PID_ID_PERIOD 180 // seconds
#define MAX_PULSE 1100
#define MIN_PULSE 600
#define PULSE_RANGE (MAX_PULSE - MIN_PULSE)
#define MAX_POWER 1000

// PV's
static float P_term = 0;
static float I_term = 0;
static float D_term = 0;

static MGP_t restoredMushroomProfile;
static MGP_node_t restoredMushroomNodes[SETTINGS_FLASH_MAX_MUSHROOM_NODES];
static mushroom_settings_t restoredMushroomSettings = {
    .current_profile = NULL,
    .current_node = NULL
};

// PFP's
static uint8_t count_mushroom_nodes(const MGP_t *profile);
static void snapshot_mushroom_settings(settings_mushroom_snapshot_t *snapshot, const mushroom_settings_t *mushroomSettings);
static void restore_mushroom_settings(const settings_mushroom_snapshot_t *snapshot, mushroom_settings_t *mushroomSettings);

/* ============================================================================
 * Function Implementations
 * ============================================================================ */

void set_humidifier_power(uint16_t power) {
    uint16_t counter_register_power = power / (MAX_POWER / PULSE_RANGE) + MIN_PULSE;
    TRANSDUCER_PWM_TIMER.Instance->CCR3 = counter_register_power;
}

void humidity_process(uint8_t humidity_setpoint) {
    const static float Pk = 100.0;
    const static float Ik = 50.0;
    const static float Dk = 1000.0;

    static uint16_t ID_counter = 0;

    float error = (float)humidity_setpoint - shedState.humidityCurrent;
    static float lastError = 0;

    // proportional
    P_term = Pk * error;
    if (P_term > MAX_POWER) {
        P_term = MAX_POWER;
    } else if (P_term < 0) {
        P_term = 0;
    }

    ID_counter++;
    if (ID_counter >= CONTROL_PROCESS_HZ * PID_ID_PERIOD) {
        // integral
        float I_delta = (Ik * error) / PID_ID_PERIOD;
        I_term += I_delta;

        if (I_term < 0) {
            I_term = 0;
        }
        if (I_term > MAX_POWER - P_term) {
            I_term = MAX_POWER - P_term;
        }

        // derivative
        float error_delta = error - lastError;
        D_term = Dk * error_delta / PID_ID_PERIOD;

        lastError = error;
        ID_counter = 0;
    }

    uint16_t power = (uint16_t)(P_term + I_term + D_term);
    if (power > MAX_POWER) {
        power = MAX_POWER;
    } else if (power < 0) {
        power = 0;
    }

    set_humidifier_power(power);
}

void set_fan_speed(uint8_t speed) {
    float gamma = 0.7;
    uint16_t pwm_output = pow(speed / 100.0f, gamma) * FAN_PWM_TIMER.Init.Period;
    FAN_PWM_TIMER.Instance->CCR3 = pwm_output;
}

void enable_shed(void) {
    start_humidifier();
    start_fan();
    shedControl.outputMode = OUTPUT_NORMAL;
}

void disable_shed(void) {
    stop_humidifier();
    stop_fan();
    shedControl.outputMode = OUTPUT_DISABLED;
}

inline void enable_boost(void) {
    HAL_GPIO_WritePin(BOOST_EN_GPIO_Port, BOOST_EN_Pin, GPIO_PIN_SET);
}

inline void disable_boost(void) {
    HAL_GPIO_WritePin(BOOST_EN_GPIO_Port, BOOST_EN_Pin, GPIO_PIN_RESET);
}

inline void start_humidifier(void) {
    HAL_TIM_PWM_Start(&TRANSDUCER_PWM_TIMER, TIM_CHANNEL_3);
}

inline void stop_humidifier(void) {
    HAL_TIM_PWM_Stop(&TRANSDUCER_PWM_TIMER, TIM_CHANNEL_3);
}

inline void start_fan(void) {
    HAL_TIM_PWM_Start(&FAN_PWM_TIMER, TIM_CHANNEL_3);
}

inline void stop_fan(void) {
    HAL_TIM_PWM_Stop(&FAN_PWM_TIMER, TIM_CHANNEL_3);
}


// EEPROM EMULATION / FLASH

bool init_EEPROM_emulation(void) {
    EE_Status status = EE_Init(EE_FORCED_ERASE);
    if (status != EE_OK) {
        // Handle error
        return false;
    }
    return true;
}

void save_settings(void) {
  
}

bool load_settings(void) {
    
}


static void snapshot_mushroom_settings(settings_mushroom_snapshot_t *snapshot, const mushroom_settings_t *mushroomSettings) {
    const MGP_t *profile;
    const MGP_node_t *node;
    uint8_t nodeCount;

    memset(snapshot, 0xFF, sizeof(*snapshot));

    if ((mushroomSettings == NULL) || (mushroomSettings->current_profile == NULL)) {
        snapshot->active = 0U;
        snapshot->currentNodeIndex = 0xFFU;
        snapshot->nodeCount = 0U;
        return;
    }

    profile = mushroomSettings->current_profile;
    node = profile->head;
    nodeCount = 0U;

    snapshot->active = 1U;
    snapshot->currentNodeIndex = 0xFFU;
    snapshot->nodeCount = count_mushroom_nodes(profile);
    strncpy(snapshot->name, profile->name, sizeof(snapshot->name));
    snapshot->name[sizeof(snapshot->name) - 1U] = '\0';
    snapshot->duration = profile->duration;
    snapshot->progress = profile->progress;
    snapshot->estimatedHarvestWindow = profile->estimatedHarvestWindow;

    while ((node != NULL) && (nodeCount < SETTINGS_FLASH_MAX_MUSHROOM_NODES)) {
        snapshot->nodes[nodeCount].humidity_cv = node->humidity_cv;
        snapshot->nodes[nodeCount].fan_cv = node->fan_cv;
        snapshot->nodes[nodeCount].time = node->time;
        snapshot->nodes[nodeCount].progress = node->progress;
        snapshot->nodes[nodeCount].type = (uint8_t)node->type;

        if (node == mushroomSettings->current_node) {
            snapshot->currentNodeIndex = nodeCount;
        }

        node = node->next;
        nodeCount++;
    }
}

static void restore_mushroom_settings(const settings_mushroom_snapshot_t *snapshot, mushroom_settings_t *mushroomSettings) {
    uint8_t nodeCount;
    uint8_t currentNodeIndex;

    if (mushroomSettings == NULL) {
        return;
    }

    memset(restoredMushroomNodes, 0xFF, sizeof(restoredMushroomNodes));
    memset(&restoredMushroomProfile, 0x00, sizeof(restoredMushroomProfile));
    restoredMushroomSettings.current_profile = NULL;
    restoredMushroomSettings.current_node = NULL;

    if ((snapshot == NULL) || (snapshot->active == 0U) || (snapshot->nodeCount == 0U)) {
        return;
    }

    nodeCount = snapshot->nodeCount;
    if (nodeCount > SETTINGS_FLASH_MAX_MUSHROOM_NODES) {
        nodeCount = SETTINGS_FLASH_MAX_MUSHROOM_NODES;
    }

    restoredMushroomProfile.duration = snapshot->duration;
    restoredMushroomProfile.progress = snapshot->progress;
    restoredMushroomProfile.estimatedHarvestWindow = snapshot->estimatedHarvestWindow;
    strncpy(restoredMushroomProfile.name, snapshot->name, sizeof(restoredMushroomProfile.name));
    restoredMushroomProfile.name[sizeof(restoredMushroomProfile.name) - 1U] = '\0';
    restoredMushroomProfile.head = &restoredMushroomNodes[0];

    for (uint8_t i = 0U; i < nodeCount; i++) {
        restoredMushroomNodes[i].humidity_cv = snapshot->nodes[i].humidity_cv;
        restoredMushroomNodes[i].fan_cv = snapshot->nodes[i].fan_cv;
        restoredMushroomNodes[i].time = snapshot->nodes[i].time;
        restoredMushroomNodes[i].progress = snapshot->nodes[i].progress;
        restoredMushroomNodes[i].type = (node_type_e)snapshot->nodes[i].type;
        restoredMushroomNodes[i].next = (i + 1U < nodeCount) ? &restoredMushroomNodes[i + 1U] : NULL;
    }

    currentNodeIndex = snapshot->currentNodeIndex;
    if (currentNodeIndex >= nodeCount) {
        currentNodeIndex = 0U;
    }

    restoredMushroomSettings.current_profile = &restoredMushroomProfile;
    restoredMushroomSettings.current_node = &restoredMushroomNodes[currentNodeIndex];
    mushroomSettings->current_profile = restoredMushroomSettings.current_profile;
    mushroomSettings->current_node = restoredMushroomSettings.current_node;
}

static uint8_t count_mushroom_nodes(const MGP_t *profile) {
    const MGP_node_t *current;
    uint8_t count = 0U;

    if (profile == NULL) {
        return 0U;
    }

    current = profile->head;
    while ((current != NULL) && (count < SETTINGS_FLASH_MAX_MUSHROOM_NODES)) {
        count++;
        current = current->next;
    }

    return count;
}

