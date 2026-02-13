/**
******************************************************************************
* @file           : sensors.c
* @brief          : Sensors implementation
******************************************************************************
*/

#include "sensors.h"
#include "main.h"
#include "driver_sht31.h"
#include "shroomshed.h"
#include "driver_sht31_basic.h"
#include "driver_sht31_shot.h"
#include "stdint.h"
#include <stdint.h>


uint8_t init_res;
uint8_t sn[4];
float temperature;
float humidity;
char err_buffer[200];


void init_sensors(void) {
    init_res = sht31_shot_init(SHT31_ADDRESS_1);
    if (init_res != 0) {
        sprintf(err_buffer, "Failed to initialize SHT31 sensor - Error code: %d\r\n", init_res);
        //CDC_Transmit_FS((uint8_t*)usb_buffer, strlen(usb_buffer));
    } else {
        //sprintf(&usb_buffer, "SHT31 sensor initialized successfully\r\n");
        //CDC_Transmit_FS((uint8_t*)usb_buffer, strlen(usb_buffer));
    }

    sht31_shot_get_serial_number(sn);
    //sprintf(&usb_buffer, "sht31: serial number is 0x%02X 0x%02X 0x%02X 0x%02X.\r\n", sn[0], sn[1], sn[2], sn[3]);
    //CDC_Transmit_FS((uint8_t*)usb_buffer, strlen(usb_buffer));
    
    HAL_Delay(500);
}

void read_sensors(void) {
    if (sht31_shot_read(&temperature, &humidity)) {
        //sprintf(&usb_buffer, "Failed to read from SHT31 sensor\r\n");
        //CDC_Transmit_FS((uint8_t*)usb_buffer, strlen(usb_buffer));
    } else {
        //sprintf(&usb_buffer, "SHT31 Read Result: %d, Temperature: %d C, Humidity: %d %%\r\n", res, (int16_t)temperature, (int16_t)humidity);
        //CDC_Transmit_FS((uint8_t*)usb_buffer, strlen(usb_buffer));
        shroomShed.temperatureCurrent = temperature;
        shroomShed.humidityCurrent = humidity;  
    } 
}
    


