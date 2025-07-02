/*
 * functions.c
 *
 *  Created on: Jan 8, 2025
 *      Author: ADMIN
 */
#include "functions.h"
#include "peripherals.h"
#include "definitions.h"
#include "flash.h"

extern pandoraStructer pandora;

void function_solenoid(uint8_t *data)
{
	//UNIT_CONTROL(LED,ON);
	uint8_t value = false;//FEEDBACK_READ(BUTTON);

	if(value == HIGH)
	{

	}
}

void functionFlashGetVal(void)
{

}

void functionFlashWrite(void)
{

}

void functionFlashWriteDefault(void)
{
	uint32_t index = 0;
	//default degerler düzenlenecek
	defaultTkkConfig.yMin = 12000;
	defaultTkkConfig.yMax = 15000;
	defaultTkkConfig.yMid = 19000;

	defaultTkkConfig.xMin = 12000;
	defaultTkkConfig.xMax = 15000;
	defaultTkkConfig.xMid = 19000;
	for(index = 0; index < BUTTON_COUNT; index++)
	{
		defaultTkkConfig.debounceFactor[index] = 20;
	}

	defaultTkkConfig.tkkModSelection = TKK_MOD_RS422;

	volatile uint32_t i = 0;
	HAL_FLASH_Unlock();
	static FLASH_EraseInitTypeDef EraseInitStructDefaultPage;
	EraseInitStructDefaultPage.TypeErase = FLASH_TYPEERASE_PAGES;
	EraseInitStructDefaultPage.PageAddress = DEFAULT_CONFIG_DATA_BASE_ADDR;
	EraseInitStructDefaultPage.NbPages = 1;

	if(HAL_FLASHEx_Erase(&EraseInitStructDefaultPage, &PAGEError) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, DEFAULT_CONFIG_DATA_INTERFACE_OFFSET		, defaultTkkConfig.tkkModSelection );
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, DEFAULT_CONFIG_DATA_X_MIDDLEPOINT_OFFSET	, defaultTkkConfig.xMid);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, DEFAULT_CONFIG_DATA_X_MINPOINT_OFFSET		, defaultTkkConfig.xMin);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, DEFAULT_CONFIG_DATA_X_MAXPOINT_OFFSET		, defaultTkkConfig.xMax);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, DEFAULT_CONFIG_DATA_Y_MIDDLEPOINT_OFFSET	, defaultTkkConfig.yMid);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, DEFAULT_CONFIG_DATA_Y_MINPOINT_OFFSET		, defaultTkkConfig.yMin);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, DEFAULT_CONFIG_DATA_Y_MAXPOINT_OFFSET		, defaultTkkConfig.yMax);

	for(i = 0; i < 32; i++)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, DEFAULT_CONFIG_DATA_DEBOUNCEFACTOR_BASE + i*CONFIG_FLASH_ADDR_INCREMENT, defaultTkkConfig.debounceFactor[i]);
	}

	HAL_FLASH_Lock();
}

uint16_t dataToWrite[] = {0x1234, 0xABCD, 0x5678, 0x9ABC, 0xDEAD};

void functionFlashDefaultValue(void)
{
    uint32_t defaultValuePage = 127; // Bank 1 son sayfa

    if (Flash_ErasePage(defaultValuePage) == HAL_OK)
    {
        Flash_Write16ToPage(defaultValuePage, dataToWrite, sizeof(dataToWrite)/2);

        for (int i = 0; i < sizeof(dataToWrite)/2; i++)
        {
            uint32_t addr = FLASH_BASE_BANK1 + (defaultValuePage * FLASH_PAGE_SIZE) + (i * 2);
            uint16_t val = Flash_Read16(addr);
            printf("Veri %d: 0x%04X\r\n", i, val);
        }
    }
}
