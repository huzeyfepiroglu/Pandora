/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins
     PH0-OSC_IN (PH0)   ------> RCC_OSC_IN
     PH1-OSC_OUT (PH1)   ------> RCC_OSC_OUT
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, COCKING_HANDLE_DRV_H_BACKWARD_Pin|COCKING_HANDLE_DRV_H_FORWARD_Pin|COCKING_HANDLE_POWER_Pin|SOLENOID_POWER_Pin
                          |SOLENOID_DRV_2_Pin|SOLENOID_DRV_1_Pin|SOLENOID_DRV_H_REVERSE_Pin|SOLENOID_DRV_H_FORWARD_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CASE_LED_GPIO_Port, CASE_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, EOS_POWER_Pin|SERVO_POWER_Pin|AKB_POWER_Pin|KKU_POWER_Pin
                          |BRAKE_DRV_12V_Pin|BRAKE_DRV_28V_Pin|EMERGENCY_STOP_RESET_Pin|SYSTEM_ON_OFF_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PGPin PGPin PGPin PGPin
                           PGPin PGPin PGPin PGPin */
  GPIO_InitStruct.Pin = COCKING_HANDLE_DRV_H_BACKWARD_Pin|COCKING_HANDLE_DRV_H_FORWARD_Pin|COCKING_HANDLE_POWER_Pin|SOLENOID_POWER_Pin
                          |SOLENOID_DRV_2_Pin|SOLENOID_DRV_1_Pin|SOLENOID_DRV_H_REVERSE_Pin|SOLENOID_DRV_H_FORWARD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = CASE_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CASE_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PDPin PDPin PDPin PDPin
                           PDPin PDPin PDPin PDPin */
  GPIO_InitStruct.Pin = EOS_POWER_Pin|SERVO_POWER_Pin|AKB_POWER_Pin|KKU_POWER_Pin
                          |BRAKE_DRV_12V_Pin|BRAKE_DRV_28V_Pin|EMERGENCY_STOP_RESET_Pin|SYSTEM_ON_OFF_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PDPin PDPin PDPin PDPin
                           PDPin PDPin */
  GPIO_InitStruct.Pin = EMERGENCY_STOP_FEEDBACK_Pin|SYSTEM_ON_OFF_FEEDBACK_Pin|SWITCHES_FIRE_FEEDBACK_Pin|SWITCHES_SAFETY_FEEDBACK_Pin
                          |SWITCHES_COCKING_HANDLE_HOME_Pin|SWITCHES_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PGPin PGPin PGPin PGPin
                           PGPin */
  GPIO_InitStruct.Pin = SWITCHES_SMGA_Pin|SWITCHES_4_Pin|SWITCHES_5_Pin|SWITCHES_6_Pin
                          |SWITCHES_7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
