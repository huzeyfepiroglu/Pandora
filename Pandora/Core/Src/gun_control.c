/*
 * gun_control.c
 *
 *  Created on: Jan 22, 2025
 *      Author: ADMIN
 */

#include "peripherals.h"
#include "definitions.h"
#include "gun_control.h"

// global structer
extern pandoraStructer pandora;

static uint32_t gunControl_getShotInterval(uint16_t rpm)
{
    return 60000 / rpm;
}

void gunControl_Init(void)
{
	SOLENOID(SOLENOID_DRV_1,OFF);

	pandora.gun.configurations.fastRpm 				= pandora.eeprom.fastRpm;
	pandora.gun.configurations.slowRpm 				= pandora.eeprom.slowRpm;
	pandora.gun.configurations.solenoidTime 		= pandora.eeprom.solenoidTime;
	pandora.gun.configurations.solenoidActiveTime  	= pandora.eeprom.solenoidActiveTime;
	pandora.gun.configurations.solenoidPassiveTime 	= pandora.eeprom.solenoidPassiveTime;
	pandora.gun.configurations.fireMode 			= pandora.eeprom.fireMode;

	pandora.states.solenoidActive 		= false;
	pandora.states.triggerHeld 			= false;
	pandora.states.changeTime 			= 0;
	pandora.states.burstCounter 		= 0;
	pandora.states.ammoCounter			= 0;
}

void gunControl_SetMode(FireMode_t mode)
{
    pandora.gun.configurations.fireMode = mode;
}

void gunControl_TriggerPressed(void)
{
    pandora.states.triggerHeld = true;
    pandora.states.burstCounter = 0;
    pandora.states.changeTime = HAL_GetTick();

    if (pandora.gun.configurations.fireMode == FIRE_MODE_SINGLE)
    {
        SOLENOID(SOLENOID_DRV_1,ON);
        pandora.states.solenoidActive = true;
    }
    else if (pandora.gun.configurations.fireMode == FIRE_MODE_FAST_BURST_3 || pandora.gun.configurations.fireMode == FIRE_MODE_FAST_BURST_5)
    {
        pandora.states.solenoidActive = true;
        SOLENOID(SOLENOID_DRV_1,ON);
    }
}

void gunControl_TriggerReleased(void)
{
    pandora.states.triggerHeld = false;
    pandora.states.solenoidActive = false;
    pandora.states.burstCounter = 0;
    SOLENOID(SOLENOID_DRV_1,OFF);
}

void gunControl_Process(uint32_t now)
{
    if (!pandora.states.triggerHeld && pandora.gun.configurations.fireMode != FIRE_MODE_SINGLE) return;

    switch (pandora.gun.configurations.fireMode)
    {
        case FIRE_MODE_SINGLE:
            if (pandora.states.solenoidActive && now - pandora.states.changeTime >= pandora.gun.configurations.solenoidTime)
            {
            	SOLENOID(SOLENOID_DRV_1,OFF);
                pandora.states.solenoidActive = false;
                pandora.states.ammoCounter++;
            }
            break;

        case FIRE_MODE_FAST_AUTO:
            if (pandora.states.solenoidActive && now - pandora.states.changeTime >= pandora.gun.configurations.solenoidActiveTime)
            {
            	SOLENOID(SOLENOID_DRV_1,OFF);
                pandora.states.solenoidActive = false;
                pandora.states.ammoCounter++;
                pandora.states.changeTime = now;
            }
            else if (!pandora.states.solenoidActive && now - pandora.states.changeTime >= pandora.gun.configurations.solenoidPassiveTime)
            {
            	SOLENOID(SOLENOID_DRV_1,ON);
                pandora.states.solenoidActive = true;
                pandora.states.changeTime = now;
            }
            break;

        case FIRE_MODE_FAST_BURST_3:
        case FIRE_MODE_FAST_BURST_5:
        {
            uint8_t target = (pandora.gun.configurations.fireMode == FIRE_MODE_FAST_BURST_3) ? 3 : 5;
            uint32_t burst_duration = gunControl_getShotInterval(pandora.gun.configurations.fastRpm) * target;

            if (pandora.states.solenoidActive && now - pandora.states.changeTime >= burst_duration)
            {
            	SOLENOID(SOLENOID_DRV_1,OFF);
                pandora.states.solenoidActive = false;
                pandora.states.ammoCounter += target;
            }
            break;
        }

        case FIRE_MODE_SLOW_AUTO:
            if (!pandora.states.solenoidActive && now - pandora.states.changeTime >= gunControl_getShotInterval(pandora.gun.configurations.slowRpm))
            {
            	SOLENOID(SOLENOID_DRV_1,ON);
                pandora.states.solenoidActive = true;
                pandora.states.changeTime = now;
            }
            else if (pandora.states.solenoidActive && now - pandora.states.changeTime >= pandora.gun.configurations.solenoidTime)
            {
            	SOLENOID(SOLENOID_DRV_1,OFF);
                pandora.states.solenoidActive = false;
                pandora.states.ammoCounter++;
                pandora.states.changeTime = now;
            }
            break;

        case FIRE_MODE_SLOW_BURST_3:
        case FIRE_MODE_SLOW_BURST_5:
        {
            uint8_t target = (pandora.gun.configurations.fireMode == FIRE_MODE_SLOW_BURST_3) ? 3 : 5;
            if (pandora.states.burstCounter >= target) break;

            if (!pandora.states.solenoidActive && now - pandora.states.changeTime >= gunControl_getShotInterval(pandora.gun.configurations.slowRpm))
            {
            	SOLENOID(SOLENOID_DRV_1,ON);
                pandora.states.solenoidActive = true;
                pandora.states.changeTime = now;
            }
            else if (pandora.states.solenoidActive && now - pandora.states.changeTime >= pandora.gun.configurations.solenoidTime)
            {
            	SOLENOID(SOLENOID_DRV_1,OFF);
                pandora.states.solenoidActive = false;
                pandora.states.ammoCounter++;
                pandora.states.burstCounter++;
                pandora.states.changeTime = now;
            }
            break;
        }

        default:
            break;
    }
}



//gunControl_Init();
//gunControl_SetMode(FIRE_MODE_FAST_AUTO);
//
//while (1) {
//    gunControl_Process(HAL_GetTick());
//
//    if (TetikBasildi()) {
//        gunControl_TriggerPressed();
//    } else {
//        gunControl_TriggerReleased();
//    }
//}
