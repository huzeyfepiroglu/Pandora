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

static uint32_t functionGunControlGetShotInterval(uint16_t rpm)
{
    return 60000 / rpm;
}

void functionGunControlInit(void)
{
	SOLENOID(SOLENOID_DRV_1,OFF);

//	pandora.configurations.solenoidFastRpm 		= pandora.eeprom.solenoidFastRpm;
//	pandora.configurations.solenoidSlowRpm 		= pandora.eeprom.solenoidSlowRpm;
//	pandora.configurations.solenoidTime 		= pandora.eeprom.solenoidTime;
//	pandora.configurations.solenoidActiveTime  	= pandora.eeprom.solenoidActiveTime;
//	pandora.configurations.solenoidPassiveTime 	= pandora.eeprom.solenoidPassiveTime;
//	pandora.configurations.solenoidFireMode 	= pandora.eeprom.fireMode;

	pandora.states.solenoidActive 		= false;
	pandora.states.triggerHeld 			= false;
	pandora.states.changeTime 			= 0;
	pandora.states.burstCounter 		= 0;
	pandora.states.ammoCounter			= 0;
}

void functionGunControlTriggerPressed(void)
{
    pandora.states.triggerHeld = true;
    pandora.states.burstCounter = 0;
    pandora.states.changeTime = HAL_GetTick();

    if (pandora.canMessages.AKB.commandFireMode == FIRE_MODE_SINGLE)
    {
        SOLENOID(SOLENOID_DRV_1,ON);
        pandora.states.solenoidActive = true;
    }
    else if (pandora.canMessages.AKB.commandFireMode == FIRE_MODE_FAST_BURST_3 || pandora.canMessages.AKB.commandFireMode == FIRE_MODE_FAST_BURST_5)
    {
        pandora.states.solenoidActive = true;
        SOLENOID(SOLENOID_DRV_1,ON);
    }
}

void functionGunControlTriggerReleased(void)
{
    pandora.states.triggerHeld = false;
    pandora.states.solenoidActive = false;
    pandora.states.burstCounter = 0;
    SOLENOID(SOLENOID_DRV_1,OFF);
}

void functionGunControlProcess(uint32_t now)
{
    if (!pandora.states.triggerHeld && pandora.canMessages.AKB.commandFireMode != FIRE_MODE_SINGLE) return;

    switch (pandora.canMessages.AKB.commandFireMode)
    {
        case FIRE_MODE_SINGLE:
            if (pandora.states.solenoidActive && now - pandora.states.changeTime >= pandora.canMessages.AKB.solenoidTime)
            {
            	SOLENOID(SOLENOID_DRV_1,OFF);
                pandora.states.solenoidActive = false;
                pandora.states.ammoCounter++;
            }
            break;

        case FIRE_MODE_FAST_AUTO:
            if (pandora.canMessages.AKB.solenoidActiveTime && now - pandora.states.changeTime >= pandora.canMessages.AKB.solenoidActiveTime)
            {
            	SOLENOID(SOLENOID_DRV_1,OFF);
                pandora.states.solenoidActive = false;
                pandora.states.ammoCounter++;
                pandora.states.changeTime = now;
            }
            else if (!pandora.canMessages.AKB.solenoidActiveTime && now - pandora.states.changeTime >= pandora.canMessages.AKB.solenoidPassiveTime)
            {
            	SOLENOID(SOLENOID_DRV_1,ON);
                pandora.states.solenoidActive = true;
                pandora.states.changeTime = now;
            }
            break;

        case FIRE_MODE_FAST_BURST_3:
        case FIRE_MODE_FAST_BURST_5:
        {
            uint8_t target = (pandora.canMessages.AKB.commandFireMode == FIRE_MODE_FAST_BURST_3) ? 3 : 5;
            uint32_t burst_duration = functionGunControlGetShotInterval(pandora.canMessages.AKB.solenoidFastRpm) * target;

            if (pandora.states.solenoidActive && now - pandora.states.changeTime >= burst_duration)
            {
            	SOLENOID(SOLENOID_DRV_1,OFF);
                pandora.states.solenoidActive = false;
                pandora.states.ammoCounter += target;
            }
            break;
        }

        case FIRE_MODE_SLOW_AUTO:
            if (!pandora.canMessages.AKB.solenoidActiveTime && now - pandora.states.changeTime >= functionGunControlGetShotInterval(pandora.canMessages.AKB.solenoidSlowRpm))
            {
            	SOLENOID(SOLENOID_DRV_1,ON);
                pandora.states.solenoidActive = true;
                pandora.states.changeTime = now;
            }
            else if (pandora.canMessages.AKB.solenoidActiveTime && now - pandora.states.changeTime >= pandora.canMessages.AKB.solenoidTime)
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
            uint8_t target = (pandora.canMessages.AKB.commandFireMode == FIRE_MODE_SLOW_BURST_3) ? 3 : 5;
            if (pandora.states.burstCounter >= target) break;

            if (!pandora.canMessages.AKB.solenoidActiveTime && now - pandora.states.changeTime >= functionGunControlGetShotInterval(pandora.canMessages.AKB.solenoidSlowRpm))
            {
            	SOLENOID(SOLENOID_DRV_1,ON);
                pandora.states.solenoidActive = true;
                pandora.states.changeTime = now;
            }
            else if (pandora.canMessages.AKB.solenoidActiveTime && now - pandora.states.changeTime >= pandora.canMessages.AKB.solenoidTime)
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



//functionGunControlInit();
//functionGunControlSetMode(FIRE_MODE_FAST_AUTO);
//
//while (1) {
//    functionGunControlProcess(HAL_GetTick());
//
//    if (TetikBasildi()) {
//        functionGunControlTriggerPressed();
//    } else {
//        functionGunControlTriggerReleased();
//    }
//}
