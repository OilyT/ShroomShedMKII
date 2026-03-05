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
#include "stdint.h"
#include <stdint.h>


uint8_t init_res;

float temperature;
float humidity;
uint16_t co2;

char err_buffer[200];


void init_sensors(void) {
    init_res = sht31_shot_init(SHT31_ADDRESS_0);
    if (init_res != 0) {
        sprintf(err_buffer, "Failed to initialize SHT31 sensor - Error code: %d\r\n", init_res);
    }

    if (!Init_SCD40()) {
        sprintf(err_buffer, "Failed to initialize SCD40 sensor - No serial number detected\r\n");
    }
}

void read_sensors(void) {
    if (!sht31_shot_read(&temperature, &humidity)) {
        shroomShed.temperatureCurrent = temperature;
        shroomShed.humidityCurrent = humidity;  
    }

    /*
    co2 = get_co2();
    if (co2 != 0) {
        shroomShed.co2Current = co2;
    }
    */

}
    


