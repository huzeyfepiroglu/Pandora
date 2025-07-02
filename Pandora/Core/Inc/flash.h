/*
 * flash.h
 *
 *  Created on: Jul 2, 2025
 *      Author: ADMIN
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include "main.h"
#include <stdbool.h>

// Ortak flash parametreleri
#define FLASH_PAGE_SIZE        0x20000U   // 128 KB
#define FLASH_BASE_BANK1       0x08000000U
#define FLASH_BASE_BANK2       0x08100000U
#define FLASH_WORD_SIZE        32U        // 256 bit = 32 byte

// 16-bit slot sistemi
#define FLASH16_SLOT_COUNT     16         // 32 byte / 2 = 16 adet 16-bit slot

// 8-bit slot sistemi
#define FLASH8_SLOT_COUNT      32         // 32 byte / 1 = 32 adet 8-bit slot

// 16-bit tipi işlemler
HAL_StatusTypeDef Flash_ErasePage(uint32_t pageNumber);
HAL_StatusTypeDef Flash_Write16AtOffset(uint32_t pageNumber, uint8_t offset_in_bytes, uint16_t value);
uint16_t Flash_Read16(uint32_t address);
bool Flash_IsEmpty16(uint32_t address);

// 8-bit tipi işlemler
HAL_StatusTypeDef Flash_Write8AtOffset(uint32_t pageNumber, uint8_t offset, uint8_t value);
uint8_t Flash_Read8(uint32_t address);
bool Flash_IsEmpty8(uint32_t address);

#endif /* INC_FLASH_H_ */
