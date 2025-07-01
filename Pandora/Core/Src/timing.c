/*
 * 	timing.c
 *
 *  Created on	: February 12, 2025
 *  Company		: ASELSAN KONYA
 *  Author		: ABDULLAH HUZEYFE PIROGLU
 *
 */


#include "timing.h"
#include "tim.h"
#include "cocking_handle_maingun.h"

uint8_t configurableTime = 1;

uint8_t  _configurableCounter 	= 0;
uint8_t  _1msCounter 	= 0;
uint8_t  _10msCounter 	= 0;
uint8_t	 _25msCounter   = 0;
uint8_t  _50msCounter 	= 0;
uint8_t  _100msCounter 	= 0;
uint8_t  _250msCounter 	= 0;
uint16_t _500msCounter 	= 0;
uint16_t _1sCounter 	= 0;
uint16_t _10sCounter 	= 0;

bool _configurableFlagScanStart 		= false;
bool _1msFlagScanStart 		= false;
bool _10msFlagScanStart 	= false;
bool _25msFlagScanStart 	= false;
bool _50msFlagScanStart 	= false;
bool _100msFlagScanStart 	= false;
bool _250msFlagScanStart 	= false;
bool _500msFlagScanStart 	= false;
bool _1sFlagScanStart 		= false;
bool _10sFlagScanStart		= false;

bool _configurableFlag	 			= false;
bool _1msFlag	 			= false;
bool _10msFlag	 			= false;
bool _25msFlag	 			= false;
bool _50msFlag	 			= false;
bool _100msFlag		 		= false;
bool _250msFlag		 		= false;
bool _500msFlag		 		= false;
bool _1sFlag				= false;
bool _10sFlag				= false;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3)   // şuan 50ms 1msye  ayarla
    {
    	functionEncoderRead(&htim3);		// her ms değerinde çağrılır. IDLE durumunda çağrılmayabilir #huzeyfe

    	_configurableCounter++;
    	if(_configurableCounter>configurableTime)
    	{
    		_configurableFlagScanStart = true;
    		_configurableCounter = 0;
    	}

    	_1msCounter++;
    	if(_1msCounter>0)
    	{
    		_1msFlagScanStart = true;
    		_1msCounter = 0;
    	}


    	_10msCounter++;
    	if(_10msCounter>9)
    	{
    		_10msFlagScanStart = true;
    		_10msCounter = 0;
    	}

    	_25msCounter++;
    	if(_25msCounter>24)
    	{
    		_25msFlagScanStart = true;
    		_25msCounter = 0;
    	}

    	_50msCounter++;
    	if(_50msCounter>49)
    	{
    		_50msFlagScanStart = true;
    		_50msCounter = 0;
    	}

    	_100msCounter++;
    	if(_100msCounter>99)
    	{
    		_100msFlagScanStart = true;
    		_100msCounter = 0;

    	}

    	_250msCounter++;
    	if(_250msCounter>249)
    	{
    		_250msFlagScanStart = true;
    		_250msCounter = 0;
    	}

    	_500msCounter++;
    	if(_500msCounter>499)
    	{
    		_500msFlagScanStart = true;
    		_500msCounter = 0;
    	}

    	_1sCounter++;
    	if(_1sCounter>999)
    	{
    		_1sFlagScanStart = true;
    		_1sCounter = 0;
    	}

    	_10sCounter++;
    	if(_10sCounter>9999)
    	{
    		_10sFlagScanStart = true;
    		_10sCounter = 0;
    	}
    }
}

void startTimeScanFlags(void)
{
	if(_configurableFlagScanStart)
	{
		_configurableFlag = true;
		_configurableFlagScanStart = false;
	}
	if(_1msFlagScanStart)
	{
		_1msFlag = true;
		_1msFlagScanStart = false;
	}
	if(_10msFlagScanStart)
	{
		_10msFlag = true;
		_10msFlagScanStart = false;
	}
	if(_25msFlagScanStart)
	{
		_25msFlag = true;
		_25msFlagScanStart = false;
	}
	if(_50msFlagScanStart)
	{
		_50msFlag = true;
		_50msFlagScanStart = false;
	}
	if(_100msFlagScanStart)
	{
		_100msFlag = true;
		_100msFlagScanStart = false;
	}
	if(_250msFlagScanStart)
	{
		_250msFlag = true;
		_250msFlagScanStart = false;
	}
	if(_500msFlagScanStart)
	{
		_500msFlag = true;
		_500msFlagScanStart = false;
	}
	if(_1sFlagScanStart)
	{
		_1sFlag = true;
		_1sFlagScanStart = false;
	}
	if(_10sFlagScanStart)
	{
		_10sFlag = true;
		_10sFlagScanStart = false;
	}
}

void clearTimeScanFlags(void)
{
	_configurableFlag 	= false;
	_1msFlag 	= false;
	_10msFlag 	= false;
	_25msFlag 	= false;
	_50msFlag 	= false;
	_100msFlag 	= false;
	_250msFlag 	= false;
	_500msFlag 	= false;
	_1sFlag 	= false;
	_10sFlag 	= false;
}
