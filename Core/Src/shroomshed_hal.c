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


/* ============================================================================
 * Function Implementations
 * ============================================================================ */

void set_humidifier_power(uint16_t power) {
    uint16_t counter_register_power = power / (MAX_POWER / PULSE_RANGE) + MIN_PULSE;
    TRANSDUCER_PWM_TIMER.Instance->CCR3 = counter_register_power;
}

void humidity_process(uint8_t humidity_setpoint) {
    const static float Pk = 100.0;
    const static float Ik = 5.0;
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


void save_settings_to_flash(uint32_t flashAddress) {
    settings_flash_blob_t flashBlob;
    FLASH_EraseInitTypeDef eraseInit = {0};
    uint32_t sectorError = 0;
    uint32_t currentAddress = flashAddress;
    uint32_t endAddress;
    uint32_t programBuffer[(sizeof(settings_flash_blob_t) + (SETTINGS_FLASH_QUADWORD_BYTES - 1U)) / 4U];

    if ((flashAddress % SETTINGS_FLASH_QUADWORD_BYTES) != 0U) {
        return;
    }

    endAddress = flashAddress + (uint32_t)sizeof(settings_flash_blob_t);
    endAddress = (endAddress + (SETTINGS_FLASH_QUADWORD_BYTES - 1U)) & ~(SETTINGS_FLASH_QUADWORD_BYTES - 1U);

    if (!IS_FLASH_USER_MEM_ADDRESS(flashAddress) || !IS_FLASH_USER_MEM_ADDRESS(endAddress - 1U)) {
        return;
    }

    if (HAL_FLASH_Unlock() != HAL_OK) {
        return;
    }

    memset(&flashBlob, 0xFF, sizeof(flashBlob));
    flashBlob.magic = SETTINGS_FLASH_MAGIC;
    flashBlob.version = SETTINGS_FLASH_VERSION;
    flashBlob.lowWaterTimeout = shedSettings.lowWaterTimeout;

    if (shedSettings.rgbSettings != NULL) {
        flashBlob.rgbSettings = *shedSettings.rgbSettings;
    }

    if (shedSettings.controlSettings != NULL) {
        flashBlob.controlSettings = *shedSettings.controlSettings;
    }

    snapshot_mushroom_settings(&flashBlob.mushroomSettings, shedSettings.mushroomSettings);

    memset(programBuffer, 0xFF, sizeof(programBuffer));
    memcpy(programBuffer, &flashBlob, sizeof(flashBlob));

    while (currentAddress < endAddress) {
        uint32_t bankBase;
        uint32_t bank;
        uint32_t sector;

        if (currentAddress < (FLASH_BASE + FLASH_BANK_SIZE)) {
            bank = FLASH_BANK_1;
            bankBase = FLASH_BASE;
        } else {
            bank = FLASH_BANK_2;
            bankBase = FLASH_BASE + FLASH_BANK_SIZE;
        }

        sector = (currentAddress - bankBase) / SETTINGS_FLASH_SECTOR_SIZE;

        eraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;
        eraseInit.Banks = bank;
        eraseInit.Sector = sector;
        eraseInit.NbSectors = 1U;

        if (HAL_FLASHEx_Erase(&eraseInit, &sectorError) != HAL_OK) {
            goto flash_cleanup;
        }

        currentAddress = bankBase + ((sector + 1U) * SETTINGS_FLASH_SECTOR_SIZE);
    }

    for (uint32_t offset = 0U; offset < sizeof(programBuffer); offset += SETTINGS_FLASH_QUADWORD_BYTES) {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_QUADWORD, flashAddress + offset, (uint32_t)(uintptr_t)&((uint8_t *)programBuffer)[offset]) != HAL_OK) {
            goto flash_cleanup;
        }
    }

flash_cleanup:
    HAL_FLASH_Lock();
}

bool load_settings_from_flash(uint32_t flashAddress) {
    const settings_flash_blob_t *flashBlob;

    if ((flashAddress % SETTINGS_FLASH_QUADWORD_BYTES) != 0U) {
        return false;
    }

    if (!IS_FLASH_USER_MEM_ADDRESS(flashAddress) || !IS_FLASH_USER_MEM_ADDRESS(flashAddress + sizeof(settings_flash_blob_t) - 1U)) {
        return false;
    }

    flashBlob = (const settings_flash_blob_t *)flashAddress;
    if ((flashBlob->magic != SETTINGS_FLASH_MAGIC) || (flashBlob->version != SETTINGS_FLASH_VERSION)) {
        return false;
    }

    shedSettings.lowWaterTimeout = flashBlob->lowWaterTimeout;

    if (shedSettings.rgbSettings != NULL) {
        *shedSettings.rgbSettings = flashBlob->rgbSettings;
    }

    if (shedSettings.controlSettings != NULL) {
        *shedSettings.controlSettings = flashBlob->controlSettings;
    }

    restore_mushroom_settings(&flashBlob->mushroomSettings, &restoredMushroomSettings);
    shedSettings.mushroomSettings = &restoredMushroomSettings;

    return true;
}

void snapshot_mushroom_settings(settings_mushroom_snapshot_t *snapshot, const mushroom_settings_t *mushroomSettings) {
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

void restore_mushroom_settings(const settings_mushroom_snapshot_t *snapshot, mushroom_settings_t *mushroomSettings) {
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

