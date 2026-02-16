
#include "main.h"
#include "stm32h5xx_hal_i2c.h"
#include "SCD40_driver.h"
#include "SCD40_API.h"
#include <stdint.h>

SCD40_Handle scd40;

bool Init_SCD40(void) {

    scd40.hi2c = &SCD40_I2C_HANDLE;
	scd40.i2c_addr = SCD40_I2C_ADDR;
    SCD40_StopPeriodicMeasurement(&scd40);
    HAL_Delay(500);

    SCD40_GetTemperatureOffset(&scd40, &scd40.temperature_offset_c);
    SCD40_GetSensorAltitude(&scd40, &scd40.sensor_altitude_m);
    SCD40_GetAutomaticSelfCalibration(&scd40, &scd40.automatic_self_calibration_enabled);
    SCD40_GetSerialNumber(&scd40, scd40.serial_number);

    if (!scd40.serial_number[0] && !scd40.serial_number[1] && !scd40.serial_number[2]) {
        // Failed to initialize SCD40 sensor - No serial number detected
        return false;
    }

    if (scd40.automatic_self_calibration_enabled)
    {
        SCD40_SetAutomaticSelfCalibration(&scd40, false);
        SCD40_GetAutomaticSelfCalibration(&scd40, &scd40.automatic_self_calibration_enabled);

    }
    SCD40_StartPeriodicMeasurement(&scd40);

    return true;
}

uint16_t get_co2(void) {
    uint16_t co2_ppm = 0;
    float temperature_c, humidity_rh;
    bool data_ready;

    if (SCD40_GetDataReadyStatus(&scd40, &data_ready) == HAL_OK && data_ready) {
        SCD40_ReadMeasurement(&scd40, &co2_ppm, &temperature_c, &humidity_rh);
    }

    return co2_ppm;
}




