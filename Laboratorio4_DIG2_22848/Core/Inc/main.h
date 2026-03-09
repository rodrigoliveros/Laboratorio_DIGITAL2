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
#include "stm32f4xx_hal.h"

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
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define DPLY_A_Pin GPIO_PIN_0
#define DPLY_A_GPIO_Port GPIOC
#define DPLY_B_Pin GPIO_PIN_1
#define DPLY_B_GPIO_Port GPIOC
#define DPLY_C_Pin GPIO_PIN_2
#define DPLY_C_GPIO_Port GPIOC
#define DPLY_D_Pin GPIO_PIN_3
#define DPLY_D_GPIO_Port GPIOC
#define B_START_Pin GPIO_PIN_0
#define B_START_GPIO_Port GPIOA
#define B_START_EXTI_IRQn EXTI0_IRQn
#define B_P1_Pin GPIO_PIN_1
#define B_P1_GPIO_Port GPIOA
#define B_P1_EXTI_IRQn EXTI1_IRQn
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define B_P2_Pin GPIO_PIN_4
#define B_P2_GPIO_Port GPIOA
#define B_P2_EXTI_IRQn EXTI4_IRQn
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define DPLY_E_Pin GPIO_PIN_4
#define DPLY_E_GPIO_Port GPIOC
#define DPLY_F_Pin GPIO_PIN_5
#define DPLY_F_GPIO_Port GPIOC
#define LED1_10_Pin GPIO_PIN_0
#define LED1_10_GPIO_Port GPIOB
#define LED1_20_Pin GPIO_PIN_1
#define LED1_20_GPIO_Port GPIOB
#define LED1_30_Pin GPIO_PIN_2
#define LED1_30_GPIO_Port GPIOB
#define LED1_40_Pin GPIO_PIN_10
#define LED1_40_GPIO_Port GPIOB
#define LED2_10_Pin GPIO_PIN_12
#define LED2_10_GPIO_Port GPIOB
#define LED2_20_Pin GPIO_PIN_13
#define LED2_20_GPIO_Port GPIOB
#define LED2_30_Pin GPIO_PIN_14
#define LED2_30_GPIO_Port GPIOB
#define LED2_40_Pin GPIO_PIN_15
#define LED2_40_GPIO_Port GPIOB
#define DPLY_G_Pin GPIO_PIN_6
#define DPLY_G_GPIO_Port GPIOC
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
