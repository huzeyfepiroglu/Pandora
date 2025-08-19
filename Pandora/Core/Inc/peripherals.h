/*
 * peripherals.h
 *
 *  Created on: Jan 9, 2025
 *      Author: ABDULLAH HUZEYFE PIROGLU
 */

#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

#include "main.h"
#include "fdcan.h"
#include "stdbool.h"
#include "stdint.h"

/*
 * GET_BIT			: Belirli bir bitin değerini oku (0 veya 1)
 * SET_BIT			: Belirli bir biti 1 yap
 * CLEAR_BIT		: Belirli bir biti 0 yap
 * TOGGLE_BIT		: Belirli bir bitin değerini tersine çevir (0 ise 1, 1 ise 0)
 * UNIT_CONTROL		: HAL_GPIO_WritePin
 * MOTOR_CONTROL	: HAL_GPIO_WritePin
 * FEEDBACK_READ	: HAL_GPIO_ReadPin
 * SWITCH_READ		: HAL_GPIO_ReadPin
 * DEVICE_ADC_READ	: HAL_ADC_Start
 * SEND_CAN_MESSAGE	: FDCAN_SendMessage
 */
//#define SWITCH_INT_READ(sw) (switches_array[sw].state)

#define GET_BIT(value, bit)     (((value) >> (bit)) & 0x01)

#define WRITE_BIT(value, bit, boolValue) \
    ((value) = ((value) & ~(1U << (bit))) | ((!!(boolValue)) << (bit)))

#define TOGGLE_BIT(value, bit)  ((value) ^= (1U << (bit)))

#define UNIT_CONTROL(device, action)  \
    HAL_GPIO_WritePin(device##_GPIO_Port, device##_Pin, (action == ON) ? GPIO_PIN_SET : GPIO_PIN_RESET)

#define MOTOR_CONTROL(mosfet, action)  \
    HAL_GPIO_WritePin(mosfet##_GPIO_Port, mosfet##_Pin, (action == ON) ? GPIO_PIN_SET : GPIO_PIN_RESET)

#define SOLENOID(mosfet, action)  \
    HAL_GPIO_WritePin(mosfet##_GPIO_Port, mosfet##_Pin, (action == ON) ? GPIO_PIN_SET : GPIO_PIN_RESET)

#define FEEDBACK_READ(device)  \
    (HAL_GPIO_ReadPin(device##_GPIO_Port, device##_Pin) == GPIO_PIN_SET ? HIGH : LOW)

#define SWITCH_READ(device)  \
    (HAL_GPIO_ReadPin(device##_GPIO_Port, device##_Pin) == GPIO_PIN_SET ? HIGH : LOW)

#define SEND_CAN_MESSAGE(id, data, lenght)  \
	FDCAN_SendMessage(&hfdcan2, id, (uint8_t *)(data), lenght)

/*&hfdcan1, 0x100,*/

#define BIT_0 0
#define BIT_1 1
#define BIT_2 2
#define BIT_3 3
#define BIT_4 4
#define BIT_5 5
#define BIT_6 6
#define BIT_7 7



///////


#define MAIN_POWER_VOLTAGE
#define MAIN_POWER_CURRENT
#define SOLENOID_CURRENT
#define COCKING_HANDLE_CURRENT
#define EOS_CURRENT
#define KKU_CURRENT
#define AKB_CURRENT
#define SERVO_CURRENT



#define RS422_RX_2
#define RS422_TX_2

#define CASE_LED

#define RTC_ALARM

#define SERVO_POWER
#define EOS_POWER
#define AKB_POWER
#define KKU_POWER
#define COCKING_HANDLE_POWER
#define SOLENOID_POWER

#define BRAKE_DRV_12V
#define BRAKE_DRV_28V

#define COCKING_HANDLE_DRV_H_FORWARD
#define COCKING_HANDLE_DRV_H_BACKWARD


#define SOLENOID_DRV_2
#define SOLENOID_DRV_1

#define SOLENOID_DRV_H_REVERSE
#define SOLENOID_DRV_H_FORWARD

#define ENCODER_1_PHASE_A
#define ENCODER_1_PHASE_B

#define ENCODER_2_PHASE_A
#define ENCODER_2_PHASE_B

#define RS422_TX_1
#define RS422_RX_1

#define EMERGENCY_STOP_RESET

#define EMERGENCY_STOP_FEEDBACK
#define SYSTEM_ON_OFF_FEEDBACK

#define SWITCHES_FIRE_FEEDBACK
#define SWITCHES_SAFETY_FEEDBACK
#define SWITCHES_COCKING_HANDLE
#define SWITCHES_SMGA
#define SWITCHES_COCKING_HANDLE_HOME
#define SWITCHES_4
#define SWITCHES_5
#define SWITCHES_6
#define SWITCHES_7


#define RTC_I2C_SDA
#define RTC_I2C_SCL

#define RS485_RX
#define RS485_TX
///////

void functionMeasure(void);
void functionReadFilteredDigitalInputs(void);
void functionReadDigitalInputs(void);

#endif /* PERIPHERALS_H_ */
