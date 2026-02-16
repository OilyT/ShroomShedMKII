
#include "SCD40_driver.h"
#include "stm32h5xx_hal_i2c.h"
#include <stdint.h>

static uint8_t scd40_crc8(const uint8_t *data, uint8_t len)
{
	uint8_t crc = 0xFFU;

	for (uint8_t i = 0; i < len; i++)
	{
		crc ^= data[i];
		for (uint8_t bit = 0; bit < 8U; bit++)
		{
			if ((crc & 0x80U) != 0U)
			{
				crc = (uint8_t)((crc << 1U) ^ 0x31U);
			}
			else
			{
				crc = (uint8_t)(crc << 1U);
			}
		}
	}

	return crc;
}

static HAL_StatusTypeDef scd40_write_command(SCD40_Handle *dev, uint16_t cmd)
{
	uint8_t tx[2];

	tx[0] = (uint8_t)(cmd >> 8U);
	tx[1] = (uint8_t)(cmd & 0xFFU);

	return HAL_I2C_Master_Transmit(dev->hi2c, dev->i2c_addr, tx, sizeof(tx), SCD40_I2C_TIMEOUT_MS);
}

static HAL_StatusTypeDef scd40_write_command_arg(SCD40_Handle *dev, uint16_t cmd, uint16_t arg)
{
	uint8_t tx[5];

	tx[0] = (uint8_t)(cmd >> 8U);
	tx[1] = (uint8_t)(cmd & 0xFFU);
	tx[2] = (uint8_t)(arg >> 8U);
	tx[3] = (uint8_t)(arg & 0xFFU);
	tx[4] = scd40_crc8(&tx[2], 2U);

	return HAL_I2C_Master_Transmit(dev->hi2c, dev->i2c_addr, tx, sizeof(tx), SCD40_I2C_TIMEOUT_MS);
}

static HAL_StatusTypeDef scd40_read_words(SCD40_Handle *dev, uint16_t cmd, uint16_t *data, size_t words)
{
	uint8_t rx[9];
	HAL_StatusTypeDef status;

	if (words == 0U || words > 3U)
	{
		return HAL_ERROR;
	}

	status = scd40_write_command(dev, cmd);
	if (status != HAL_OK)
	{
		return status;
	}

	status = HAL_I2C_Master_Receive(dev->hi2c, dev->i2c_addr, rx, (uint16_t)(words * 3U),
									SCD40_I2C_TIMEOUT_MS);
	if (status != HAL_OK)
	{
		return status;
	}

	for (size_t i = 0; i < words; i++)
	{
		uint8_t *chunk = &rx[i * 3U];
		if (scd40_crc8(chunk, 2U) != chunk[2])
		{
			return HAL_ERROR;
		}
		data[i] = (uint16_t)((uint16_t)chunk[0] << 8U) | (uint16_t)chunk[1];
	}

	return HAL_OK;
}


HAL_StatusTypeDef SCD40_StartPeriodicMeasurement(SCD40_Handle *dev)
{
	return scd40_write_command(dev, SCD40_CMD_START_PERIODIC_MEASUREMENT);
}

HAL_StatusTypeDef SCD40_StartLowPowerPeriodicMeasurement(SCD40_Handle *dev)
{
	return scd40_write_command(dev, SCD40_CMD_START_LOW_POWER_PERIODIC_MEASUREMENT);
}

HAL_StatusTypeDef SCD40_StopPeriodicMeasurement(SCD40_Handle *dev)
{
	return scd40_write_command(dev, SCD40_CMD_STOP_PERIODIC_MEASUREMENT);
}

HAL_StatusTypeDef SCD40_ReadMeasurement(SCD40_Handle *dev, uint16_t *co2_ppm,
										float *temperature_c, float *humidity_rh)
{
	uint16_t words[3];
	HAL_StatusTypeDef status = scd40_read_words(dev, SCD40_CMD_READ_MEASUREMENT, words, 3U);

	if (status != HAL_OK)
	{
		return status;
	}

	if (co2_ppm != NULL)
	{
		*co2_ppm = words[0];
	}

	if (temperature_c != NULL)
	{
		*temperature_c = -45.0f + (175.0f * ((float)words[1] / 65535.0f));
	}

	if (humidity_rh != NULL)
	{
		*humidity_rh = 100.0f * ((float)words[2] / 65535.0f);
	}

	return HAL_OK;
}

HAL_StatusTypeDef SCD40_GetDataReadyStatus(SCD40_Handle *dev, bool *data_ready)
{
	uint16_t status;
	HAL_StatusTypeDef result = scd40_read_words(dev, SCD40_CMD_GET_DATA_READY_STATUS, &status, 1U);

	if (result != HAL_OK)
	{
		return result;
	}

	if (data_ready != NULL)
	{
		*data_ready = ((status & 0x07FFU) != 0U);
	}

	return HAL_OK;
}

HAL_StatusTypeDef SCD40_SetTemperatureOffset(SCD40_Handle *dev, float offset_c)
{
	uint16_t raw = (uint16_t)((offset_c * 65535.0f) / 175.0f);
	return scd40_write_command_arg(dev, SCD40_CMD_SET_TEMPERATURE_OFFSET, raw);
}

HAL_StatusTypeDef SCD40_GetTemperatureOffset(SCD40_Handle *dev, float *offset_c)
{
	uint16_t raw;
	HAL_StatusTypeDef status = scd40_read_words(dev, SCD40_CMD_GET_TEMPERATURE_OFFSET, &raw, 1U);

	if (status != HAL_OK)
	{
		return status;
	}

	if (offset_c != NULL)
	{
		*offset_c = 175.0f * ((float)raw / 65535.0f);
	}

	return HAL_OK;
}

HAL_StatusTypeDef SCD40_SetSensorAltitude(SCD40_Handle *dev, uint16_t altitude_m)
{
	return scd40_write_command_arg(dev, SCD40_CMD_SET_SENSOR_ALTITUDE, altitude_m);
}

HAL_StatusTypeDef SCD40_GetSensorAltitude(SCD40_Handle *dev, uint16_t *altitude_m)
{
	uint16_t raw;
	HAL_StatusTypeDef status = scd40_read_words(dev, SCD40_CMD_GET_SENSOR_ALTITUDE, &raw, 1U);

	if (status != HAL_OK)
	{
		return status;
	}

	if (altitude_m != NULL)
	{
		*altitude_m = raw;
	}

	return HAL_OK;
}

HAL_StatusTypeDef SCD40_SetAmbientPressure(SCD40_Handle *dev, uint16_t pressure_hpa)
{
	return scd40_write_command_arg(dev, SCD40_CMD_SET_AMBIENT_PRESSURE, pressure_hpa);
}

HAL_StatusTypeDef SCD40_PersistSettings(SCD40_Handle *dev)
{
	return scd40_write_command(dev, SCD40_CMD_PERSIST_SETTINGS);
}

HAL_StatusTypeDef SCD40_GetSerialNumber(SCD40_Handle *dev, uint16_t serial[3])
{
	if (serial == NULL)
	{
		return HAL_ERROR;
	}

	return scd40_read_words(dev, SCD40_CMD_GET_SERIAL_NUMBER, serial, 3U);
}

HAL_StatusTypeDef SCD40_PerformSelfTest(SCD40_Handle *dev, uint16_t *result)
{
	uint16_t raw;
	HAL_StatusTypeDef status = scd40_read_words(dev, SCD40_CMD_PERFORM_SELF_TEST, &raw, 1U);

	if (status != HAL_OK)
	{
		return status;
	}

	if (result != NULL)
	{
		*result = raw;
	}

	return HAL_OK;
}

HAL_StatusTypeDef SCD40_PerformFactoryReset(SCD40_Handle *dev)
{
	return scd40_write_command(dev, SCD40_CMD_PERFORM_FACTORY_RESET);
}

HAL_StatusTypeDef SCD40_Reinit(SCD40_Handle *dev)
{
	return scd40_write_command(dev, SCD40_CMD_REINIT);
}

HAL_StatusTypeDef SCD40_MeasureSingleShot(SCD40_Handle *dev)
{
	return scd40_write_command(dev, SCD40_CMD_MEASURE_SINGLE_SHOT);
}

HAL_StatusTypeDef SCD40_MeasureSingleShotRhtOnly(SCD40_Handle *dev)
{
	return scd40_write_command(dev, SCD40_CMD_MEASURE_SINGLE_SHOT_RHT_ONLY);
}

HAL_StatusTypeDef SCD40_SetAutomaticSelfCalibration(SCD40_Handle *dev, bool enable)
{
	uint16_t raw = enable ? 1U : 0U;
	return scd40_write_command_arg(dev, SCD40_CMD_SET_AUTOMATIC_SELF_CALIBRATION, raw);
}

HAL_StatusTypeDef SCD40_GetAutomaticSelfCalibration(SCD40_Handle *dev, bool *enable)
{
	uint16_t raw;
	HAL_StatusTypeDef status = scd40_read_words(dev, SCD40_CMD_GET_AUTOMATIC_SELF_CALIBRATION, &raw, 1U);

	if (status != HAL_OK)
	{
		return status;
	}

	if (enable != NULL)
	{
		*enable = (raw != 0U);
	}

	return HAL_OK;
}
