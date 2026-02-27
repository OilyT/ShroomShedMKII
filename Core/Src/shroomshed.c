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
#include "main.h"
#include "shroomshed.h"
#include "display_manager.h"
#include "screens.h"
#include "sensors.h"
#include "ili9341_touch.h"
#include "ili9341.h"
#include "stm32h5xx_hal_gpio.h"
#include "stm32h5xx_hal_tim.h"
#include "rgb.h"


/* ============================================================================
 * Defines and Typedefs
 * ============================================================================ */


// humidity PID
#define PID_ID_PERIOD 2 // seconds
#define MAX_PULSE 1200
#define MIN_PULSE 300
#define PULSE_RANGE (MAX_PULSE - MIN_PULSE)
#define PID_MODIFIER 100

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

struct shroomShed_t shroomShed;

uint8_t usb_buffer[200];


/* ============================================================================
 * Function Prototypes
 * ============================================================================ */
void init_pwm(void);
void humidity_control(void);
/* ============================================================================
 * Function Implementations
 * ============================================================================ */

void init_shroomshed(void) {
    shroomShed.temperatureCurrent = 15.0f;
    shroomShed.humidityCurrent = 40.0f;
    shroomShed.co2Current = 0;
    shroomShed.humidityControlvalue = 90;
    shroomShed.fanSpeed = 15;
    shroomShed.waterState = true;

    initDisplay();

    //uint32_t min_x, min_y, max_x, max_y;
    //calibrate_touch(&min_x, &min_y, &max_x, &max_y);
    //sprintf(usb_buffer, " Min X: %lu, Max X: %lu, Min Y: %lu, Max Y: %lu\r\n", min_x, max_x, min_y, max_y);

    displayProcess();
    init_sensors();
    init_pwm();
    RGB_Init();

    switch_screen(SCREEN_ID_MAIN);
}

void loop(void)
{
    /* Initialize */
    
    /* Main loop */

    if (lastDisplayProcess + (SYSTICK_HZ/DISPLAY_PROCESS_HZ) < HAL_GetTick()) {
        lastDisplayProcess = HAL_GetTick();
        displayProcess();
    }

    if (lastSensorProcess + (SYSTICK_HZ/SENSOR_PROCESS_HZ) < HAL_GetTick()) {
        lastSensorProcess = HAL_GetTick();
        read_sensors();
    }
    
    if (lastTouchProcess + (SYSTICK_HZ/TOUCH_PROCESS_HZ) < HAL_GetTick()) {
        lastTouchProcess = HAL_GetTick();
        poll_touchpad();
    }

    if (lastControlProcess + (SYSTICK_HZ/CONTROL_PROCESS_HZ) < HAL_GetTick()) {
        lastControlProcess = HAL_GetTick();
        humidity_control();
    }

    if (lastSerialProcess + (SYSTICK_HZ/SERIAL_PROCESS_HZ) < HAL_GetTick()) {
        lastSerialProcess = HAL_GetTick();
            if (hUsbDeviceFS.pClassData != NULL) {
            TEMPLATE_Transmit(usb_buffer, sizeof(usb_buffer));
            memset(usb_buffer, 0, sizeof(usb_buffer));
        }
    }

    if (lastRgbProcess + (SYSTICK_HZ/RGB_PROCESS_HZ) < HAL_GetTick()) {
        lastRgbProcess = HAL_GetTick();
        RGB_Process();
    }
    /* Cleanup */
}

/* ============================================================================
 * Local Function Implementations
 * ============================================================================ */

 void humidity_control(void) {
    // humidifier PID control
    uint16_t Pk = 10;
    uint16_t Ik = 1;
    uint16_t Dk = 100;
    static uint16_t counter = 0;
    static int32_t lastError = 0;

    bool printSerial = false;

    int32_t PID_output = 0;
    int32_t P_term = 0;
    static int32_t I_term = 0;
    static int32_t D_term = 0;

    int32_t error = (shroomShed.humidityControlvalue*PID_MODIFIER) - (shroomShed.humidityCurrent*PID_MODIFIER);

    P_term = (Pk * error);

    if (counter >= CONTROL_PROCESS_HZ * PID_ID_PERIOD) {
        I_term += (Ik * error);
        if (I_term > PULSE_RANGE*PID_MODIFIER) {
            I_term = PULSE_RANGE*PID_MODIFIER;
        } else if (I_term < 0) {
            I_term = 0;
        }
        D_term = (Dk * (error - lastError));
        lastError = error;
        printSerial = true;
        counter = 0;
    } else {
        counter++;
    }

    PID_output = P_term/PID_MODIFIER + I_term/PID_MODIFIER + D_term/PID_MODIFIER + MIN_PULSE;
    if (PID_output < MIN_PULSE) {
        PID_output = MIN_PULSE;
    } else if (PID_output > MAX_PULSE) {
        PID_output = MAX_PULSE;
    }

    if (printSerial) {
        //sprintf(usb_buffer, "Error: %d, P: %d, I: %d, D: %d, Output: %d\r\n", error/PID_MODIFIER, P_term/PID_MODIFIER, I_term/PID_MODIFIER, D_term/PID_MODIFIER, PID_output);
    }
    
    // load pulse value into timer register
    TRANSDUCER_PWM_TIMER.Instance->CCR3 = (PID_output);
 }

 void init_pwm(void) {
    HAL_TIM_PWM_Start(&TRANSDUCER_PWM_TIMER, TIM_CHANNEL_3);

 }

