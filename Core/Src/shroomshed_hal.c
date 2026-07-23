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

// humidity PID
#define PID_ID_PERIOD 180 // seconds
#define MAX_PULSE 1100
#define MIN_PULSE 600
#define PULSE_RANGE (MAX_PULSE - MIN_PULSE)
#define MAX_POWER 1000


void set_humidifier_power(uint16_t power) {
    uint16_t counter_register_power = power / (MAX_POWER / PULSE_RANGE) + MIN_PULSE;
    TRANSDUCER_PWM_TIMER.Instance->CCR3 = counter_register_power;
}

void humidity_process(uint8_t humidity_setpoint) {
    const static float Pk = 100.0;
    const static float Ik = 2.0;
    const static float Dk = 100.0;

    static uint16_t ID_counter = 0;
    float P_term = 0;
    static float I_term = 0;
    static float D_term = 0;

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