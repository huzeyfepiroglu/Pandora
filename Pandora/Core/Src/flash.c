#include "flash.h"
#include "definitions.h"

#define FLASH_SECTOR     7
#define FLASH_ADDR       (FLASH_BASE_BANK1 + (FLASH_SECTOR * FLASH_SECTOR_SIZE))

static const eeprom defaultValues = {
	.cockingHandleArmedDistance = 10,
	.cockingHandleSafeDistance  = 5,
	.solenoidFastRpm            = 3000,
	.solenoidSlowRpm            = 1500,
	.solenoidFireMode           = 1,
	.solenoidTime               = 50,
	.solenoidActiveTime         = 20,
	.solenoidPassiveTime        = 30
};

void functionLoadFromFlash(void)
{
	const eeprom* flash_ptr = (const eeprom*)FLASH_ADDR;

	if (*(const uint32_t*)flash_ptr != 0xFFFFFFFF) {
		memcpy(&pandora.eeprom, flash_ptr, sizeof(eeprom));
	} else {
		memcpy(&pandora.eeprom, &defaultValues, sizeof(eeprom));
	}
}

void functionSaveToFlash(void)
{
	uint8_t buffer[FLASH_WORD_SIZE];
	memset(buffer, 0xFF, sizeof(buffer));
	memcpy(buffer, &pandora.eeprom, sizeof(eeprom));

	FLASH_EraseInitTypeDef eraseInit;
	uint32_t sectorError;

	eraseInit.TypeErase    = FLASH_TYPEERASE_SECTORS;
	eraseInit.Banks        = FLASH_BANK_1;
	eraseInit.Sector       = FLASH_SECTOR;
	eraseInit.NbSectors    = 1;
	eraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3;

	HAL_FLASH_Unlock();
	HAL_FLASHEx_Erase(&eraseInit, &sectorError);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_FLASHWORD, EEPROM_FLASH_ADDR, (uint64_t*)buffer);
	HAL_FLASH_Lock();
}
