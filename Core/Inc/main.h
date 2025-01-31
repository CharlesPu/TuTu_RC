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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdarg.h>
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
#define DOGGY_Pin GPIO_PIN_13
#define DOGGY_GPIO_Port GPIOC
#define SW1_2_Pin GPIO_PIN_14
#define SW1_2_GPIO_Port GPIOC
#define SW1_3_Pin GPIO_PIN_15
#define SW1_3_GPIO_Port GPIOC
#define RK1_X_Pin GPIO_PIN_1
#define RK1_X_GPIO_Port GPIOA
#define BLE_TX_Pin GPIO_PIN_2
#define BLE_TX_GPIO_Port GPIOA
#define BLE_RX_Pin GPIO_PIN_3
#define BLE_RX_GPIO_Port GPIOA
#define RK1_Y_Pin GPIO_PIN_4
#define RK1_Y_GPIO_Port GPIOA
#define NRF_SCK_Pin GPIO_PIN_5
#define NRF_SCK_GPIO_Port GPIOA
#define NRF_MISO_Pin GPIO_PIN_6
#define NRF_MISO_GPIO_Port GPIOA
#define NRF_MOSI_Pin GPIO_PIN_7
#define NRF_MOSI_GPIO_Port GPIOA
#define RK2_Y_Pin GPIO_PIN_0
#define RK2_Y_GPIO_Port GPIOB
#define RK2_X_Pin GPIO_PIN_1
#define RK2_X_GPIO_Port GPIOB
#define MPU_I2C_SCL_Pin GPIO_PIN_10
#define MPU_I2C_SCL_GPIO_Port GPIOB
#define MPU_I2C_SDA_Pin GPIO_PIN_11
#define MPU_I2C_SDA_GPIO_Port GPIOB
#define VIB_MOTOR_Pin GPIO_PIN_12
#define VIB_MOTOR_GPIO_Port GPIOB
#define BEEP_Pin GPIO_PIN_13
#define BEEP_GPIO_Port GPIOB
#define KEY1_Pin GPIO_PIN_14
#define KEY1_GPIO_Port GPIOB
#define KEY2_Pin GPIO_PIN_15
#define KEY2_GPIO_Port GPIOB
#define RK1_Z_Pin GPIO_PIN_8
#define RK1_Z_GPIO_Port GPIOA
#define RK2_Z_Pin GPIO_PIN_11
#define RK2_Z_GPIO_Port GPIOA
#define SW2_1_Pin GPIO_PIN_12
#define SW2_1_GPIO_Port GPIOA
#define SW2_2_Pin GPIO_PIN_15
#define SW2_2_GPIO_Port GPIOA
#define SW2_3_Pin GPIO_PIN_3
#define SW2_3_GPIO_Port GPIOB
#define NRF_IRQ_Pin GPIO_PIN_4
#define NRF_IRQ_GPIO_Port GPIOB
#define NRF_CE_Pin GPIO_PIN_5
#define NRF_CE_GPIO_Port GPIOB
#define OLED_SCL_Pin GPIO_PIN_6
#define OLED_SCL_GPIO_Port GPIOB
#define OLED_SDA_Pin GPIO_PIN_7
#define OLED_SDA_GPIO_Port GPIOB
#define NRF_CS_Pin GPIO_PIN_8
#define NRF_CS_GPIO_Port GPIOB
#define SW1_1_Pin GPIO_PIN_9
#define SW1_1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define MODULE_MPU6050
#define MODULE_NRF24L01_TX

#define DBG 0
#define INF 1
#define ERR 2
#define LOG_LEVEL DBG
 
#define LOG(level, format, ...)                                                             \
    do                                                                                      \
    {                                                                                       \
        if (level < LOG_LEVEL)                                                              \
            break;                                                                          \
        fprintf(stdout, "[%s:%d][%s] " format "\n", __FILE__, __LINE__, __FUNCTION__,##__VA_ARGS__); \
    } while (0)
 
#define INF_LOG(format, ...) LOG(INF, format, ##__VA_ARGS__)
#define DBG_LOG(format, ...) LOG(DBG, format, ##__VA_ARGS__)
#define ERR_LOG(format, ...) LOG(ERR, format, ##__VA_ARGS__)
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
