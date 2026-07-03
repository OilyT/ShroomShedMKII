/**
******************************************************************************
* @file           : display_manager.h
* @brief          : Header for display_manager.c file. 
******************************************************************************
*/


#ifndef __DISPLAY_MANAGER_H
#define __DISPLAY_MANAGER_H

#include "main.h"
#include "lvgl.h"
#include "stm32h5xx_hal_tim.h"
#include "ui.h"
#include "screens.h"


#define RGB_16_BIT


#define DISPLAY_LED_TIMER htim4

extern TIM_HandleTypeDef DISPLAY_LED_TIMER;


void displayProcess(void);
void initDisplay(void);
void poll_touchpad(void);
void switch_screen(enum ScreensEnum screen);
void load_previous_screen(void);
void set_display_brightness(uint8_t brightness);

#endif /* __DISPLAY_MANAGER_H */
