/*
 * functions.c
 *
 *  Created on: Jan 8, 2025
 *      Author: ADMIN
 */
#include "functions.h"
#include "peripherals.h"
#include "definitions.h"
#include "cocking_handle_maingun.h"
#include "flash.h"

extern pandoraStructer pandora;

void functionCommandsCheck(void)
{
    if (pandora.canMessages.AKB.commandHERCULEPowerOnOff != pandora.canMessages.AKB.previous.commandHERCULEPowerOnOff)   // sadece değişim olduğunda girer
    {
        if (pandora.canMessages.AKB.commandHERCULEPowerOnOff == 1)
        {
            UNIT_CONTROL(SERVO_POWER,ON);
            pandora.states.HERCULEPowerOnOff = true;
        }
        else
        {
        	UNIT_CONTROL(SERVO_POWER,OFF);
        	pandora.states.HERCULEPowerOnOff = false;
        }

        pandora.canMessages.AKB.previous.commandHERCULEPowerOnOff = pandora.canMessages.AKB.commandHERCULEPowerOnOff;
    }

    if (pandora.canMessages.AKB.commandEOSPowerOnOff != pandora.canMessages.AKB.previous.commandEOSPowerOnOff)   // sadece değişim olduğunda girer
    {
        if (pandora.canMessages.AKB.commandEOSPowerOnOff == 1)
        {
            UNIT_CONTROL(EOS_POWER,ON);
            pandora.states.EOSPowerOnOff = true;
        }
        else
        {
        	UNIT_CONTROL(EOS_POWER,OFF);
        	pandora.states.EOSPowerOnOff = false;
        }

        pandora.canMessages.AKB.previous.commandEOSPowerOnOff = pandora.canMessages.AKB.commandEOSPowerOnOff;
    }

    if (pandora.canMessages.AKB.commandKKBPowerOnOff != pandora.canMessages.AKB.previous.commandKKBPowerOnOff)   // sadece değişim olduğunda girer
    {
        if (pandora.canMessages.AKB.commandKKBPowerOnOff == 1)
        {
            UNIT_CONTROL(KKU_POWER,ON);
            pandora.states.KKBPowerOnOff = true;
        }
        else
        {
        	UNIT_CONTROL(KKU_POWER,OFF);
        	pandora.states.KKBPowerOnOff = false;
        }

        pandora.canMessages.AKB.previous.commandKKBPowerOnOff = pandora.canMessages.AKB.commandKKBPowerOnOff;
    }

    if (pandora.canMessages.AKB.commandAKBPowerOnOff != pandora.canMessages.AKB.previous.commandAKBPowerOnOff)   // sadece değişim olduğunda girer
    {
        if (pandora.canMessages.AKB.commandAKBPowerOnOff == 1)
        {
            UNIT_CONTROL(AKB_POWER,ON);
            pandora.states.AKBPowerOnOff = true;
        }
        else
        {
        	UNIT_CONTROL(AKB_POWER,OFF);
        	pandora.states.AKBPowerOnOff = false;
        }

        pandora.canMessages.AKB.previous.commandAKBPowerOnOff = pandora.canMessages.AKB.commandAKBPowerOnOff;
    }

    if (pandora.canMessages.AKB.commandSOLPowerOnOff != pandora.canMessages.AKB.previous.commandSOLPowerOnOff)   // sadece değişim olduğunda girer
    {
        if (pandora.canMessages.AKB.commandSOLPowerOnOff == 1)
        {
            UNIT_CONTROL(SOLENOID_POWER,ON);
            pandora.states.SOLPowerOnOff = true;
        }
        else
        {
        	UNIT_CONTROL(SOLENOID_POWER,OFF);
        	pandora.states.SOLPowerOnOff = false;
        }

        pandora.canMessages.AKB.previous.commandSOLPowerOnOff = pandora.canMessages.AKB.commandSOLPowerOnOff;
    }

    if (pandora.canMessages.AKB.commandCHPowerOnOff != pandora.canMessages.AKB.previous.commandCHPowerOnOff)   // sadece değişim olduğunda girer
    {
        if (pandora.canMessages.AKB.commandCHPowerOnOff == 1)
        {
            UNIT_CONTROL(COCKING_HANDLE_POWER,ON);
            pandora.states.CHPowerOnOff = true;
        }
        else
        {
        	UNIT_CONTROL(COCKING_HANDLE_POWER,OFF);
        	pandora.states.CHPowerOnOff = false;
        }

        pandora.canMessages.AKB.previous.commandCHPowerOnOff = pandora.canMessages.AKB.commandCHPowerOnOff;
    }

    if (pandora.canMessages.AKB.commandCockingHandleHome != pandora.canMessages.AKB.previous.commandCockingHandleHome)   // sadece değişim olduğunda girer
    {
        if (pandora.canMessages.AKB.commandCockingHandleHome == 1)
        {
            functionCockingHandleGoHome();
        }
        else
        {
        	//NONE
        }

        pandora.canMessages.AKB.previous.commandCockingHandleHome = pandora.canMessages.AKB.commandCockingHandleHome;
    }

    if (pandora.canMessages.AKB.commandCockingHandleSafe != pandora.canMessages.AKB.previous.commandCockingHandleSafe)   // sadece değişim olduğunda girer
    {
        if (pandora.canMessages.AKB.commandCockingHandleSafe == 1)
        {
            functionCockingHandleGoSafe();
        }
        else
        {
        	//NONE
        }

        pandora.canMessages.AKB.previous.commandCockingHandleSafe = pandora.canMessages.AKB.commandCockingHandleSafe;
    }

    if (pandora.canMessages.AKB.commandCockingHandleArm != pandora.canMessages.AKB.previous.commandCockingHandleArm)   // sadece değişim olduğunda girer
    {
        if (pandora.canMessages.AKB.commandCockingHandleArm == 1)
        {
            functionCockingHandleGoArm();
        }
        else
        {
        	//NONE
        }

        pandora.canMessages.AKB.previous.commandCockingHandleArm = pandora.canMessages.AKB.commandCockingHandleArm;
    }

    if (pandora.canMessages.AKB.commandEmergencyStop != pandora.canMessages.AKB.previous.commandEmergencyStop)   // sadece değişim olduğunda girer
    {
        if (pandora.canMessages.AKB.commandEmergencyStop == 1)
        {
        	UNIT_CONTROL(SERVO_POWER,OFF);
        	UNIT_CONTROL(EOS_POWER,OFF);
        	UNIT_CONTROL(KKU_POWER,OFF);
        	UNIT_CONTROL(AKB_POWER,OFF);
        	UNIT_CONTROL(SOLENOID_POWER,OFF);
        	UNIT_CONTROL(COCKING_HANDLE_POWER,OFF);

        	pandora.states.HERCULEPowerOnOff 	= false;
        	pandora.states.EOSPowerOnOff 		= false;
        	pandora.states.KKBPowerOnOff 		= false;
        	pandora.states.AKBPowerOnOff 		= false;
        	pandora.states.SOLPowerOnOff 		= false;
        	pandora.states.CHPowerOnOff 		= false;
        }
        else
        {
        	//NONE
        }

        pandora.canMessages.AKB.previous.commandEmergencyStop = pandora.canMessages.AKB.commandEmergencyStop;
    }

    if (pandora.canMessages.AKB.commandWarMode != pandora.canMessages.AKB.previous.commandWarMode)   // sadece değişim olduğunda girer
    {
        if (pandora.canMessages.AKB.commandWarMode == 1)
        {
        	// DO SOMETHING
        }
        else
        {
        	//NONE
        }

        pandora.canMessages.AKB.previous.commandWarMode = pandora.canMessages.AKB.commandWarMode;
    }
}
