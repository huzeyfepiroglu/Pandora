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

//#define COMMAND_HEADER 									0xA5
//#define COMMAND_ACK 									0xFF
//#define CHECKSUM_ACK 									0x01
//
//#define COMMAND_REFRESH_CONFIG_DATA 					0xBB
//#define COMMAND_SET_DEFAULT_CONFIG_DATA 				0xCC
//#define COMMAND_CALIBRATION_START 						0xDD
//
//#define COMMAND_MODSEL_WRITE 							0x01
//#define COMMAND_XCALIB_WRITE 							0x02
//#define COMMAND_YCALIB_WRITE 							0x03
//#define COMMAND_DEBOUNCE_WRITE 							0x04
//
//#define COMMAND_MODSEL_READ 							0x81
//#define COMMAND_XCALIB_READ 							0x82
//#define COMMAND_YCALIB_READ 							0x83
//#define COMMAND_DEBOUNCE_READ 							0x84
//
//#define COMMAND_DEFAULT_MODSEL_READ 					0x71
//#define COMMAND_DEFAULT_XCALIB_READ 					0x72
//#define COMMAND_DEFAULT_YCALIB_READ 					0x73
//#define COMMAND_DEFAULT_DEBOUNCE_READ 					0x74
//
//#define COMMAND_BOOT_MODE								0xC5
//#define COMMAND_SYSTEM_RESET    						0xD5

HAL_StatusTypeDef FDCAN_SendMessage(FDCAN_HandleTypeDef *hfdcan, uint32_t id, uint8_t *data, uint8_t length);
HAL_StatusTypeDef FDCAN_ReceiveMessage(FDCAN_HandleTypeDef *hfdcan);

void checkCommand(uint8_t* data);
void checkRequest(uint8_t* data);

void eventAKB(uint32_t id, uint8_t *data);
//void eventKKU(uint8_t *data, uint8_t dataLenght);
//void eventEOS(uint8_t *data, uint8_t dataLenght);
//void eventHERCULE(uint8_t *data, uint8_t dataLenght);

#endif /* CAN_MESSAGES_H_ */
