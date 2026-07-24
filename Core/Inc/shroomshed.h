/* USER CODE BEGIN Header */
/**
******************************************************************************
* @file           : shroom_shed.h
* @brief          : Header for shroom_shed.c file.
*                   This file contains structs and defines for the shroom shed
******************************************************************************
*/


#ifndef __SHROOMSHED_H
#define __SHROOMSHED_H

#include <sys/_intsup.h>
#ifdef __cplusplus
extern "C" {   
#endif

#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "usbd_cdc_if.h"
#include "rgb.h"
#include "mushroom.h"

// system polling
#define SYSTICK_HZ 1000
#define TOUCH_PROCESS_HZ 500
#define SERIAL_PROCESS_HZ 2
#define DISPLAY_PROCESS_HZ 30
#define SENSOR_PROCESS_HZ 1
#define CONTROL_PROCESS_HZ 1
#define RGB_PROCESS_HZ 100



extern USBD_HandleTypeDef hUsbDeviceFS;
extern struct shedState_t shedState;
extern struct shedSettings_t shedSettings;
extern struct shedControl_t shedControl;

typedef enum shedControlMode_e {
    MODE_AUTOMATIC = 0,
    MODE_MANUAL = 1
} shedControlMode_e;

typedef enum shedOutputMode_e {
    OUTPUT_NORMAL = 0,
    OUTPUT_DISABLED = 1
} shedOutputMode_e;

typedef struct shedControl_t {
    shedControlMode_e controlMode; // 0 for automatic, 1 for manual
    shedOutputMode_e outputMode; // 0 for normal, 1 for disabled
    uint8_t humidityControlValue;
    uint8_t fanControlValue;
    uint8_t manualHumidityControlValue;
    uint8_t manualFanControlValue;
} shedControl_t;

typedef struct shedState_t {
    float humidityCurrent;
    float temperatureCurrent;
    uint16_t co2Current;
    bool waterState;
} shedState_t;

typedef struct shedSettings_t {
    uint8_t lowWaterTimeout; // minutes
    RGB_disco_settings_t *rgbSettings;
    shedControl_t *controlSettings;
    mushroom_settings_t *mushroomSettings;
} shedSettings_t;



void init_shroomshed(void);
void loop(void);




#ifdef __cplusplus
}
#endif

#endif /* __SHROOMSHED_H */