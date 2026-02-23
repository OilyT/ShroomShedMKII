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

void displayProcess(void);
void initDisplay(void);
void poll_touchpad(void);

#endif /* __DISPLAY_MANAGER_H */
