#include "rgb.h"
#include <stdint.h>
#include <string.h>
#include "main.h"
#include "stdbool.h"
#include "stm32h5xx_hal.h"

/* RGB LED structs */
RGB_Colour zone_colour[4];
uint8_t rgb_buffer[96];



/* Function prototypes */
static void RGB_flush_buffer(void);
static uint8_t* rgb_colour_to_buffer(RGB_Colour color);
static uint8_t RGB_bit_to_byte(uint8_t byte, uint8_t bit_position);
void disco_mode(RGB_Colour *colour, uint8_t step, uint16_t offset);
void set_all_zones(RGB_Colour colour);
void RGB_flush_buffer(void);


void RGB_Init(void) {


    set_all_zones((RGB_Colour){.red = 1, .green = 0, .blue = 0});
    RGB_flush_buffer();
    HAL_Delay(100);
    set_all_zones((RGB_Colour){.red = 64, .green = 0, .blue = 0});
    RGB_flush_buffer();
    HAL_Delay(100);
    set_all_zones((RGB_Colour){.red = 128, .green = 0, .blue = 0});
    RGB_flush_buffer();
    HAL_Delay(100);
    set_all_zones((RGB_Colour){.red = 255, .green = 0, .blue = 0});
    RGB_flush_buffer();
    HAL_Delay(100);
    set_all_zones((RGB_Colour){.red = 0, .green = 1, .blue = 0});
    RGB_flush_buffer();
    HAL_Delay(100);
    set_all_zones((RGB_Colour){.red = 0, .green = 64, .blue = 0});
    RGB_flush_buffer();
    HAL_Delay(100);
    set_all_zones((RGB_Colour){.red = 0, .green = 128, .blue = 0});
    RGB_flush_buffer();
    HAL_Delay(100);
    set_all_zones((RGB_Colour){.red = 0, .green = 255, .blue = 0});
    RGB_flush_buffer();
    HAL_Delay(100);
    set_all_zones((RGB_Colour){.red = 0, .green = 0, .blue = 1});
    RGB_flush_buffer();
    HAL_Delay(100);
    set_all_zones((RGB_Colour){.red = 0, .green = 0, .blue = 64});
    RGB_flush_buffer();
    HAL_Delay(100);
    set_all_zones((RGB_Colour){.red = 0, .green = 0, .blue = 128});
    RGB_flush_buffer();
    HAL_Delay(100);
    set_all_zones((RGB_Colour){.red = 0, .green = 0, .blue = 255});
    RGB_flush_buffer();
    HAL_Delay(100);
    
}

void RGB_Process(void) {
    for (uint8_t i = 0; i < 4; i++) {
        disco_mode(&zone_colour[i], 5, i*64);
    }
    RGB_flush_buffer();
}

void set_all_zones(RGB_Colour colour) {
    for (uint8_t i = 0; i < 4; i++) {
        zone_colour[i] = colour;
    }
}

void RGB_flush_buffer(void) {
    // load all data into buffer
    uint8_t *zone_buffer;
    uint8_t byte;

    for (uint8_t i = 0; i < 4; i++) {
        zone_buffer = rgb_colour_to_buffer(zone_colour[i]);
        for (uint8_t j = 0; j < 24; j++) {
            byte = *(zone_buffer+j);
            rgb_buffer[i*24 + j] = byte;
        }
    }

    // transmit entire buffer
    HAL_SPI_Transmit(&RGB_SPI_PORT, rgb_buffer, 96, HAL_MAX_DELAY);
}

void disco_mode(RGB_Colour *colour, uint8_t step, uint16_t offset) {
    
    static uint16_t pos = 0;

    pos = pos + step;
    if (pos >= 767) {
        pos = pos % 767;
    }

    uint16_t zone_pos = pos + offset;
    if (zone_pos >= 767) {
        zone_pos = zone_pos % 767;
    }


    uint8_t phase = zone_pos / 255;

    switch (phase) {
        case 0:
            colour->red = zone_pos;
            colour->green = 0;
            colour->blue = 255 - zone_pos;
            break;
        case 1:
            colour->red = 510 - zone_pos;
            colour->green = zone_pos - 255;
            colour->blue = 0;
            break;
        case 2:
            colour->red = 0;
            colour->green = 765 - zone_pos;
            colour->blue = zone_pos - 510;
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

