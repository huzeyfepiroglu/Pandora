/*
 * can_messages.h
 *
 *  Created on: Jan 8, 2025
 *      Author: AHP
 */

#ifndef CAN_MESSAGES_H_
#define CAN_MESSAGES_H_

#include "stdint.h"
#include "main.h"

HAL_StatusTypeDef FDCAN_SendMessage(FDCAN_HandleTypeDef *hfdcan, uint32_t id, uint8_t *data, uint8_t length);
HAL_StatusTypeDef FDCAN_ReceiveMessage(FDCAN_HandleTypeDef *hfdcan);

void eventAKB(uint32_t id, uint8_t *data, uint8_t dataLenght);
//void eventKKU(uint8_t *data, uint8_t dataLenght);
//void eventEOS(uint8_t *data, uint8_t dataLenght);
//void eventHERCULE(uint8_t *data, uint8_t dataLenght);

#endif /* CAN_MESSAGES_H_ */
