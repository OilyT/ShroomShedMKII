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

// system polling
#define SYSTICK_HZ 1000
#define TOUCH_PROCESS_HZ 200
#define SERIAL_PROCESS_HZ 2
#define DISPLAY_PROCESS_HZ 50
#define SENSOR_PROCESS_HZ 1
#define CONTROL_PROCESS_HZ 1
#define RGB_PROCESS_HZ 100

#define TRANSDUCER_PWM_TIMER htim3
#define FAN_PWM_TIMER htim1

extern TIM_HandleTypeDef TRANSDUCER_PWM_TIMER;
extern TIM_HandleTypeDef FAN_PWM_TIMER;

extern USBD_HandleTypeDef hUsbDeviceFS;
extern struct shroomShed_t shroomShed;


typedef struct shroomShedSettings_t {
    uint8_t lowWaterTimeout; // minutes
    RGB_disco_settings_t *discoSettings;
} shroomShedSettings_t;


typedef struct shroomShed_t {
    float humidityCurrent;
    float temperatureCurrent;
    uint16_t co2Current;
    uint8_t humidityControlValue;
    uint8_t fanSpeed;
    bool waterState;
    bool shedManualMode;
    shroomShedSettings_t *settings;
} shroomShed_t;

typedef struct MGP_node_t {
    uint8_t humidity_cv;
    uint8_t fan_speed;
    uint16_t time; // hours
    struct MGP_node_t *next;
} MGP_node_t;


typedef struct MGP_t {
    MGP_node_t *head;
    char name[20];
} MGP_t;




void init_shroomshed(void);
void loop(void);



#ifdef __cplusplus
}
#endif

#endif /* __SHROOMSHED_H */