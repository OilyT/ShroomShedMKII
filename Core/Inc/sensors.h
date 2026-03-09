/**
******************************************************************************
* @file           : sensors.h
* @brief          : Sensors implementation
******************************************************************************
*/

#ifndef __SENSORS_H
#define __SENSORS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "shroomshed.h"
#include "stm32h5xx_hal.h"


void sensor_process(void);
void init_sensors(void);

extern struct shroomShed_t shroomShed;


#ifdef __cplusplus
}
#endif

#endif /* __SENSORS_H */
