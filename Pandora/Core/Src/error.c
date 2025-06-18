/*
 * error.c
 *
 *  Created on: Jan 23, 2025
 *      Author: ADMIN
 */
#include "error.h"
#include "definitions.h"

extern pandoraStructer pandora;

void function_errorCheck (void)
{
	/************************SOLENOID_BEGIN**************************/
	if(pandora.powerManagement.solenoidCurrent > AMPER_5)
	{
		pandora.powerManagement.errorSolenoidCurrent = true;
	}
	else
	{
		pandora.powerManagement.errorSolenoidCurrent = false;
	}
	/************************SOLENOID_END****************************/

	/*********************COCKING_HANDLE_BEGIN***********************/
	if(pandora.powerManagement.cockingHandleCurrent > AMPER_5)
	{
		pandora.powerManagement.errorCockingHandleCurrent = true;
	}
	else
	{
		pandora.powerManagement.errorCockingHandleCurrent = false;
	}
	/*********************COCKING_HANDLE_END*************************/

	/************************HERCULE_BEGIN***************************/
	if(pandora.powerManagement.servoCurrent > AMPER_5)
	{
		pandora.powerManagement.errorHerculeCurrent = true;
	}
	else
	{
		pandora.powerManagement.errorHerculeCurrent = false;
	}
	/************************HERCULE_END*****************************/

	/**************************KKU_BEGIN*****************************/
	if(pandora.powerManagement.KKUCurrent > AMPER_5)
	{
		pandora.powerManagement.errorKKUCurrent = true;
	}
	else
	{
		pandora.powerManagement.errorKKUCurrent = false;
	}
	/**************************KKU_END*******************************/

	/**************************AKB_BEGIN*****************************/
	if(pandora.powerManagement.AKBCurrent > AMPER_5)
	{
		pandora.powerManagement.errorAKBCurrent = true;
	}
	else
	{
		pandora.powerManagement.errorAKBCurrent = false;
	}
	/**************************AKB_END*******************************/

	/**************************GDB_BEGIN*****************************/
	if(pandora.powerManagement.GDBCurrent > AMPER_5)
	{
		pandora.powerManagement.errorGDBCurrent = true;
	}
	else
	{
		pandora.powerManagement.errorGDBCurrent = false;
	}
	/**************************GDB_END*******************************/

	/**************************EOS_BEGIN*****************************/
	if(pandora.powerManagement.EOSCurrent > AMPER_5)
	{
		pandora.powerManagement.errorEOSCurrent = true;
	}
	else
	{
		pandora.powerManagement.errorEOSCurrent = false;
	}
	/**************************EOS_END*******************************/

	/************************BATTERY_BEGIN***************************/
	if(pandora.powerManagement.batteryVoltage < VOLTAGE_22)
	{
		pandora.powerManagement.errorBatteryVoltage = true;
	}
	else
	{
		pandora.powerManagement.errorBatteryVoltage = false;
	}
	/************************BATTERY_END***************************/
}
