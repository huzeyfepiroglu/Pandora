#include "flash.h"
#include <string.h>

static uint32_t GetPageAddress(uint32_t pageNumber)
{
    if (pageNumber < 128)
        return FLASH_BASE_BANK1 + (pageNumber * FLASH_PAGE_SIZE);
    else
        return FLASH_BASE_BANK2 + ((pageNumber - 128) * FLASH_PAGE_SIZE);
}

static uint32_t GetPageBank(uint32_t pageNumber)
{
    return (pageNumber < 128) ? FLASH_BANK_1 : FLASH_BANK_2;
}

HAL_StatusTypeDef Flash_ErasePage(uint32_t pageNumber)
{
    FLASH_EraseInitTypeDef eraseInit;
    uint32_t pageError;

    eraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
    eraseInit.Banks = GetPageBank(pageNumber);
    eraseInit.Page = (pageNumber < 128) ? pageNumber : (pageNumber - 128);
    eraseInit.NbPages = 1;

    HAL_FLASH_Unlock();
    HAL_StatusTypeDef status = HAL_FLASHEx_Erase(&eraseInit, &pageError);
    HAL_FLASH_Lock();

    return status;
}

// 16-bit veri yazımı
HAL_StatusTypeDef Flash_Write16AtOffset(uint32_t pageNumber, uint8_t offset, uint16_t value)
{
    if (offset % 2 != 0 || offset >= FLASH_WORD_SIZE) return HAL_ERROR;

    uint8_t buffer[FLASH_WORD_SIZE];
    memset(buffer, 0xFF, sizeof(buffer));

    buffer[offset]     = value & 0xFF;
    buffer[offset + 1] = (value >> 8) & 0xFF;

    uint32_t address = GetPageAddress(pageNumber);

    HAL_FLASH_Unlock();
    HAL_StatusTypeDef status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_FLASHWORD, address, (uint64_t*)buffer);
    HAL_FLASH_Lock();

    return status;
}

uint16_t Flash_Read16(uint32_t address)
{
    return *(volatile uint16_t*)address;
}

bool Flash_IsEmpty16(uint32_t address)
{
    return (*(volatile uint16_t*)address == 0xFFFF);
}

// 8-bit veri yazımı
HAL_StatusTypeDef Flash_Write8AtOffset(uint32_t pageNumber, uint8_t offset, uint8_t value)
{
    if (offset >= FLASH_WORD_SIZE) return HAL_ERROR;

    uint8_t buffer[FLASH_WORD_SIZE];
    memset(buffer, 0xFF, sizeof(buffer));

    buffer[offset] = value;

    uint32_t address = GetPageAddress(pageNumber);

    HAL_FLASH_Unlock();
    HAL_StatusTypeDef status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_FLASHWORD, address, (uint64_t*)buffer);
    HAL_FLASH_Lock();

    return status;
}

uint8_t Flash_Read8(uint32_t address)
{
    return *(volatile uint8_t*)address;
}

bool Flash_IsEmpty8(uint32_t address)
{
    return (*(volatile uint8_t*)address == 0xFF);
}
