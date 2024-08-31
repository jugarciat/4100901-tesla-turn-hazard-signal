/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32l4xx_hal.h"

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
#define S1_Pin GPIO_PIN_1
#define S1_GPIO_Port GPIOA
#define S1_EXTI_IRQn EXTI1_IRQn
#define S2_Pin GPIO_PIN_4
#define S2_GPIO_Port GPIOA
#define S2_EXTI_IRQn EXTI4_IRQn
#define D1_Pin GPIO_PIN_5
#define D1_GPIO_Port GPIOA
#define D3_Pin GPIO_PIN_7
#define D3_GPIO_Port GPIOA
#define COLUMN1_Pin GPIO_PIN_10
#define COLUMN1_GPIO_Port GPIOB
#define COLUMN1_EXTI_IRQn EXTI15_10_IRQn
#define COLUMN4_Pin GPIO_PIN_7
#define COLUMN4_GPIO_Port GPIOC
#define COLUMN4_EXTI_IRQn EXTI9_5_IRQn
#define COLUMN2_Pin GPIO_PIN_8
#define COLUMN2_GPIO_Port GPIOA
#define COLUMN2_EXTI_IRQn EXTI9_5_IRQn
#define COLUMN3_Pin GPIO_PIN_9
#define COLUMN3_GPIO_Port GPIOA
#define COLUMN3_EXTI_IRQn EXTI9_5_IRQn
#define ROW1_Pin GPIO_PIN_10
#define ROW1_GPIO_Port GPIOA
#define ROW2_Pin GPIO_PIN_3
#define ROW2_GPIO_Port GPIOB
#define ROW4_Pin GPIO_PIN_4
#define ROW4_GPIO_Port GPIOB
#define ROW3_Pin GPIO_PIN_5
#define ROW3_GPIO_Port GPIOB
#define D4_Pin GPIO_PIN_6
#define D4_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
