#ifndef RGB_H
#define RGB_H

#include <stdint.h>
#include "main.h"
#include "stdbool.h"
 

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} RGB_Colour;

typedef struct {

} RGB_disco_settings_t;

typedef enum uint8_t {
    RGB_mode_static_colour = 0,
    RGB_mode_disco = 1,
} RGB_Mode;

typedef struct {
    bool enabled;
    RGB_Mode currentMode;
    uint8_t discoPower;
    uint8_t discoSpeed;
    uint8_t discoOffset;
    uint8_t staticRed; // 0 - 10 intensity value
    uint8_t staticGreen;
    uint8_t staticBlue;
} RGB_settings_t;


#define RGB_SPI_PORT hspi2
extern SPI_HandleTypeDef RGB_SPI_PORT;

extern RGB_settings_t rgbSettings;


#define LOGIC_0 0xC0
#define LOGIC_1 0xF0


void RGB_Init(void);
void RGB_Process(void);


#endif /* RGB_H */
