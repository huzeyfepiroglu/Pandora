/*
 * error.c
 *
 *  Created on: Jan 23, 2025
 *      Author: ADMIN
 */
#include "error.h"
#include "definitions.h"

extern pandoraStructer pandora;

void functionErrorCheck (void)
{
	/************************SOLENOID_BEGIN**************************/
	if(pandora.powerManagement.solenoidCurrent > AMPER_5)
	{
		pandora.error.solenoidCurrentHigh = true;
	}
	else
	{
		pandora.error.solenoidCurrentHigh = false;
	}
	/************************SOLENOID_END****************************/

	/*********************COCKING_HANDLE_BEGIN***********************/
	if(pandora.powerManagement.cockingHandleCurrent > AMPER_5)
	{
		pandora.error.cockingHandleCurrentHigh = true;
	}
	else
	{
		pandora.error.cockingHandleCurrentHigh = false;
	}
	/*********************COCKING_HANDLE_END*************************/

	/************************HERCULE_BEGIN***************************/
	if(pandora.powerManagement.servoCurrent > AMPER_5)
	{
		pandora.error.herculeCurrentHigh = true;
	}
	else
	{
		pandora.error.herculeCurrentHigh = false;
	}
	/************************HERCULE_END*****************************/

	/**************************KKU_BEGIN*****************************/
	if(pandora.powerManagement.KKUCurrent > AMPER_5)
	{
		pandora.error.kkuCurrentHigh = true;
	}
	else
	{
		pandora.error.kkuCurrentHigh = false;
	}
	/**************************KKU_END*******************************/

	/**************************AKB_BEGIN*****************************/
	if(pandora.powerManagement.AKBCurrent > AMPER_5)
	{
		pandora.error.akbCurrentHigh = true;
	}
	else
	{
		pandora.error.akbCurrentHigh = false;
	}
	/**************************AKB_END*******************************/

	/**************************GDB_BEGIN*****************************/
	if(pandora.powerManagement.GDBCurrent > AMPER_5)
	{
		pandora.error.gdbCurrentHigh = true;
	}
	else
	{
		pandora.error.gdbCurrentHigh = false;
	}
	/**************************GDB_END*******************************/

	/**************************EOS_BEGIN*****************************/
	if(pandora.powerManagement.EOSCurrent > AMPER_5)
	{
		pandora.error.eosCurrentHigh = true;
	}
	else
	{
		pandora.error.eosCurrentHigh = false;
	}
	/**************************EOS_END*******************************/

	/************************BATTERY_BEGIN***************************/
	if(pandora.powerManagement.batteryVoltage < VOLTAGE_22)
	{
		pandora.error.gdbVoltageLow = true;
	}
	else
	{
		pandora.error.gdbVoltageLow = false;
	}
	/************************BATTERY_END***************************/
}
