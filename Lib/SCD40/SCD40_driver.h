// SCD40 hardware driver

#ifndef SCD40_H
#define SCD40_H

#include "main.h"
#include "stm32h5xx_hal_i2c.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>



// SCD40 COMMAND TABLE
#define SCD40_CMD_START_PERIODIC_MEASUREMENT           0x21B1
#define SCD40_CMD_START_LOW_POWER_PERIODIC_MEASUREMENT 0x21AC
#define SCD40_CMD_READ_MEASUREMENT                     0xEC05
#define SCD40_CMD_STOP_PERIODIC_MEASUREMENT            0x3F86
#define SCD40_CMD_SET_TEMPERATURE_OFFSET               0x241D
#define SCD40_CMD_GET_TEMPERATURE_OFFSET               0x2318
#define SCD40_CMD_SET_SENSOR_ALTITUDE                  0x2427
#define SCD40_CMD_GET_SENSOR_ALTITUDE                  0x2322
#define SCD40_CMD_SET_AMBIENT_PRESSURE                 0xE000
#define SCD40_CMD_GET_DATA_READY_STATUS                0xE4B8
#define SCD40_CMD_PERSIST_SETTINGS                     0x3615
#define SCD40_CMD_GET_SERIAL_NUMBER                    0x3682
#define SCD40_CMD_PERFORM_SELF_TEST                    0x3639
#define SCD40_CMD_PERFORM_FACTORY_RESET                0x3632
#define SCD40_CMD_REINIT                               0x3646
#define SCD40_CMD_MEASURE_SINGLE_SHOT                  0x219D
#define SCD40_CMD_MEASURE_SINGLE_SHOT_RHT_ONLY         0x2196
#define SCD40_CMD_SET_AUTOMATIC_SELF_CALIBRATION       0x2416
#define SCD40_CMD_GET_AUTOMATIC_SELF_CALIBRATION       0x2313

#define SCD40_I2C_ADDR                                (0x62U << 1)
#define SCD40_I2C_TIMEOUT_MS                          100U

typedef struct
{
	I2C_HandleTypeDef *hi2c;
	uint16_t i2c_addr;
	uint16_t serial_number[3];
	float temperature_offset_c;
	uint16_t sensor_altitude_m;
	bool automatic_self_calibration_enabled;
} SCD40_Handle;

HAL_StatusTypeDef SCD40_StartPeriodicMeasurement(SCD40_Handle *dev);
HAL_StatusTypeDef SCD40_StartLowPowerPeriodicMeasurement(SCD40_Handle *dev);
HAL_StatusTypeDef SCD40_StopPeriodicMeasurement(SCD40_Handle *dev);
HAL_StatusTypeDef SCD40_ReadMeasurement(SCD40_Handle *dev, uint16_t *co2_ppm,
										float *temperature_c, float *humidity_rh);
HAL_StatusTypeDef SCD40_GetDataReadyStatus(SCD40_Handle *dev, bool *data_ready);

HAL_StatusTypeDef SCD40_SetTemperatureOffset(SCD40_Handle *dev, float offset_c);
HAL_StatusTypeDef SCD40_GetTemperatureOffset(SCD40_Handle *dev, float *offset_c);
HAL_StatusTypeDef SCD40_SetSensorAltitude(SCD40_Handle *dev, uint16_t altitude_m);
HAL_StatusTypeDef SCD40_GetSensorAltitude(SCD40_Handle *dev, uint16_t *altitude_m);
HAL_StatusTypeDef SCD40_SetAmbientPressure(SCD40_Handle *dev, uint16_t pressure_hpa);

HAL_StatusTypeDef SCD40_PersistSettings(SCD40_Handle *dev);
HAL_StatusTypeDef SCD40_GetSerialNumber(SCD40_Handle *dev, uint16_t serial[3]);
HAL_StatusTypeDef SCD40_PerformSelfTest(SCD40_Handle *dev, uint16_t *result);
HAL_StatusTypeDef SCD40_PerformFactoryReset(SCD40_Handle *dev);
HAL_StatusTypeDef SCD40_Reinit(SCD40_Handle *dev);

HAL_StatusTypeDef SCD40_MeasureSingleShot(SCD40_Handle *dev);
HAL_StatusTypeDef SCD40_MeasureSingleShotRhtOnly(SCD40_Handle *dev);
HAL_StatusTypeDef SCD40_SetAutomaticSelfCalibration(SCD40_Handle *dev, bool enable);
HAL_StatusTypeDef SCD40_GetAutomaticSelfCalibration(SCD40_Handle *dev, bool *enable);


#endif


