/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h5xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define USB_FS

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DISPLAY_SCK_Pin GPIO_PIN_2
#define DISPLAY_SCK_GPIO_Port GPIOE
#define DISPLAY_DC_Pin GPIO_PIN_3
#define DISPLAY_DC_GPIO_Port GPIOE
#define DISPLAY_CS_Pin GPIO_PIN_4
#define DISPLAY_CS_GPIO_Port GPIOE
#define DISPLAY_MISO_Pin GPIO_PIN_5
#define DISPLAY_MISO_GPIO_Port GPIOE
#define DISPLAY_MOSI_Pin GPIO_PIN_6
#define DISPLAY_MOSI_GPIO_Port GPIOE
#define DISPLAY_RST_Pin GPIO_PIN_13
#define DISPLAY_RST_GPIO_Port GPIOC
#define WATER_LED_Pin GPIO_PIN_1
#define WATER_LED_GPIO_Port GPIOC
#define RGB_MOSI_Pin GPIO_PIN_3
#define RGB_MOSI_GPIO_Port GPIOC
#define BOOST_EN_Pin GPIO_PIN_2
#define BOOST_EN_GPIO_Port GPIOA
#define SD_CS_Pin GPIO_PIN_4
#define SD_CS_GPIO_Port GPIOA
#define SD_SCK_Pin GPIO_PIN_5
#define SD_SCK_GPIO_Port GPIOA
#define SD_MISO_Pin GPIO_PIN_6
#define SD_MISO_GPIO_Port GPIOA
#define SD_MOSI_Pin GPIO_PIN_7
#define SD_MOSI_GPIO_Port GPIOA
#define TRANDUCER_PWM_Pin GPIO_PIN_0
#define TRANDUCER_PWM_GPIO_Port GPIOB
#define FAN_PWM_Pin GPIO_PIN_1
#define FAN_PWM_GPIO_Port GPIOB
#define SHT31_SDA_Pin GPIO_PIN_9
#define SHT31_SDA_GPIO_Port GPIOC
#define SHT31_SCL_Pin GPIO_PIN_8
#define SHT31_SCL_GPIO_Port GPIOA
#define TOUCH_SCK_Pin GPIO_PIN_3
#define TOUCH_SCK_GPIO_Port GPIOB
#define TOUCH_MISO_Pin GPIO_PIN_4
#define TOUCH_MISO_GPIO_Port GPIOB
#define TOUCH_MOSI_Pin GPIO_PIN_5
#define TOUCH_MOSI_GPIO_Port GPIOB
#define TOUCH_IRQ_Pin GPIO_PIN_6
#define TOUCH_IRQ_GPIO_Port GPIOB
#define TOUCH_CS_Pin GPIO_PIN_15
#define TOUCH_CS_GPIO_Port GPIOA
#define DISPLAY_LED_Pin GPIO_PIN_8
#define DISPLAY_LED_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define USE_TEST_UNIT


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
