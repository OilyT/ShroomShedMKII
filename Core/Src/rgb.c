#include "rgb.h"
#include <stdint.h>
#include "main.h"
#include "stdbool.h"
#include "shroomshed.h"


#define RGB_BUFFER_SIZE 96
#define DISCO_POWER 10
#define DISCO_SPEED 10
#define DISCO_OFFSET 10
#define DISCO_STEP_DIVISOR (RGB_PROCESS_HZ * 50)
#define REDSHIFT 50


RGB_Colour zone_colour[4];
uint8_t rgb_buffer[RGB_BUFFER_SIZE];


static void RGB_flush_buffer(void);
static uint8_t* rgb_colour_to_buffer(RGB_Colour color);
static uint8_t RGB_bit_to_byte(uint8_t byte, uint8_t bit_position);
static void disco_mode(RGB_Colour *colour, uint16_t offset);
static void set_all_zones(RGB_Colour colour);
static void RGB_flush_buffer(void);



void RGB_Init(void) {

}

void RGB_Process(void) {
    for (uint8_t i = 0; i < 4; i++) {
        disco_mode(&zone_colour[i], DISCO_OFFSET*i);
    }
    RGB_flush_buffer();
}

void set_all_zones(RGB_Colour colour) {
    for (uint8_t i = 0; i < 4; i++) {
        zone_colour[i] = colour;
    }
}

void RGB_flush_buffer(void) {
    uint8_t *zone_buffer;
    uint8_t byte;

    for (uint8_t i = 0; i < 4; i++) {
        zone_buffer = rgb_colour_to_buffer(zone_colour[i]);
        for (uint8_t j = 0; j < 24; j++) {
            byte = *(zone_buffer+j);
            rgb_buffer[i*24 + j] = byte;
        }
    }
    HAL_SPI_Transmit(&RGB_SPI_PORT, rgb_buffer, RGB_BUFFER_SIZE, HAL_MAX_DELAY);
}

void disco_mode(RGB_Colour *colour, uint16_t offset) {

    static uint16_t pos = 0;
    static uint16_t step_remainder = 0;

    uint16_t range = (DISCO_POWER * 255) / 100;
    offset = (offset * range) / 100;
    uint16_t step = (range * DISCO_SPEED);
    step = step + step_remainder;
    step_remainder = step % DISCO_STEP_DIVISOR;
    step = step / DISCO_STEP_DIVISOR;

    uint32_t redshift = (REDSHIFT * range * DISCO_POWER) / 10000;
  

    pos = pos + step;
    if (pos >= range * 3) {
        pos = pos % (range * 3);
    }

    uint16_t zone_pos = pos + offset;
    if (zone_pos >= range * 3) {
        zone_pos = zone_pos % (range * 3);
    }

    uint8_t phase = zone_pos / range;

    int16_t temp_red, temp_green, temp_blue;
    switch (phase) {
        case 0:
            temp_red = zone_pos + redshift;
            if (temp_red > range) {
                temp_red = range;
            }
            colour->red = temp_red;
            colour->green = 0;
            temp_blue = (range) - zone_pos - redshift;
            if (temp_blue < 0) {
                temp_blue = 0;
            }
            colour->blue = temp_blue;
            break;
        case 1:
            temp_red = (range * 2) - zone_pos + redshift;
            if (temp_red > range) {
                temp_red = range;
            }   
            colour->red = temp_red;
            temp_green = zone_pos - range - redshift;
            if (temp_green < 0) {
                temp_green = 0;
            }
            colour->green = temp_green;
            colour->blue = 0;
            break;
        case 2:
            colour->red = 0;
            colour->green = (range * 3) - zone_pos;
            colour->blue = zone_pos - (range * 2);
            break;
    }
}

static uint8_t* rgb_colour_to_buffer(RGB_Colour color) {
    uint8_t buffer[24] = {0};
    for (uint8_t i = 0; i < 8; i++) {
        buffer[7-i] = RGB_bit_to_byte(color.red, i);
        buffer[15-i] = RGB_bit_to_byte(color.green, i);
        buffer[23-i] = RGB_bit_to_byte(color.blue, i);
    }
    uint8_t *pBuffer = &buffer[0];
    return pBuffer;
}

static uint8_t RGB_bit_to_byte(uint8_t byte, uint8_t bit_position) {
    uint8_t return_byte = (byte & (1 << bit_position)) ? LOGIC_1 : LOGIC_0;
    return return_byte;
}

