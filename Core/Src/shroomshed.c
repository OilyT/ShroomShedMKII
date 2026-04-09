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
#include "ili9341_touch.h"
#include "ili9341.h"
#include "rgb.h"
#include "mushroom.h"
#include "stm32h5xx_hal.h"


/* ============================================================================
 * Defines and Typedefs
 * ============================================================================ */


// humidity PID
#define PID_ID_PERIOD 1 // seconds
#define MAX_PULSE 1100
#define MIN_PULSE 600
#define PULSE_RANGE (MAX_PULSE - MIN_PULSE)
#define PID_MODIFIER 100
#define RATE_LIMIT 20 // percent per cycle
/* ============================================================================
 * Static Variables
 * ============================================================================ */
uint32_t currentSystick;
uint32_t lastSerialProcess;
uint32_t lastTouchProcess;
uint32_t lastDisplayProcess;
uint32_t lastControlProcess;
uint32_t lastSensorProcess;
uint32_t lastRgbProcess;

uint8_t usb_buffer[100];

/* ============================================================================
 * Global Structs
 * ============================================================================ */
struct shedState_t shedState = {
    .temperatureCurrent = 0,
    .humidityCurrent = 0,
    .co2Current = 0,
    .waterState = true
};
struct shedSettings_t shedSettings = {
    .lowWaterTimeout = 10
};
struct shedControl_t shedControl = {
    .controlMode = MODE_MANUAL,
    .outputMode = OUTPUT_NORMAL,
    .humidityControlValue = 90,
    .fanControlValue = 20,
    .manualHumidityControlValue = 85,
    .manualFanControlValue = 20
};


/* ============================================================================
 * Function Prototypes
 * ============================================================================ */
static void shed_control(void);
static void init_pwm(void);
static void humidity_control(void);
static void fan_control(void);
static void determine_water_state(void);
/* ============================================================================
 * Function Implementations
 * ============================================================================ */

void init_shroomshed(void) {

    initDisplay();
    displayProcess();
    init_sensors();
    init_pwm();
    RGB_Init();
    init_mushrooms();
    HAL_Delay(2000);
    switch_screen(SCREEN_ID_MAIN);
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
        sensor_process ();
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
            //TEMPLATE_Transmit(usb_buffer, sizeof(usb_buffer));
            //memset(usb_buffer, 0, sizeof(usb_buffer));
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

static void shed_control (void) {
    if (shedControl.controlMode == MODE_AUTOMATIC) {
        tick_MGP();
    } else {
        shedControl.humidityControlValue = shedControl.manualHumidityControlValue;
        shedControl.fanControlValue = shedControl.manualFanControlValue;
    }
    
    humidity_control();
    determine_water_state();
    fan_control();
}

static void humidity_control(void) {
    // humidifier PID control
    const static uint16_t Pk = 50;
    const static uint16_t Ik = 1; 
    const static uint16_t Dk = 100;
    const static uint16_t rate_limit = RATE_LIMIT * PULSE_RANGE / 100;

    static uint16_t counter = 0;
    static int32_t lastError = 0;

    bool printSerial = false;

    int32_t PID_output = 0;
    static int32_t rate_limited_PID_output = 0;


    int32_t P_term = 0;
    static int32_t I_term = 0;
    static int32_t D_term = 0;

    int32_t error = (shedControl.humidityControlValue*PID_MODIFIER) - (shedState.humidityCurrent*PID_MODIFIER);

    P_term = (Pk * error);
    if (P_term > PULSE_RANGE * PID_MODIFIER) {
        P_term = PULSE_RANGE * PID_MODIFIER;
    } else if (P_term < - (PULSE_RANGE * PID_MODIFIER)) {
        P_term = -(PULSE_RANGE * PID_MODIFIER);
    }

    counter++;
    if (counter >= CONTROL_PROCESS_HZ * PID_ID_PERIOD) {
        // integral
        int16_t I_delta = Ik * error * PID_ID_PERIOD;
        I_delta /= 2;
        I_term += I_delta;

        if (I_term < 0) {
            I_term = 0;
        }
        if (I_term > (PULSE_RANGE * PID_MODIFIER) - P_term) {
            I_term = (PULSE_RANGE * PID_MODIFIER) - P_term;
        }

        // derivative
        int16_t error_delta = error - lastError;
        D_term = Dk * error_delta / PID_ID_PERIOD;


        lastError = error;
        printSerial = true;
        counter = 0;
    }


    PID_output = P_term/PID_MODIFIER + I_term/PID_MODIFIER + D_term/PID_MODIFIER;

    if (PID_output < 0) {
        PID_output = 0;
    } else if (PID_output > PULSE_RANGE) {
        PID_output = PULSE_RANGE;
    }

    // Rate limiting
    int16_t PID_delta = PID_output - rate_limited_PID_output;
    if (PID_delta > rate_limit) {
        rate_limited_PID_output += rate_limit;
    } else if (PID_delta < -rate_limit) {
        rate_limited_PID_output -= rate_limit;
    } else {
        rate_limited_PID_output = PID_output;
    }

    PID_output = rate_limited_PID_output;

    int16_t PID_output_normalised;
    if (PID_output == 0) {
        PID_output_normalised = 0;
    } else {
        PID_output_normalised = (PID_output * 100) / PULSE_RANGE;
    }


    if (printSerial) {
        sprintf(usb_buffer, "Error: %d, P: %d, I: %d, D: %d, Output: %d\r\n", error/10, P_term/PID_MODIFIER, I_term/PID_MODIFIER, D_term/PID_MODIFIER, PID_output);
        //sprintf(usb_buffer, "CV: %d, PV: %.2f, PID: %d, FAN: %d\r\n", shedControl.humidityControlValue, shedState.humidityCurrent, PID_output_normalised, shedControl.fanControlValue);
    }
    // load pulse value into timer register, add min pulse value if not PID_oputput is not 0
    if (PID_output) PID_output += MIN_PULSE;
    TRANSDUCER_PWM_TIMER.Instance->CCR3 = (PID_output);
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
    // LED indicator
    HAL_GPIO_WritePin(WATER_LED_GPIO_Port, WATER_LED_Pin, shedState.waterState ? GPIO_PIN_RESET : GPIO_PIN_SET);  
}


static void fan_control(void) {
    float gamma = 0.7;
    uint16_t pwm_output = pow(shedControl.fanControlValue / 100.0f, gamma) * FAN_PWM_TIMER.Init.Period;
    FAN_PWM_TIMER.Instance->CCR3 = pwm_output;
}


static void init_pwm(void) {
    HAL_TIM_PWM_Start(&TRANSDUCER_PWM_TIMER, TIM_CHANNEL_3);
    HAL_TIMEx_PWMN_Start(&FAN_PWM_TIMER, TIM_CHANNEL_3);  // TIMEx_PWMN_Start is for complementary channel (3N)
}

