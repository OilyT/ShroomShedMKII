#include "sd.h"

#include "main.h"
#include "stm32h5xx_hal.h"

#include <string.h>

#define SD_SECTOR_SIZE 512U
#define SD_MEDIA_CACHE_SIZE (8U * SD_SECTOR_SIZE)
#define SD_SPI_TIMEOUT_MS 500U
#define SD_INIT_TIMEOUT_MS 2000U

typedef enum
{
	SD_TYPE_UNKNOWN = 0,
	SD_TYPE_SDSC,
	SD_TYPE_SDHC
} sd_type_t;

static FX_MEDIA sd_media;
static UCHAR sd_media_cache[SD_MEDIA_CACHE_SIZE];
static sd_type_t sd_type = SD_TYPE_UNKNOWN;
static ULONG sd_total_sectors = 0;

extern SPI_HandleTypeDef hspi6;

static VOID sd_fx_driver(FX_MEDIA *media_ptr);

static void sd_cs_high(void)
{
	HAL_GPIO_WritePin(SD_CS_GPIO_Port, SD_CS_Pin, GPIO_PIN_SET);
}

static void sd_cs_low(void)
{
	HAL_GPIO_WritePin(SD_CS_GPIO_Port, SD_CS_Pin, GPIO_PIN_RESET);
}

static uint8_t sd_spi_xfer(uint8_t out)
{
	uint8_t in = 0xFF;
	(void)HAL_SPI_TransmitReceive(&hspi6, &out, &in, 1, SD_SPI_TIMEOUT_MS);
	return in;
}

static void sd_spi_clock_idle(UINT cycles)
{
	sd_cs_high();
	while (cycles-- > 0U)
	{
		(void)sd_spi_xfer(0xFF);
	}
}

static UINT sd_wait_ready(UINT timeout_ms)
{
	uint32_t start = HAL_GetTick();
	while ((HAL_GetTick() - start) < timeout_ms)
	{
		if (sd_spi_xfer(0xFF) == 0xFF)
		{
			return FX_SUCCESS;
		}
	}
	return FX_IO_ERROR;
}

static void sd_deselect(void)
{
	sd_cs_high();
	(void)sd_spi_xfer(0xFF);
}

static UINT sd_select(void)
{
	sd_cs_low();
	if (sd_wait_ready(SD_SPI_TIMEOUT_MS) != FX_SUCCESS)
	{
		sd_deselect();
		return FX_IO_ERROR;
	}
	return FX_SUCCESS;
}

static uint8_t sd_send_cmd(uint8_t cmd, uint32_t arg, uint8_t crc)
{
	uint8_t res;

	sd_deselect();
	if (sd_select() != FX_SUCCESS)
	{
		return 0xFF;
	}

	sd_spi_xfer(0x40U | cmd);
	sd_spi_xfer((uint8_t)(arg >> 24));
	sd_spi_xfer((uint8_t)(arg >> 16));
	sd_spi_xfer((uint8_t)(arg >> 8));
	sd_spi_xfer((uint8_t)arg);
	sd_spi_xfer(crc);

	for (UINT i = 0; i < 8U; i++)
	{
		res = sd_spi_xfer(0xFF);
		if ((res & 0x80U) == 0U)
		{
			return res;
		}
	}

	return 0xFF;
}

static uint8_t sd_send_acmd(uint8_t cmd, uint32_t arg)
{
	uint8_t res = sd_send_cmd(55, 0, 0x65);
	if (res > 1U)
	{
		return res;
	}
	return sd_send_cmd(cmd, arg, 0x77);
}

static UINT sd_read_bytes(uint8_t *buff, UINT len)
{
	while (len-- > 0U)
	{
		*buff++ = sd_spi_xfer(0xFF);
	}
	return FX_SUCCESS;
}

static UINT sd_read_csd(uint8_t csd[16])
{
	uint8_t token;

	if (sd_send_cmd(9, 0, 0xFF) != 0)
	{
		sd_deselect();
		return FX_IO_ERROR;
	}

	uint32_t start = HAL_GetTick();
	do
	{
		token = sd_spi_xfer(0xFF);
		if (token == 0xFE)
		{
			break;
		}
	} while ((HAL_GetTick() - start) < SD_SPI_TIMEOUT_MS);

	if (token != 0xFE)
	{
		sd_deselect();
		return FX_IO_ERROR;
	}

	(void)sd_read_bytes(csd, 16);
	(void)sd_spi_xfer(0xFF);
	(void)sd_spi_xfer(0xFF);
	sd_deselect();

	return FX_SUCCESS;
}

static UINT sd_update_capacity(void)
{
	uint8_t csd[16];
	if (sd_read_csd(csd) != FX_SUCCESS)
	{
		return FX_IO_ERROR;
	}

	if ((csd[0] >> 6) == 1U)
	{
		uint32_t csize = ((uint32_t)(csd[7] & 0x3FU) << 16) | ((uint32_t)csd[8] << 8) | csd[9];
		sd_total_sectors = (csize + 1U) * 1024U;
		sd_type = SD_TYPE_SDHC;
	}
	else
	{
		uint32_t csize = ((uint32_t)(csd[6] & 0x03U) << 10) | ((uint32_t)csd[7] << 2) | ((csd[8] & 0xC0U) >> 6);
		uint32_t csize_mult = ((uint32_t)(csd[9] & 0x03U) << 1) | ((csd[10] & 0x80U) >> 7);
		uint32_t block_len = 1U << (csd[5] & 0x0FU);
		uint32_t mult = 1U << (csize_mult + 2U);
		uint32_t blocknr = (csize + 1U) * mult;
		uint32_t capacity = blocknr * block_len;
		sd_total_sectors = capacity / SD_SECTOR_SIZE;
		sd_type = SD_TYPE_SDSC;
	}

	return FX_SUCCESS;
}

static UINT sd_init_card(void)
{
	uint8_t ocr[4];
	uint8_t res;

	sd_spi_clock_idle(10);

	res = sd_send_cmd(0, 0, 0x95);
	if (res != 0x01U)
	{
		sd_deselect();
		return FX_IO_ERROR;
	}

	res = sd_send_cmd(8, 0x1AA, 0x87);
	if (res == 0x01U)
	{
		(void)sd_read_bytes(ocr, 4);
		if (ocr[2] != 0x01U || ocr[3] != 0xAAU)
		{
			sd_deselect();
			return FX_IO_ERROR;
		}
	}

	uint32_t start = HAL_GetTick();
	do
	{
		res = sd_send_acmd(41, 0x40000000U);
	} while (res != 0x00U && (HAL_GetTick() - start) < SD_INIT_TIMEOUT_MS);

	if (res != 0x00U)
	{
		sd_deselect();
		return FX_IO_ERROR;
	}

	res = sd_send_cmd(58, 0, 0xFF);
	if (res != 0x00U)
	{
		sd_deselect();
		return FX_IO_ERROR;
	}

	(void)sd_read_bytes(ocr, 4);
	sd_deselect();

	if (ocr[0] & 0x40U)
	{
		sd_type = SD_TYPE_SDHC;
	}
	else
	{
		sd_type = SD_TYPE_SDSC;
		(void)sd_send_cmd(16, SD_SECTOR_SIZE, 0xFF);
		sd_deselect();
	}

	return sd_update_capacity();
}

static UINT sd_read_sectors(uint32_t sector, uint8_t *buffer, UINT count)
{
	uint32_t addr = sector;
	if (sd_type != SD_TYPE_SDHC)
	{
		addr *= SD_SECTOR_SIZE;
	}

	while (count-- > 0U)
	{
		if (sd_send_cmd(17, addr, 0xFF) != 0U)
		{
			sd_deselect();
			return FX_IO_ERROR;
		}

		uint8_t token;
		uint32_t start = HAL_GetTick();
		do
		{
			token = sd_spi_xfer(0xFF);
			if (token == 0xFEU)
			{
				break;
			}
		} while ((HAL_GetTick() - start) < SD_SPI_TIMEOUT_MS);

		if (token != 0xFEU)
		{
			sd_deselect();
			return FX_IO_ERROR;
		}

		(void)sd_read_bytes(buffer, SD_SECTOR_SIZE);
		buffer += SD_SECTOR_SIZE;
		(void)sd_spi_xfer(0xFF);
		(void)sd_spi_xfer(0xFF);
		sd_deselect();

		addr += (sd_type == SD_TYPE_SDHC) ? 1U : SD_SECTOR_SIZE;
	}

	return FX_SUCCESS;
}

static UINT sd_write_sectors(uint32_t sector, const uint8_t *buffer, UINT count)
{
	uint32_t addr = sector;
	if (sd_type != SD_TYPE_SDHC)
	{
		addr *= SD_SECTOR_SIZE;
	}

	while (count-- > 0U)
	{
		if (sd_send_cmd(24, addr, 0xFF) != 0U)
		{
			sd_deselect();
			return FX_IO_ERROR;
		}

		sd_spi_xfer(0xFE);
		for (UINT i = 0; i < SD_SECTOR_SIZE; i++)
		{
			sd_spi_xfer(buffer[i]);
		}
		buffer += SD_SECTOR_SIZE;
		sd_spi_xfer(0xFF);
		sd_spi_xfer(0xFF);

		uint8_t resp = sd_spi_xfer(0xFF) & 0x1FU;
		if (resp != 0x05U)
		{
			sd_deselect();
			return FX_IO_ERROR;
		}

		if (sd_wait_ready(SD_SPI_TIMEOUT_MS) != FX_SUCCESS)
		{
			sd_deselect();
			return FX_IO_ERROR;
		}

		sd_deselect();
		addr += (sd_type == SD_TYPE_SDHC) ? 1U : SD_SECTOR_SIZE;
	}

	return FX_SUCCESS;
}

static VOID sd_fx_driver(FX_MEDIA *media_ptr)
{
	UINT status = FX_IO_ERROR;

	switch (media_ptr->fx_media_driver_request)
	{
		case FX_DRIVER_INIT:
			status = sd_init_card();
			media_ptr->fx_media_driver_write_protect = FX_FALSE;
			break;

		case FX_DRIVER_UNINIT:
			status = FX_SUCCESS;
			break;

		case FX_DRIVER_READ:
			status = sd_read_sectors((uint32_t)media_ptr->fx_media_driver_logical_sector,
									 (uint8_t *)media_ptr->fx_media_driver_buffer,
									 (UINT)media_ptr->fx_media_driver_sectors);
			break;

		case FX_DRIVER_WRITE:
			status = sd_write_sectors((uint32_t)media_ptr->fx_media_driver_logical_sector,
									  (const uint8_t *)media_ptr->fx_media_driver_buffer,
									  (UINT)media_ptr->fx_media_driver_sectors);
			break;

		case FX_DRIVER_FLUSH:
			status = FX_SUCCESS;
			break;

		case FX_DRIVER_BOOT_READ:
			status = sd_read_sectors(0U, (uint8_t *)media_ptr->fx_media_driver_buffer, 1U);
			break;

		default:
			status = FX_IO_ERROR;
			break;
	}

	media_ptr->fx_media_driver_status = status;
}

UINT sd_init(void)
{
	return fx_media_open(&sd_media, "SD", sd_fx_driver, FX_NULL, sd_media_cache, sizeof(sd_media_cache));
}

UINT sd_deinit(void)
{
	return fx_media_close(&sd_media);
}

FX_MEDIA *sd_get_media(void)
{
	return &sd_media;
}

ULONG sd_get_total_sectors(void)
{
	return sd_total_sectors;
}

static UINT sd_file_open_append(FX_FILE *file, const CHAR *path)
{
	UINT status = fx_file_open(&sd_media, file, (CHAR *)path, FX_OPEN_FOR_WRITE);
	if (status == FX_NOT_FOUND)
	{
		status = fx_file_create(&sd_media, (CHAR *)path);
		if (status != FX_SUCCESS && status != FX_ALREADY_CREATED)
		{
			return status;
		}
		status = fx_file_open(&sd_media, file, (CHAR *)path, FX_OPEN_FOR_WRITE);
	}

	if (status != FX_SUCCESS)
	{
		return status;
	}

	return fx_file_seek(file, (ULONG)file->fx_file_current_file_size);
}

UINT sd_csv_append_line(const CHAR *path, const CHAR *line)
{
	FX_FILE file;
	UINT status = sd_file_open_append(&file, path);
	if (status != FX_SUCCESS)
	{
		return status;
	}

	ULONG len = (ULONG)strlen(line);
	status = fx_file_write(&file, (VOID *)line, len);
	if (status == FX_SUCCESS)
	{
		if (len == 0U || line[len - 1U] != '\n')
		{
			const CHAR nl = '\n';
			status = fx_file_write(&file, (VOID *)&nl, 1U);
		}
	}

	(void)fx_file_close(&file);
	(void)fx_media_flush(&sd_media);
	return status;
}

UINT sd_csv_append_row(const CHAR *path, const CHAR * const *fields, UINT field_count)
{
	FX_FILE file;
	UINT status = sd_file_open_append(&file, path);
	if (status != FX_SUCCESS)
	{
		return status;
	}

	for (UINT i = 0; i < field_count; i++)
	{
		const CHAR *field = fields[i] ? fields[i] : "";
		ULONG len = (ULONG)strlen(field);
		status = fx_file_write(&file, (VOID *)field, len);
		if (status != FX_SUCCESS)
		{
			break;
		}
		if (i + 1U < field_count)
		{
			const CHAR comma = ',';
			status = fx_file_write(&file, (VOID *)&comma, 1U);
			if (status != FX_SUCCESS)
			{
				break;
			}
		}
	}

	if (status == FX_SUCCESS)
	{
		const CHAR nl = '\n';
		status = fx_file_write(&file, (VOID *)&nl, 1U);
	}

	(void)fx_file_close(&file);
	(void)fx_media_flush(&sd_media);
	return status;
}

UINT sd_csv_read_line(const CHAR *path, ULONG *offset, CHAR *buffer, UINT buffer_len, UINT *out_len)
{
	if (buffer_len < 2U)
	{
		return FX_BUFFER_ERROR;
	}

	FX_FILE file;
	UINT status = fx_file_open(&sd_media, &file, (CHAR *)path, FX_OPEN_FOR_READ);
	if (status != FX_SUCCESS)
	{
		return status;
	}

	status = fx_file_seek(&file, *offset);
	if (status != FX_SUCCESS)
	{
		(void)fx_file_close(&file);
		return status;
	}

	UINT total = 0U;
	ULONG actual = 0U;
	while (total < (buffer_len - 1U))
	{
		CHAR ch;
		status = fx_file_read(&file, &ch, 1U, &actual);
		if (status != FX_SUCCESS || actual == 0U)
		{
			break;
		}

		buffer[total++] = ch;
		if (ch == '\n')
		{
			break;
		}
	}

	buffer[total] = '\0';
	*offset += total;
	if (out_len)
	{
		*out_len = total;
	}

	(void)fx_file_close(&file);

	if (total == 0U && actual == 0U)
	{
		return FX_END_OF_FILE;
	}

	return status;
}
