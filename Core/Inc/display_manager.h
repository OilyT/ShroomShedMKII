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
#include "ui.h"
#include "screens.h"


void displayProcess(void);
void initDisplay(void);
void poll_touchpad(void);
void switch_screen(enum ScreensEnum screen);

#endif /* __DISPLAY_MANAGER_H */
