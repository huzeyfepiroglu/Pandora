/*
 * error.c
 *
 *  Created on: Jan 23, 2025
 *      Author: ADMIN
 */
#include "error.h"
#include "definitions.h"

extern pandoraStructer pandora;

void functionHighCurrentErrorCheck (void)
{
	pandora.error.solenoidCurrentHigh		= (pandora.powerManagement.SCurrent		 	> AMPER_5) 	? true : false;
	pandora.error.cockingHandleCurrentHigh	= (pandora.powerManagement.CHCurrent		> AMPER_5) 	? true : false;
	pandora.error.herculeCurrentHigh 		= (pandora.powerManagement.HERCULECurrent 	> AMPER_5) 	? true : false;
	pandora.error.kkuCurrentHigh 			= (pandora.powerManagement.KKUCurrent 		> AMPER_5) 	? true : false;
	pandora.error.akbCurrentHigh 			= (pandora.powerManagement.AKBCurrent 		> AMPER_5) 	? true : false;
	pandora.error.gdbCurrentHigh 			= (pandora.powerManagement.GDBCurrent 		> AMPER_5) 	? true : false;
	pandora.error.eosCurrentHigh 			= (pandora.powerManagement.EOSCurrent 		> AMPER_5) 	? true : false;
	pandora.error.gdbVoltageHigh 			= (pandora.powerManagement.BATVoltage 		> VOLT_28) 	? true : false;
	pandora.error.gdbVoltageLow	 			= (pandora.powerManagement.BATVoltage 		< VOLT_22) 	? true : false;
}

void functionMosfetErrorCheck (void)
{
	if((pandora.switches.switches_fire_order 	== true)	&&
	   (pandora.states.firing 					== true )   &&
	   (pandora.powerManagement.SCurrent 		< AMPER_1)  &&
	   (pandora.error.system 					== false))
	{
		pandora.error.solenoidCurrentLow = true; // mosfet hatası. LOOP kontrolü var olduğu için atış durumunda akım çekmiyorsa mosfet arızalıdır.
	}

	if((pandora.switches.switches_cocking_handle_order 	== true    )	&&
	   (pandora.gun.cockingHandle.brakeState 			== OFF     )	&&
	   (pandora.gun.cockingHandle.motorState 			!= IDLE    )	&&
	   (pandora.powerManagement.CHCurrent				<  AMPER_1 ) 	&&
	   (pandora.error.system 							== false   ))
	{
		pandora.error.cockingHandleCurrentLow = true; // mosfet hatası. LOOP kontrolü var olduğu için atış durumunda akım çekmiyorsa mosfet arızalıdır.
	}

	if((pandora.configurations.onOffAKB				 	== true    )	&&
	   (pandora.powerManagement.AKBCurrent				<  AMPER_1 ) 	&&
	   (pandora.error.system 							== false   ))
	{
		pandora.error.akbCurrentLow = true;
	}

	if((pandora.configurations.onOffKKU				 	== true    )	&&
	   (pandora.powerManagement.KKUCurrent				<  AMPER_1 ) 	&&
	   (pandora.error.system 							== false   ))
	{
		pandora.error.kkuCurrentLow = true;
	}

	if((pandora.configurations.onOffEOS				 	== true    )	&&
	   (pandora.powerManagement.EOSCurrent				<  AMPER_1 ) 	&&
	   (pandora.error.system 							== false   ))
	{
		pandora.error.eosCurrentLow = true;
	}

	if((pandora.configurations.onOffHERCULE				== true    )	&&
	   (pandora.powerManagement.HERCULECurrent			<  AMPER_1 ) 	&&
	   (pandora.error.system 							== false   ))
	{
		pandora.error.herculeCurrentLow = true;
	}
}
