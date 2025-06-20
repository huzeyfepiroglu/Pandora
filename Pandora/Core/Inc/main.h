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
#include "stm32h7xx_hal.h"

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
#define MAIN_POWER_VOLTAGE_Pin GPIO_PIN_6
#define MAIN_POWER_VOLTAGE_GPIO_Port GPIOF
#define MAIN_POWER_CURRENT_Pin GPIO_PIN_7
#define MAIN_POWER_CURRENT_GPIO_Port GPIOF
#define SOLENOID_CURRENT_Pin GPIO_PIN_8
#define SOLENOID_CURRENT_GPIO_Port GPIOF
#define COCKING_HANDLE_CURRENT_Pin GPIO_PIN_9
#define COCKING_HANDLE_CURRENT_GPIO_Port GPIOF
#define EOS_CURRENT_Pin GPIO_PIN_11
#define EOS_CURRENT_GPIO_Port GPIOF
#define KKU_CURRENT_Pin GPIO_PIN_12
#define KKU_CURRENT_GPIO_Port GPIOF
#define AKB_CURRENT_Pin GPIO_PIN_13
#define AKB_CURRENT_GPIO_Port GPIOF
#define SERVO_CURRENT_Pin GPIO_PIN_14
#define SERVO_CURRENT_GPIO_Port GPIOF
#define COCKING_HANDLE_DRV_H_BACKWARD_Pin GPIO_PIN_1
#define COCKING_HANDLE_DRV_H_BACKWARD_GPIO_Port GPIOG
#define RS422_RX_2_Pin GPIO_PIN_7
#define RS422_RX_2_GPIO_Port GPIOE
#define RS422_TX_2_Pin GPIO_PIN_8
#define RS422_TX_2_GPIO_Port GPIOE
#define CASE_LED_Pin GPIO_PIN_11
#define CASE_LED_GPIO_Port GPIOE
#define EOS_POWER_Pin GPIO_PIN_9
#define EOS_POWER_GPIO_Port GPIOD
#define SERVO_POWER_Pin GPIO_PIN_10
#define SERVO_POWER_GPIO_Port GPIOD
#define AKB_POWER_Pin GPIO_PIN_11
#define AKB_POWER_GPIO_Port GPIOD
#define KKU_POWER_Pin GPIO_PIN_12
#define KKU_POWER_GPIO_Port GPIOD
#define BRAKE_DRV_12V_Pin GPIO_PIN_14
#define BRAKE_DRV_12V_GPIO_Port GPIOD
#define BRAKE_DRV_28V_Pin GPIO_PIN_15
#define BRAKE_DRV_28V_GPIO_Port GPIOD
#define COCKING_HANDLE_DRV_H_FORWARD_Pin GPIO_PIN_2
#define COCKING_HANDLE_DRV_H_FORWARD_GPIO_Port GPIOG
#define COCKING_HANDLE_POWER_Pin GPIO_PIN_3
#define COCKING_HANDLE_POWER_GPIO_Port GPIOG
#define SOLENOID_POWER_Pin GPIO_PIN_4
#define SOLENOID_POWER_GPIO_Port GPIOG
#define SOLENOID_DRV_2_Pin GPIO_PIN_5
#define SOLENOID_DRV_2_GPIO_Port GPIOG
#define SOLENOID_DRV_1_Pin GPIO_PIN_6
#define SOLENOID_DRV_1_GPIO_Port GPIOG
#define SOLENOID_DRV_H_REVERSE_Pin GPIO_PIN_7
#define SOLENOID_DRV_H_REVERSE_GPIO_Port GPIOG
#define SOLENOID_DRV_H_FORWARD_Pin GPIO_PIN_8
#define SOLENOID_DRV_H_FORWARD_GPIO_Port GPIOG
#define ENCODER_1_PHASE_A_Pin GPIO_PIN_6
#define ENCODER_1_PHASE_A_GPIO_Port GPIOC
#define ENCODER_1_PHASE_B_Pin GPIO_PIN_7
#define ENCODER_1_PHASE_B_GPIO_Port GPIOC
#define ENCODER_2_PHASE_A_Pin GPIO_PIN_8
#define ENCODER_2_PHASE_A_GPIO_Port GPIOA
#define ENCODER_2_PHASE_B_Pin GPIO_PIN_9
#define ENCODER_2_PHASE_B_GPIO_Port GPIOA
#define RS422_TX_1_Pin GPIO_PIN_10
#define RS422_TX_1_GPIO_Port GPIOC
#define RS422_RX_1_Pin GPIO_PIN_11
#define RS422_RX_1_GPIO_Port GPIOC
#define EMERGENCY_STOP_RESET_Pin GPIO_PIN_0
#define EMERGENCY_STOP_RESET_GPIO_Port GPIOD
#define EMERGENCY_STOP_FEEDBACK_Pin GPIO_PIN_1
#define EMERGENCY_STOP_FEEDBACK_GPIO_Port GPIOD
#define SYSTEM_ON_OFF_Pin GPIO_PIN_2
#define SYSTEM_ON_OFF_GPIO_Port GPIOD
#define SWITCHES_FIRE_ORDER_Pin GPIO_PIN_3
#define SWITCHES_FIRE_ORDER_GPIO_Port GPIOD
#define SWITCHES_SAFETY_Pin GPIO_PIN_4
#define SWITCHES_SAFETY_GPIO_Port GPIOD
#define SYSTEM_ON_OFFD5_Pin GPIO_PIN_5
#define SYSTEM_ON_OFFD5_GPIO_Port GPIOD
#define SWITCHES_COCKING_HANDLE_ORDER_Pin GPIO_PIN_6
#define SWITCHES_COCKING_HANDLE_ORDER_GPIO_Port GPIOD
#define SWITCHES_MOVEMENT_ALLOWED_Pin GPIO_PIN_7
#define SWITCHES_MOVEMENT_ALLOWED_GPIO_Port GPIOD
#define SWITCHES_SMGA_Pin GPIO_PIN_9
#define SWITCHES_SMGA_GPIO_Port GPIOG
#define SWITCHES_SYSTEM_ON_OFF_Pin GPIO_PIN_10
#define SWITCHES_SYSTEM_ON_OFF_GPIO_Port GPIOG
#define SWITCHES_CREW_1_Pin GPIO_PIN_11
#define SWITCHES_CREW_1_GPIO_Port GPIOG
#define SWITCHES_CREW_2_Pin GPIO_PIN_12
#define SWITCHES_CREW_2_GPIO_Port GPIOG
#define SWITCHES_COCKING_HANDLE_HOME_Pin GPIO_PIN_13
#define SWITCHES_COCKING_HANDLE_HOME_GPIO_Port GPIOG
#define RTC_I2C_SDA_Pin GPIO_PIN_7
#define RTC_I2C_SDA_GPIO_Port GPIOB
#define RTC_I2C_SCL_Pin GPIO_PIN_8
#define RTC_I2C_SCL_GPIO_Port GPIOB
#define RS485_RX_Pin GPIO_PIN_0
#define RS485_RX_GPIO_Port GPIOE
#define RS485_TX_Pin GPIO_PIN_1
#define RS485_TX_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
