
/**
******************************************************************************
* @file           : shroomshed_hal.h
* @brief          : Header for shroomshed_hal.c file.
*                   This file contains function prototypes for shroomshed hardware abstraction layer
******************************************************************************
*/

#ifndef __SHROOMSHED_HAL_H
#define __SHROOMSHED_HAL_H

#include <stdint.h>
#include "main.h"
#include "stm32h5xx_hal.h"
#include "rgb.h"
#include "shroomshed.h"

#define TRANSDUCER_PWM_TIMER htim3
#define FAN_PWM_TIMER htim1


extern TIM_HandleTypeDef TRANSDUCER_PWM_TIMER;
extern TIM_HandleTypeDef FAN_PWM_TIMER;

typedef struct {
    uint8_t humidity_cv;
    uint8_t fan_cv;
    uint16_t time;
    uint16_t progress;
    uint8_t type;
    uint8_t reserved;
} settings_mushroom_node_t;

typedef struct {
    uint8_t active;
    uint8_t currentNodeIndex;
    uint8_t nodeCount;
    uint8_t reserved;
    char name[20];
    uint16_t duration;
    uint16_t progress;
    uint16_t estimatedHarvestWindow;
    settings_mushroom_node_t nodes[100];
} settings_mushroom_snapshot_t;

typedef struct {
    uint32_t magic;
    uint32_t version;
    uint8_t lowWaterTimeout;
    uint8_t reserved[3];
    RGB_disco_settings_t rgbSettings;
    shedControl_t controlSettings;
    settings_mushroom_snapshot_t mushroomSettings;
} settings_flash_blob_t;

void enable_shed(void);
void disable_shed(void);
void start_humidifier(void);
void humidity_process(uint8_t humidity_setpoint);
void stop_humidifier(void);
void enable_boost(void);
void disable_boost(void);
void start_fan(void);
void set_fan_speed(uint8_t speed);
void stop_fan(void);







#endif /* __SHROOMSHED_HAL_H */