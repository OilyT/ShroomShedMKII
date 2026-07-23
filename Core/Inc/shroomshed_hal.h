
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

#define TRANSDUCER_PWM_TIMER htim3
#define FAN_PWM_TIMER htim1

extern TIM_HandleTypeDef TRANSDUCER_PWM_TIMER;
extern TIM_HandleTypeDef FAN_PWM_TIMER;


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