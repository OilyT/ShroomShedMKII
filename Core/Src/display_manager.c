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
#include "ili9341_touch.h"
#include "lvgl.h"
#include "stm32h5xx_hal_exti.h"
#include "stm32h5xx_hal_gpio.h"
#include "stm32h5xx_hal_tim.h"
#include "ui.h"
#include "vars.h"
#include "shroomshed.h"
#include <stdint.h>
#include "rgb.h"
#include "screens.h"
#include "stdbool.h"


#define TOUCH_BUFFER_SIZE 8


/* Declare buffer for 1/10 screen size; BYTES_PER_PIXEL will be 2 for RGB565. */
#define BYTES_PER_PIXEL (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_RGB565))
static uint8_t buf1[ILI9341_WIDTH * ILI9341_HEIGHT / 10 * BYTES_PER_PIXEL];


lv_display_t * display;
lv_indev_t * indev_touchpad;

static int16_t current_screen = 2;
static int16_t previous_screen = 2;
extern RGB_disco_settings_t discoSettings;

uint8_t display_brightness = 100;

EXTI_HandleTypeDef htouch_exti;


// local function prototypes
void my_flush_cb(lv_display_t * display, const lv_area_t * area, uint8_t * px_map);
static void update_display_vars(void);
static void touchpad_read(lv_indev_t * indev_drv, lv_indev_data_t * data);
static void touchpad_init(void);
uint32_t flush_touch_buffer(uint16_t *buffer, bool avg);



//INIT DISPLAY HARDWARE AND LVGL

void initDisplay(void) {
    ILI9341_Init();

    // turn on backlight with PWM
    HAL_TIM_PWM_Start(&DISPLAY_LED_TIMER, TIM_CHANNEL_3);
    //HAL_GPIO_WritePin(DISPLAY_LED_GPIO_Port, DISPLAY_LED_Pin, GPIO_PIN_SET);
    

    // initialize LVGL
    lv_init();
    lv_tick_set_cb(HAL_GetTick);

    display = lv_display_create(ILI9341_WIDTH, ILI9341_HEIGHT);

    /* Set display buffer for display `display1`. */
    lv_display_set_buffers(display, buf1, NULL, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_display_set_flush_cb(display, my_flush_cb);

    touchpad_init();

    ui_init();
    ui_tick();
    lv_timer_handler();
    ui_tick();
    lv_timer_handler();
    ui_tick();
    lv_timer_handler();
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


// DISPLAY PROCESSING

void displayProcess(void) {
    update_display_vars();
    // Call EEZ UI tick (handles screen updates)
    ui_tick();
    // Call LVGL timer handler
    lv_timer_handler();

}

void switch_screen(enum ScreensEnum screen) {
    previous_screen = current_screen;
    current_screen = screen;
    switch (screen) {
        case SCREEN_ID_SPLASH_SCREEN:
            loadScreen(SCREEN_ID_SPLASH_SCREEN);
            break;
        case SCREEN_ID_MAIN:
            loadScreen(SCREEN_ID_MAIN );
            break;
        case SCREEN_ID_MENU_MAIN:
            loadScreen(SCREEN_ID_MENU_MAIN);
            break;
        case SCREEN_ID_MENU_GENERAL:
            loadScreen(SCREEN_ID_MENU_GENERAL);
            break;
        case SCREEN_ID_DISCO_MODE:
            loadScreen(SCREEN_ID_DISCO_MODE);
            break;
        case SCREEN_ID_MANUAL_CONTROL:
            loadScreen(SCREEN_ID_MANUAL_CONTROL);
            break;
    }
}


static void update_display_vars(void) {

    switch (current_screen) {
        case SCREEN_ID_MAIN:
            set_var_humidity_fp(shroomShed.humidityCurrent);
            set_var_temperature_fp(shroomShed.temperatureCurrent);
            set_var_airflow_int(shroomShed.fanSpeed);
            break;
        case SCREEN_ID_DISCO_MODE:
            set_var_disco_power_int(discoSettings.discoPower);
            set_var_disco_speed_int(discoSettings.discoSpeed);
            set_var_disco_phase_int(discoSettings.discoOffset);
            break;
        case SCREEN_ID_MENU_GENERAL:
            set_var_display_brightness(get_var_display_brightness());
            break;
        case SCREEN_ID_MANUAL_CONTROL:
            set_var_humidity_fp(shroomShed.humidityCurrent);
            set_var_airflow_int(shroomShed.fanSpeed);
            break;
    }
}


// INTERFACE FUNCTIONS

inline void load_previous_screen(void) {
    switch_screen(previous_screen);
}


inline void set_display_brightness(uint8_t brightness) {
    display_brightness = brightness;
    DISPLAY_LED_TIMER.Instance->CCR3 = (brightness * DISPLAY_LED_TIMER.Init.Period) / 100;
}

/*------------------
 * Touchpad
 * -----------------*/

bool currentlyTouched = false;
bool touchSinceLastRead = false;
static uint16_t xbuffer[TOUCH_BUFFER_SIZE];
static uint16_t ybuffer[TOUCH_BUFFER_SIZE];
static uint8_t bufferIndex = 0;

uint16_t last_touch_x = 0;
uint16_t last_touch_y = 0;


static void touchpad_init(void)
{
    indev_touchpad = lv_indev_create();        /* Create input device */
    lv_indev_set_type(indev_touchpad, LV_INDEV_TYPE_POINTER);   /* Set the device type */
    lv_indev_set_read_cb(indev_touchpad, touchpad_read);    /* Set the read callback */
}


/*Called by LVGL to read the touchpad*/
static void touchpad_read(lv_indev_t * indev_drv, lv_indev_data_t * data)
{
    static int32_t last_x = 0;
    static int32_t last_y = 0;

    if(touchSinceLastRead) {
        last_x = flush_touch_buffer(xbuffer, true);
        last_y = flush_touch_buffer(ybuffer, true);
        if (last_x != 0 && last_y != 0) {
            data->state = LV_INDEV_STATE_PRESSED;
        } else {
            data->state = LV_INDEV_STATE_RELEASED;
        }
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
    touchSinceLastRead = false;

    data->point.x = last_x;
    data->point.y = last_y;
}


void poll_touchpad(void) {

    if (ILI9341_TouchPressed()) {
        currentlyTouched = true;
    } else {
        currentlyTouched = false;
    }

    if (currentlyTouched) {
        //HAL_GPIO_WritePin(WATER_LED_GPIO_Port, WATER_LED_Pin, GPIO_PIN_SET);
        if (!(ILI9341_TouchGetCoordinates(&last_touch_x, &last_touch_y))) {
            currentlyTouched = false;
        } else {
            xbuffer[bufferIndex] = last_touch_x;
            ybuffer[bufferIndex] = last_touch_y;
            bufferIndex = (bufferIndex + 1) % TOUCH_BUFFER_SIZE;
            touchSinceLastRead = true;
        }
    }
    if (!currentlyTouched) {
       // HAL_GPIO_WritePin(WATER_LED_GPIO_Port, WATER_LED_Pin, GPIO_PIN_RESET);
    }
}

uint32_t flush_touch_buffer(uint16_t *buffer, bool avg) {
    uint32_t avg_value = 0;
    if (avg) {
        uint8_t samplesInBuffer = 0;
        for (uint8_t i = 0; i < TOUCH_BUFFER_SIZE; i++) {
            if (buffer[i] == 0) continue;
            avg_value += buffer[i];
            samplesInBuffer++;
            buffer[i] = 0;
        }
        if (samplesInBuffer) avg_value = avg_value / samplesInBuffer;
    } else {
        for (uint8_t i = 0; i < TOUCH_BUFFER_SIZE; i++) {
            buffer[i] = 0;
        }
    }
    return avg_value;
}


// touchpad interrupt callback functions

/* 
void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == TOUCH_IRQ_Pin) {
        currentlyTouched = true;
        touchSinceLastRead = true;
    }
}
*/
/*
void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == TOUCH_IRQ_Pin) {
        currentlyTouched = false;
        touchSinceLastRead = true;
    }
}
*/


