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
		pandora.CIT.errorSolenoidCurrent = true;
	}
	else
	{
		pandora.CIT.errorSolenoidCurrent = false;
	}
	/************************SOLENOID_END****************************/

	/*********************COCKING_HANDLE_BEGIN***********************/
	if(pandora.powerManagement.cockingHandleCurrent > AMPER_5)
	{
		pandora.CIT.errorCockingHandleCurrent = true;
	}
	else
	{
		pandora.CIT.errorCockingHandleCurrent = false;
	}
	/*********************COCKING_HANDLE_END*************************/

	/************************HERCULE_BEGIN***************************/
	if(pandora.powerManagement.servoCurrent > AMPER_5)
	{
		pandora.CIT.errorHerculeCurrent = true;
	}
	else
	{
		pandora.CIT.errorHerculeCurrent = false;
	}
	/************************HERCULE_END*****************************/

	/**************************KKU_BEGIN*****************************/
	if(pandora.powerManagement.KKUCurrent > AMPER_5)
	{
		pandora.CIT.errorKKUCurrent = true;
	}
	else
	{
		pandora.CIT.errorKKUCurrent = false;
	}
	/**************************KKU_END*******************************/

	/**************************AKB_BEGIN*****************************/
	if(pandora.powerManagement.AKBCurrent > AMPER_5)
	{
		pandora.CIT.errorAKBCurrent = true;
	}
	else
	{
		pandora.CIT.errorAKBCurrent = false;
	}
	/**************************AKB_END*******************************/

	/**************************GDB_BEGIN*****************************/
	if(pandora.powerManagement.GDBCurrent > AMPER_5)
	{
		pandora.CIT.errorGDBCurrent = true;
	}
	else
	{
		pandora.CIT.errorGDBCurrent = false;
	}
	/**************************GDB_END*******************************/

	/**************************EOS_BEGIN*****************************/
	if(pandora.powerManagement.EOSCurrent > AMPER_5)
	{
		pandora.CIT.errorEOSCurrent = true;
	}
	else
	{
		pandora.CIT.errorEOSCurrent = false;
	}
	/**************************EOS_END*******************************/

	/************************BATTERY_BEGIN***************************/
	if(pandora.powerManagement.batteryVoltage < VOLTAGE_22)
	{
		pandora.CIT.errorBatteryVoltage = true;
	}
	else
	{
		pandora.CIT.errorBatteryVoltage = false;
	}
	/************************BATTERY_END***************************/
}
