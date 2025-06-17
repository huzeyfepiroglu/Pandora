/*
 * functions.c
 *
 *  Created on: Jan 8, 2025
 *      Author: ADMIN
 */
#include "functions.h"
#include "peripherals.h"
#include "definitions.h"

extern pandoraStructer pandora;

void function_solenoid(uint8_t *data)
{
	//UNIT_CONTROL(LED,ON);
	uint8_t value = false;//FEEDBACK_READ(BUTTON);

	if(value == HIGH)
	{

	}
}

void function_readSwitches (void)
{
//	pandora.switches.smga 		= SWITCH_INT_READ(SMGA);
//	pandora.switches.gunType_1 	= SWITCH_INT_READ(GUN_TYPE_1);
//	pandora.switches.gunType_2 	= SWITCH_INT_READ(GUN_TYPE_2);
//	pandora.switches.gunType_3 	= SWITCH_INT_READ(GUN_TYPE_3);
//	pandora.switches.gunType_4 	= SWITCH_INT_READ(GUN_TYPE_4);
//
//	pandora.switches.switch_1 	= SWITCH_INT_READ(SWITCH_1);
//	pandora.switches.switch_2 	= SWITCH_INT_READ(SWITCH_2);
//	pandora.switches.switch_3 	= SWITCH_INT_READ(SWITCH_3);
//	pandora.switches.switch_4 	= SWITCH_INT_READ(SWITCH_4);
//	pandora.switches.switch_5 	= SWITCH_INT_READ(SWITCH_5);
}

void function_readPIOs (void)
{
//	pandora.PIO.fireOrder 		= SWITCH_INT_READ(FIRE_ORDER);
//	pandora.PIO.fireSafety 		= SWITCH_INT_READ(FIRE_SAFETY);
//	pandora.PIO.systemOnOff		= SWITCH_INT_READ(SYSTEM_ON_OFF);
}


