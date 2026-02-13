/**
******************************************************************************
* @file           : display_manager.c
* @brief          : Display manager implementation
******************************************************************************
*/

#include "display_manager.h"
#include "main.h"  
#include "screens.h"
#include "ili9341.h"
#include "lvgl.h"
#include "stm32h5xx_hal.h"
#include "ui.h"
#include "vars.h"
#include "shroomshed.h"


/* Declare buffer for 1/10 screen size; BYTES_PER_PIXEL will be 2 for RGB565. */
#define BYTES_PER_PIXEL (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_RGB565))
static uint8_t buf1[ILI9341_WIDTH * ILI9341_HEIGHT / 10 * BYTES_PER_PIXEL];

lv_display_t * display;


void my_flush_cb(lv_display_t * display, const lv_area_t * area, uint8_t * px_map);
void update_display_vars(void);



void initDisplay(void) {
    // Initialize the display hardware
    ILI9341_Init();
    // turn on backlight
    HAL_GPIO_WritePin(DISPLAY_LED_GPIO_Port, DISPLAY_LED_Pin, GPIO_PIN_SET);

    // initialize LVGL
    lv_init();
    lv_tick_set_cb(HAL_GetTick);

    // Create the display
    display = lv_display_create(ILI9341_WIDTH, ILI9341_HEIGHT);

    /* Set display buffer for display `display1`. */
    lv_display_set_buffers(display, buf1, NULL, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);

    lv_display_set_flush_cb(display, my_flush_cb);

    // Initialize EEZ Studio generated UI
    ui_init();
    loadScreen(SCREEN_ID_SPLASH_SCREEN); 
 }


void my_flush_cb(lv_display_t * display, const lv_area_t * area, uint8_t * px_map)
{
    uint16_t * buf16 = (uint16_t *)px_map; /* RGB565 display buffer */
    
    /* Calculate area dimensions */
    int32_t width = area->x2 - area->x1 + 1;
    int32_t height = area->y2 - area->y1 + 1;
    int32_t total_pixels = width * height;
    
    /* Swap bytes for each pixel (LVGL little-endian to ILI9341 big-endian) */
    for(int32_t i = 0; i < total_pixels; i++) {
        uint16_t pixel = buf16[i];
        buf16[i] = (pixel >> 8) | (pixel << 8);  // Swap MSB and LSB
    }

    /* Send the entire buffer as one rectangular region */
    ILI9341_DrawImage(area->x1, area->y1, width, height, buf16);
    lv_display_flush_ready(display);
}


void updateDisplay(void) {
    update_display_vars();

    // Call LVGL timer handler
    lv_timer_handler();
    
    // Call EEZ UI tick (handles screen updates)
    ui_tick();
}

void displayProcess(void) {
    // Placeholder for display processing code
    if (HAL_GetTick() > 5000) {
        loadScreen(SCREEN_ID_MAIN);
    }

    updateDisplay();
}

void update_display_vars(void) {
    set_var_display_humidity(shroomShed.humidityCurrent);
    set_var_display_temperature(shroomShed.temperatureCurrent);
}


