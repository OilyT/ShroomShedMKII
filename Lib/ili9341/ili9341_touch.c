/* vim: set ai et ts=4 sw=4: */

#include "stm32h5xx_hal.h"
#include "ili9341_touch.h"
#include "ili9341.h"
#include <stdint.h>

#define READ_Y 0xD0
#define READ_X 0x90

#define MIN_SAMPLES 32
#define MAX_SAMPLES 64
#define CALIBRATION_SAMPLES 128
#define CALIBRATION_ITERATIONS 4

static void ILI9341_TouchSelect() {
    HAL_GPIO_WritePin(ILI9341_TOUCH_CS_GPIO_Port, ILI9341_TOUCH_CS_Pin, GPIO_PIN_RESET);
}

void ILI9341_TouchUnselect() {
    HAL_GPIO_WritePin(ILI9341_TOUCH_CS_GPIO_Port, ILI9341_TOUCH_CS_Pin, GPIO_PIN_SET);
}

bool ILI9341_TouchPressed() {
    return HAL_GPIO_ReadPin(ILI9341_TOUCH_IRQ_GPIO_Port, ILI9341_TOUCH_IRQ_Pin) == GPIO_PIN_RESET;
}

bool ILI9341_TouchGetCoordinates(uint16_t* x, uint16_t* y) {

    static const uint8_t cmd_read_x[] = { READ_X };
    static const uint8_t cmd_read_y[] = { READ_Y };
    static const uint8_t zeroes_tx[] = { 0x00, 0x00 };

    ILI9341_TouchSelect();

    uint32_t avg_x = 0;
    uint32_t avg_y = 0;
    uint8_t nsamples = 0;
    for(uint8_t i = 0; i < MAX_SAMPLES; i++) {
        if(!ILI9341_TouchPressed())
            break;
        
        nsamples++;

        HAL_SPI_Transmit(&ILI9341_TOUCH_SPI_PORT, (uint8_t*)cmd_read_y, sizeof(cmd_read_y), HAL_MAX_DELAY);
        uint8_t y_raw[2];
        HAL_SPI_TransmitReceive(&ILI9341_TOUCH_SPI_PORT, (uint8_t*)zeroes_tx, y_raw, sizeof(y_raw), HAL_MAX_DELAY);

        HAL_SPI_Transmit(&ILI9341_TOUCH_SPI_PORT, (uint8_t*)cmd_read_x, sizeof(cmd_read_x), HAL_MAX_DELAY);
        uint8_t x_raw[2];
        HAL_SPI_TransmitReceive(&ILI9341_TOUCH_SPI_PORT, (uint8_t*)zeroes_tx, x_raw, sizeof(x_raw), HAL_MAX_DELAY);

        avg_x += (((uint16_t)x_raw[0]) << 8) | ((uint16_t)x_raw[1]);
        avg_y += (((uint16_t)y_raw[0]) << 8) | ((uint16_t)y_raw[1]);
    }

    ILI9341_TouchUnselect();

    if(nsamples < MIN_SAMPLES)
        return false;

    uint32_t raw_x = (avg_x / nsamples);
    if(raw_x < ILI9341_TOUCH_MIN_RAW_X) raw_x = ILI9341_TOUCH_MIN_RAW_X;
    if(raw_x > ILI9341_TOUCH_MAX_RAW_X) raw_x = ILI9341_TOUCH_MAX_RAW_X;

    uint32_t raw_y = (avg_y / nsamples);
    if(raw_y < ILI9341_TOUCH_MIN_RAW_Y) raw_y = ILI9341_TOUCH_MIN_RAW_Y;
    if(raw_y > ILI9341_TOUCH_MAX_RAW_Y) raw_y = ILI9341_TOUCH_MAX_RAW_Y;


    *x = (raw_x - ILI9341_TOUCH_MIN_RAW_X) * ILI9341_TOUCH_SCALE_X / (ILI9341_TOUCH_MAX_RAW_X - ILI9341_TOUCH_MIN_RAW_X);
    *y = (raw_y - ILI9341_TOUCH_MIN_RAW_Y) * ILI9341_TOUCH_SCALE_Y / (ILI9341_TOUCH_MAX_RAW_Y - ILI9341_TOUCH_MIN_RAW_Y);

    return true;
}

bool touch_get_avg_x_y(uint16_t *x, uint16_t *y, uint8_t samples) {
    static const uint8_t cmd_read_x[] = { READ_X };
    static const uint8_t cmd_read_y[] = { READ_Y };
    static const uint8_t zeroes_tx[] = { 0x00, 0x00 };

    uint32_t avg_x = 0;
    uint32_t avg_y = 0;

    ILI9341_TouchSelect();

    for(uint8_t i = 0; i < samples; i++) {
        if(!ILI9341_TouchPressed()) return false;

        HAL_SPI_Transmit(&ILI9341_TOUCH_SPI_PORT, (uint8_t*)cmd_read_y, sizeof(cmd_read_y), HAL_MAX_DELAY);
        uint8_t y_raw[2];
        HAL_SPI_TransmitReceive(&ILI9341_TOUCH_SPI_PORT, (uint8_t*)zeroes_tx, y_raw, sizeof(y_raw), HAL_MAX_DELAY);

        HAL_SPI_Transmit(&ILI9341_TOUCH_SPI_PORT, (uint8_t*)cmd_read_x, sizeof(cmd_read_x), HAL_MAX_DELAY);
        uint8_t x_raw[2];
        HAL_SPI_TransmitReceive(&ILI9341_TOUCH_SPI_PORT, (uint8_t*)zeroes_tx, x_raw, sizeof(x_raw), HAL_MAX_DELAY);

        avg_x += (((uint16_t)x_raw[0]) << 8) | ((uint16_t)x_raw[1]);
        avg_y += (((uint16_t)y_raw[0]) << 8) | ((uint16_t)y_raw[1]);
    }
    ILI9341_TouchUnselect();
    *x = avg_x / samples;
    *y = avg_y / samples;
    return true;
}


 void calibrate_touch(uint32_t *min_x, uint32_t *min_y, uint32_t *max_x, uint32_t *max_y) {
    uint16_t x, y;
    uint8_t iterations = 0;
    *min_x = 0xFFFFFFFF;
    *min_y = 0xFFFFFFFF;
    *max_x = 0;
    *max_y = 0;

    // top left
    ILI9341_FillRectangle(0, 0, 5, 5, ILI9341_RED);
    while (iterations < CALIBRATION_ITERATIONS) {
        if (touch_get_avg_x_y(&x, &y, CALIBRATION_SAMPLES)) {
            if (x < *min_x) *min_x = x;
            if (y < *min_y) *min_y = y;
            iterations++;
        }
    }
    iterations = 0;
    ILI9341_FillRectangle(145, 105, 30, 30, ILI9341_RED);
    HAL_Delay(500);
    ILI9341_FillRectangle(145, 105, 30, 30, ILI9341_WHITE);

    // top right
    ILI9341_FillRectangle(315, 0, 5, 5, ILI9341_RED);
    while (iterations < CALIBRATION_ITERATIONS) {
        if (touch_get_avg_x_y(&x, &y, CALIBRATION_SAMPLES)) {
            if (x > *max_x) *max_x = x;
            if (y < *min_y) *min_y = y;
            iterations++;
        }
    }
    iterations = 0;
    ILI9341_FillRectangle(145, 105, 30, 30, ILI9341_RED);
    HAL_Delay(500);
    ILI9341_FillRectangle(145, 105, 30, 30, ILI9341_WHITE);

    // bottom left
    ILI9341_FillRectangle(0, 235, 5, 5, ILI9341_RED);
    while (iterations < CALIBRATION_ITERATIONS) {
        if (touch_get_avg_x_y(&x, &y, CALIBRATION_SAMPLES)) {
            if (x < *min_x) *min_x = x;
            if (y > *max_y) *max_y = y;
            iterations++;
        }
    }
    iterations = 0;
    ILI9341_FillRectangle(145, 105, 30, 30, ILI9341_RED);
    HAL_Delay(500);
    ILI9341_FillRectangle(145, 105, 30, 30, ILI9341_WHITE);

    // bottom right
    ILI9341_FillRectangle(315, 235, 5, 5, ILI9341_RED);
    while(iterations < CALIBRATION_ITERATIONS) {
        if (touch_get_avg_x_y(&x, &y, CALIBRATION_SAMPLES)) {
            if (x > *max_x) *max_x = x;
            if (y > *max_y) *max_y = y;
            iterations++;
        }
    }
}