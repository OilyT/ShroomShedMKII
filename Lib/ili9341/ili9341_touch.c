/* vim: set ai et ts=4 sw=4: */

#include "stm32h5xx_hal.h"
#include "ili9341_touch.h"
#include "ili9341.h"
#include "stm32h5xx_hal_spi.h"
#include <stdint.h>

#define READ_Y 0xD0
#define READ_X 0x90

#define MIN_SAMPLES 16
#define MAX_SAMPLES 64
#define CALIBRATION_SAMPLES 128
#define CALIBRATION_ITERATIONS 4

#define Z_THRESHOLD 200 


static uint16_t besttwoavg(uint16_t x , uint16_t y , uint16_t z );
static void read_xy_cycle(uint16_t* x , uint16_t* y);
static inline uint16_t xpt2046_unpack_sample(const uint8_t *rx);


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


bool get_touch_coordinates(uint16_t* x, uint16_t* y) {

    if (!ILI9341_TouchPressed()) return false;

    const uint8_t repeats = 4;

    uint16_t x_data[repeats];
    uint16_t y_data[repeats];

    uint8_t cmd_buff[3] = {0};
    uint8_t *p_cmd_buff = &cmd_buff[0];
    uint8_t rx_buff[3] = {0};
    uint8_t *p_rx_buff = &rx_buff[0];

    uint8_t samples_taken = 0;
    
    ILI9341_TouchSelect();


    // read touch pressure
    uint16_t z;

    p_cmd_buff[0] = 0xB1;
    HAL_SPI_Transmit(&ILI9341_TOUCH_SPI_PORT, p_cmd_buff, 3, HAL_MAX_DELAY); // 24 clocks so that conversions is complete
    p_cmd_buff[0] = 0xC1;
    HAL_SPI_TransmitReceive(&ILI9341_TOUCH_SPI_PORT, p_cmd_buff, p_rx_buff, 3, HAL_MAX_DELAY); // 24 clock cycle
    uint16_t z1 = xpt2046_unpack_sample(rx_buff);
    z = z1 + 4095;
    p_cmd_buff[0] = 0x91;
    HAL_SPI_TransmitReceive(&ILI9341_TOUCH_SPI_PORT, p_cmd_buff, p_rx_buff, 3, HAL_MAX_DELAY);
    uint16_t z2 = xpt2046_unpack_sample(rx_buff);
    z -= z2;
    
    // take dummy measure of each since they are always noisy
    p_cmd_buff[0] = 0x91;
    HAL_SPI_TransmitReceive(&ILI9341_TOUCH_SPI_PORT, p_cmd_buff, p_rx_buff, 2, HAL_MAX_DELAY);
    cmd_buff[0] = 0xD1;
    HAL_SPI_TransmitReceive(&ILI9341_TOUCH_SPI_PORT, p_cmd_buff, p_rx_buff, 2, HAL_MAX_DELAY);

    for (uint8_t i = 0; i < repeats; i++) {
        //if (!ILI9341_TouchPressed()) break;
        read_xy_cycle(&x_data[i], &y_data[i]);   
        samples_taken ++;
    }

    // power down at end of conversion
    cmd_buff[0] = 0xD0;
    HAL_SPI_TransmitReceive(&ILI9341_TOUCH_SPI_PORT, p_cmd_buff, p_rx_buff, 2, HAL_MAX_DELAY);
    ILI9341_TouchUnselect();

    int32_t temp_x = 0;
    int32_t temp_y = 0;
    for (uint8_t i = 0; i < samples_taken; i++) {
        temp_x += x_data[i];
        temp_y += y_data[i];
    }

    if (samples_taken == 0) return false;

    temp_x /= samples_taken;
    temp_y /= samples_taken;

    *x = (uint16_t)temp_x;
    *y = (uint16_t)temp_y;
    return true;

}

static void read_xy_cycle(uint16_t* x, uint16_t* y) {
    uint8_t cmd_buff[2] = {0};
    uint8_t rx_buff[2] = {0};
    uint8_t *p_cmd_buff = &cmd_buff[0];
    uint8_t *p_rx_buff = &rx_buff[0];

    uint16_t data[6] = {0};

    // take 3 readings each of x and y

    cmd_buff[0] = 0x91;
    HAL_SPI_TransmitReceive(&ILI9341_TOUCH_SPI_PORT, p_cmd_buff, p_rx_buff, 2, HAL_MAX_DELAY);
    data[0] = xpt2046_unpack_sample(rx_buff);
    cmd_buff[0] = 0xD1;
    HAL_SPI_TransmitReceive(&ILI9341_TOUCH_SPI_PORT, p_cmd_buff, p_rx_buff, 2, HAL_MAX_DELAY); 
    data[1] = xpt2046_unpack_sample(rx_buff);
    cmd_buff[0] = 0x91;
    HAL_SPI_TransmitReceive(&ILI9341_TOUCH_SPI_PORT, p_cmd_buff, p_rx_buff, 2, HAL_MAX_DELAY); 
    data[2] = xpt2046_unpack_sample(rx_buff);
    cmd_buff[0] = 0xD1;
    HAL_SPI_TransmitReceive(&ILI9341_TOUCH_SPI_PORT, p_cmd_buff, p_rx_buff, 2, HAL_MAX_DELAY); 
    data[3] = xpt2046_unpack_sample(rx_buff);
    cmd_buff[0] = 0x91;
    HAL_SPI_TransmitReceive(&ILI9341_TOUCH_SPI_PORT, p_cmd_buff, p_rx_buff, 2, HAL_MAX_DELAY); 
    data[4] = xpt2046_unpack_sample(rx_buff);
    cmd_buff[0] = 0xD1;
    HAL_SPI_TransmitReceive(&ILI9341_TOUCH_SPI_PORT, p_cmd_buff, p_rx_buff, 2, HAL_MAX_DELAY);
    data[5] = xpt2046_unpack_sample(rx_buff);

    // return the best two average of the 3 readings for x and y
    *x = besttwoavg(data[0], data[2], data[4]);
    *y = besttwoavg(data[1], data[3], data[5]);

}

static inline uint16_t xpt2046_unpack_sample(const uint8_t *rx) {
    return (((((uint16_t)rx[0]) << 8) | rx[1]) & 0x7FFFU) >> 3;
}

static uint16_t besttwoavg( uint16_t x , uint16_t y , uint16_t z ) {
    uint16_t da, db, dc;
    uint16_t reta = 0;
    if ( x > y ) da = x - y; else da = y - x;
    if ( x > z ) db = x - z; else db = z - x;
    if ( z > y ) dc = z - y; else dc = y - z;

    if ( da <= db && da <= dc ) reta = (x + y) >> 1;
    else if ( db <= da && db <= dc ) reta = (x + z) >> 1;
    else reta = (y + z) >> 1;
    return (reta);
}


