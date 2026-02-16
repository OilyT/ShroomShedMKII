// SCD40_API.h - API for SCD40 CO2 sensor

#ifndef SCD40_API_H
#define SCD40_API_H

#include <stdbool.h>
#include <stdint.h>
#include "main.h"
#include "stm32h5xx_hal_i2c.h"
#include "SCD40_driver.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SCD40_I2C_HANDLE hi2c3
extern I2C_HandleTypeDef SCD40_I2C_HANDLE;

typedef struct
{
	uint16_t co2_ppm;
	float temperature_c;
	float humidity_rh;
} SCD40_Measurement_t;

bool Init_SCD40(void);
uint16_t get_co2(void);

#ifdef __cplusplus
}
#endif

#endif /* SCD40_API_H */