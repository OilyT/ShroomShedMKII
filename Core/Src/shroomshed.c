/**
 * @file shroomshed.c
 * @brief Main source file for ShroomShed application
 * @author yolo swaggins
 * @date with your mum
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "main.h"
#include "shroomshed.h"
#include "display_manager.h"
#include "screens.h"
#include "sensors.h"
#include "rgb.h"
#include "mushroom.h"
#include "shroomshed_hal.h"
#include "stm32h5xx_hal_flash.h"


/* ============================================================================
 * Defines
 * ============================================================================ */




/* ============================================================================
 * Static Variables
 * ============================================================================ */
static uint32_t currentSystick;
static uint32_t lastSerialProcess;
static uint32_t lastTouchProcess;
static uint32_t lastDisplayProcess;
static uint32_t lastControlProcess;
static uint32_t lastSensorProcess;
static uint32_t lastRgbProcess;

static uint8_t usb_buffer[100];

/* ============================================================================
 * Global Structs
 * ============================================================================ */
struct shedState_t shedState = {
    .temperatureCurrent = 0,
    .humidityCurrent = 0,
    .co2Current = 0,
    .waterState = true
};

struct shedControl_t shedControl = {
    .controlMode = MODE_MANUAL,
    .outputMode = OUTPUT_NORMAL,
    .humidityControlValue = 90,
    .fanControlValue = 20,
    .manualHumidityControlValue = 90,
    .manualFanControlValue = 20
};

struct shedSettings_t shedSettings = {
    .lowWaterTimeout = 15,
    .rgbSettings = &rgbSettings,
    .controlSettings = &shedControl
};


/* ============================================================================
 * Function Prototypes
 * ============================================================================ */
static void shed_control(void);
static void determine_water_state(void);

/* ============================================================================
 * Function Implementations
 * ============================================================================ */

void init_shroomshed(void) {

    init_sensors();
    RGB_Init();
    init_mushrooms();
    initDisplay();
    displayProcess();
    loadScreen(SCREEN_ID_MAIN);

    enable_boost();
    enable_shed();
}

void loop(void)
{    
    currentSystick = HAL_GetTick();
    if (lastDisplayProcess + (SYSTICK_HZ/DISPLAY_PROCESS_HZ) < currentSystick) {
        lastDisplayProcess = currentSystick;
        displayProcess();
    }

    currentSystick = HAL_GetTick();
    if (lastSensorProcess + (SYSTICK_HZ/SENSOR_PROCESS_HZ) < currentSystick) {
        lastSensorProcess = currentSystick;
        sensor_process();
    }

    currentSystick = HAL_GetTick();
    if (lastTouchProcess + (SYSTICK_HZ/TOUCH_PROCESS_HZ) < currentSystick) {
        lastTouchProcess = currentSystick;
        poll_touchpad();
    }

    currentSystick = HAL_GetTick();
    if (lastControlProcess + (SYSTICK_HZ/CONTROL_PROCESS_HZ) < currentSystick) {
        lastControlProcess = currentSystick;
        shed_control();
    }

    currentSystick = HAL_GetTick();
    if (lastSerialProcess + (SYSTICK_HZ/SERIAL_PROCESS_HZ) < currentSystick) {
        lastSerialProcess = currentSystick;
        if (hUsbDeviceFS.pClassData != NULL) {
            TEMPLATE_Transmit(usb_buffer, sizeof(usb_buffer));
            memset(usb_buffer, 0, sizeof(usb_buffer));
        }
    }

    currentSystick = HAL_GetTick(); 
    if (lastRgbProcess + (SYSTICK_HZ/RGB_PROCESS_HZ) < currentSystick) {
        lastRgbProcess = currentSystick;
        RGB_Process();
    }
}

/* ============================================================================
 * Local Function Implementations
 * ============================================================================ */

static void shed_control(void) {

    if (shedControl.outputMode == OUTPUT_DISABLED) {
        // do nothing currently
    } else {
        if (shedControl.controlMode == MODE_AUTOMATIC) {
            tick_MGP();
        } else {
            shedControl.humidityControlValue = shedControl.manualHumidityControlValue;
            shedControl.fanControlValue = shedControl.manualFanControlValue;
        }
        set_fan_speed(shedControl.fanControlValue);
        humidity_process(shedControl.humidityControlValue);
        determine_water_state();
    }
}



static void determine_water_state(void) {
    // Low water detection logic
    uint8_t lowWaterTimeout = shedSettings.lowWaterTimeout;

    uint8_t threshold = 90;
    if (shedControl.humidityControlValue - 5 < threshold) {
        threshold = shedControl.humidityControlValue - 5;
    }
    
    static uint32_t humStart = 0;
    uint32_t humTimeOn = 0;
    static bool belowThreshold = false;
    static bool lastWaterState = true;
    if (shedState.waterState && !lastWaterState) {
        humStart = HAL_GetTick();
        belowThreshold = false;
    }
    lastWaterState = shedState.waterState;

    if (shedState.humidityCurrent < threshold && shedState.waterState) {
        if (!belowThreshold) {
            humStart = HAL_GetTick();
            belowThreshold = true;
        }
        humTimeOn = HAL_GetTick() - humStart;
        if (humTimeOn > (lowWaterTimeout * 60000)) {
            shedState.waterState = false;
        }
    } else {
        belowThreshold = false;
        if (!shedState.waterState && (shedState.humidityCurrent >= threshold)) {
            shedState.waterState = true;
        }
    }

    if (shedControl.outputMode == OUTPUT_DISABLED) {
        shedState.waterState = true;
    }

    // LED indicator
    HAL_GPIO_WritePin(WATER_LED_GPIO_Port, WATER_LED_Pin, shedState.waterState ? GPIO_PIN_RESET : GPIO_PIN_SET);  
}








