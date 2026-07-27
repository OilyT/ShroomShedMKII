/**
******************************************************************************
* @file           : sensors.c
* @brief          : Sensors implementation
******************************************************************************
*/

#include "sensors.h"
#include "main.h"
#include "SCD40_API.h"
#include "shroomshed.h"
#include "driver_sht31_basic.h"
#include "driver_sht31_shot.h"
#include "driver_sht31.h"
#include "stdint.h"
#include <stdint.h>
#include "shroomshed_hal.h"



#define HEATER_THRESHOLD 96 // % RH
#define HEATER_ON_TIME 5 // cycles
#define HEATER_COOLDOWN 15 // cycles
#define HEATER_TIMEOUT 30 // cycles

#define HUMIDITY_BUFFER_SIZE 4


uint8_t init_res;

float temperature;
float humidity;
static float humidity_buffer[HUMIDITY_BUFFER_SIZE] = {0};
static uint8_t humidity_buffer_index;
uint16_t co2;

char err_buffer[200];


static bool read_temperature_humidity(void);
static bool sensor_heater_process(void);


void init_sensors(void) {
    init_res = sht31_shot_init(SHT31_ADDRESS_0);
    if (init_res != 0) {
        sprintf(err_buffer, "Failed to initialize SHT31 sensor - Error code: %d\r\n", init_res);
    }
    if (!Init_SCD40()) {
        sprintf(err_buffer, "Failed to initialize SCD40 sensor - No serial number detected\r\n");
    }
}


void sensor_process(void) {
    if (read_temperature_humidity()) {
        if (!sensor_heater_process()) { // don't load values if in a heater cycle
            humidity_buffer[humidity_buffer_index] = humidity;
            humidity_buffer_index = (humidity_buffer_index + 1) % HUMIDITY_BUFFER_SIZE;
            float humidity_sum = 0;
            for (uint8_t i = 0; i < HUMIDITY_BUFFER_SIZE; i++) {
                humidity_sum += humidity_buffer[i];
            }
            float humidity_avg = humidity_sum / HUMIDITY_BUFFER_SIZE;

            shedState.humidityCurrent = humidity_avg;
            shedState.temperatureCurrent = temperature;
        }
    } else {
        //disable_shed(); // if sensor read fails disable shed to prevent excessive humidification
        sht31_shot_init(SHT31_ADDRESS_0);
    }
    /*
    co2 = get_co2();
    if (co2 != 0) {
        shedState.co2Current = co2;
    }
    */
}


bool read_temperature_humidity(void) {
    if (!sht31_shot_read(&temperature, &humidity)) {
        return true;
    } else {
        return false;
    }
}


static bool sensor_heater_process(void) {

    static uint8_t heaterCycles = 0;
    static uint8_t heaterCoolDownCycles;
    static bool heaterCycleActive = false;
    static bool heaterActive = false;
    static float entryTemp;

    if (heaterCycleActive) {
        if (heaterActive) {
            heaterCycles++;
            if (heaterCycles >= HEATER_ON_TIME) {
                sht31_shot_set_heater(SHT31_BOOL_FALSE);
                heaterActive = false;
            }
        }
        if ((fabs(temperature - entryTemp) <= 0.5) || (heaterCycles >= HEATER_TIMEOUT)) {
            heaterCycleActive = false;
            heaterCoolDownCycles = HEATER_COOLDOWN;
        }
        return true;
    } else {
        if (heaterCoolDownCycles != 0) {
            heaterCoolDownCycles--;
        } else {
            if (humidity > HEATER_THRESHOLD) {
                heaterCycleActive = true;
                entryTemp = temperature;
                sht31_shot_set_heater(SHT31_BOOL_TRUE);
                heaterActive = true;
                heaterCycles = HEATER_ON_TIME;
            }
        }
        return false;
    }
}
    

