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
    bool on;
    uint8_t discoPower;
    uint8_t discoSpeed;
    uint8_t discoOffset;
} RGB_disco_settings_t;


#define RGB_SPI_PORT hspi2
extern SPI_HandleTypeDef RGB_SPI_PORT;


#define LOGIC_0 0xC0
#define LOGIC_1 0xF0


void RGB_Init(void);
void RGB_Process(void);


#endif /* RGB_H */

