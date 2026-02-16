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

#ifdef __cplusplus
extern "C" {   
#endif


#include <stdint.h>
#include <stdbool.h>


struct shroomShed_t {

    float humidityCurrent;
    float temperatureCurrent;
    uint16_t co2Current;
    uint8_t humidityControlvalue;
    uint8_t fanSpeed;

    bool waterState;
};

extern struct shroomShed_t shroomShed;
extern char usb_buffer[200];


#ifdef __cplusplus
}
#endif

#endif /* __SHROOMSHED_H */