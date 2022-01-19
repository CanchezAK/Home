/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f1xx_hal.h"

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

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define D7_Pin GPIO_PIN_4
#define D7_GPIO_Port GPIOA
#define D6_Pin GPIO_PIN_5
#define D6_GPIO_Port GPIOA
#define D5_Pin GPIO_PIN_6
#define D5_GPIO_Port GPIOA
#define D4_Pin GPIO_PIN_7
#define D4_GPIO_Port GPIOA
#define E_Pin GPIO_PIN_2
#define E_GPIO_Port GPIOB
#define R_W_Pin GPIO_PIN_10
#define R_W_GPIO_Port GPIOB
#define RS_Pin GPIO_PIN_11
#define RS_GPIO_Port GPIOB
#define BTN_4_Pin GPIO_PIN_11
#define BTN_4_GPIO_Port GPIOA
#define BTN_3_Pin GPIO_PIN_12
#define BTN_3_GPIO_Port GPIOA
#define LED_BTN_1_Pin GPIO_PIN_15
#define LED_BTN_1_GPIO_Port GPIOA
#define LED_BTN_2_Pin GPIO_PIN_10
#define LED_BTN_2_GPIO_Port GPIOC
#define LED_BTN_3_Pin GPIO_PIN_11
#define LED_BTN_3_GPIO_Port GPIOC
#define LED_BTN_4_Pin GPIO_PIN_12
#define LED_BTN_4_GPIO_Port GPIOC
#define LED_BTN_5_Pin GPIO_PIN_2
#define LED_BTN_5_GPIO_Port GPIOD
#define LED_BTN_6_Pin GPIO_PIN_3
#define LED_BTN_6_GPIO_Port GPIOB
#define BTN_1_Pin GPIO_PIN_4
#define BTN_1_GPIO_Port GPIOB
#define BTN_2_Pin GPIO_PIN_5
#define BTN_2_GPIO_Port GPIOB
#define BTN_5_Pin GPIO_PIN_8
#define BTN_5_GPIO_Port GPIOB
#define BTN_6_Pin GPIO_PIN_9
#define BTN_6_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
