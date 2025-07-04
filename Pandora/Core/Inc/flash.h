/*
 * flash.h
 *
 *  Created on: Jul 2, 2025
 *      Author: ADMIN
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include "main.h"

#define FLASH_BASE_BANK1       0x08000000U

void EEPROM_LoadFromFlash(void);
void EEPROM_SaveToFlash(void);

#endif /* INC_FLASH_H_ */
