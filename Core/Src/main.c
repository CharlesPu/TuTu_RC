/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "oled_u8g2.h"
#include "nrf24l01.h"
#include "rc.h"
#include "buzzer.h"
#include "vib_motor.h"
#include "mpu6050.h"

#ifdef MODULE_MPU6050
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#endif
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	HAL_Delay(100); // for oled

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_TIM4_Init();
  MX_ADC1_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  BUZZER_init();
  VIBMOTOR_init();
  OLED_U8G2_init();
  RC_init();

// #ifdef MODULE_MPU6050
//   MPU_Init();					       //��ʼ��MPU6050
//   uint8_t res = 0;
//   do{
//     res = mpu_dmp_init();
// 		ERR_LOG("mpu_dmp_init fail code: %d\r\n",res);
// 	}while (res);
// #endif

  HAL_Delay(2000);
  BUZZER_beep_twice();
  VIBMOTOR_vibrate_once();
  INF_LOG("tutu rc start!\r\n");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  uint64_t loop_cnt=0;
  RC_MODE rc_mode = RC_KEYS;
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    // OLED_U8G2_draw_test();
    // RK_get_xyzVal();
    imu_data_t imu_data;
// #ifdef MODULE_MPU6050
//     res = mpu_dmp_get_data(&imu_data);
//     if(!res)
// 			imu_data.temp = MPU_Get_Temperature();
// 		else
//       ERR_LOG("mpu_dmp_get_data fail: %d\r\n", res);
// #endif
    //////////////////////////////  1s   ///////////////////////////////// 
    if (loop_cnt % 100 == 0) {
      HAL_GPIO_TogglePin(DOGGY_GPIO_Port, DOGGY_Pin);
      // printf("hello purui!\r\n");
#ifdef MODULE_MPU6050   
      // OLED_U8G2_draw_mpu6050(&imu_data);
#endif
    }
    //////////////////////////////  50ms   ///////////////////////////////// 
    if (loop_cnt % 5 == 1) {
      rc_keys_t rc_keys = RC_get_keys();
      if (rc_keys.sw_right.sw_2) {
        if (rc_mode == RC_KEYS){ // 第一次切换�?�来
        #ifdef MODULE_MPU6050
          MPU_Init();					    
          uint8_t res = 0;
          do{
            res = mpu_dmp_init();
            ERR_LOG("mpu_dmp_init fail code: %d\r\n",res);
          }while (res);
        #endif
          VIBMOTOR_vibrate_once();
        }
        rc_mode = RC_IMU;
        #ifdef MODULE_MPU6050
            uint8_t res = mpu_dmp_get_data(&imu_data);
            if(!res)
              imu_data.temp = MPU_Get_Temperature();
            else
              ERR_LOG("mpu_dmp_get_data fail: %d\r\n", res);
        #endif
      }else {
        rc_mode = RC_KEYS;
      }
      RC_control(&imu_data, &rc_keys);
    }

    HAL_Delay(10);
    loop_cnt++;
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
