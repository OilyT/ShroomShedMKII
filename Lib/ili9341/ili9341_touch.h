/* vim: set ai et ts=4 sw=4: */
#ifndef __ILI9341_TOUCH_H__
#define __ILI9341_TOUCH_H__

#include <stdbool.h>
#include <stdint.h>
#include "main.h"
#include "stm32h5xx_hal_spi.h"

/*** Redefine if necessary ***/

// Warning! Use SPI bus with < 1.3 Mbit speed, better ~650 Kbit to be save.
#define ILI9341_TOUCH_SPI_PORT hspi1
extern SPI_HandleTypeDef ILI9341_TOUCH_SPI_PORT;

#define ILI9341_TOUCH_IRQ_Pin       TOUCH_IRQ_Pin
#define ILI9341_TOUCH_IRQ_GPIO_Port TOUCH_IRQ_GPIO_Port
#define ILI9341_TOUCH_CS_Pin        TOUCH_CS_Pin
#define ILI9341_TOUCH_CS_GPIO_Port  TOUCH_CS_GPIO_Port

// change depending on screen orientation
#define ILI9341_TOUCH_SCALE_X 320
#define ILI9341_TOUCH_SCALE_Y 240

// default calibration values
#define ILI9341_TOUCH_MIN_RAW_X 1760
#define ILI9341_TOUCH_MAX_RAW_X 30901
#define ILI9341_TOUCH_MIN_RAW_Y 2143
#define ILI9341_TOUCH_MAX_RAW_Y 31068

// uint32_t TOUCH_MIN_X;
// uint32_t TOUCH_MAX_X;
// uint32_t TOUCH_MIN_Y;
// uint32_t TOUCH_MAX_Y;

// call before initializing any SPI devices
void ILI9341_TouchUnselect();

bool ILI9341_TouchPressed();
bool ILI9341_TouchGetCoordinates(uint16_t* x, uint16_t* y);
void calibrate_touch(uint32_t *min_x, uint32_t *min_y, uint32_t *max_x, uint32_t *max_y );
bool get_touch_coordinates(uint16_t* x, uint16_t* y);

#endif // __ILI9341_TOUCH_H__
