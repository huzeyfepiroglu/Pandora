/*
 * power_management.c
 *
 *  Created on: May 16, 2025
 *      Author: ADMIN
 */

/*
 * EOS: ELECTRO OPTIC SUIT
 * KKU: KULLANICI KONTROL UNITESI
 * AKB: AKILLI KONTROL BIRIMI
 * HERCULE: SERVO SURUCU
 * KKM: KURMA KOLU MEKANIZMASI
 * SLN: SOLENOID
 *
 */

#include "power_management.h"
#include "peripherals.h"
#include "definitions.h"

extern pandoraStructer pandora;

void funcPCIUnitSupply(void)	/*Power Control Interface*/
{
	UNIT_CONTROL(EOS_POWER,ON);
	UNIT_CONTROL(KKU_POWER,ON);
	UNIT_CONTROL(AKB_POWER,ON);
	UNIT_CONTROL(SERVO_POWER,ON);
}

void funcVoltageMeasure(uint8_t *data)
{
	pandora.powerManagement.batteryVoltage = pandora.analogDigitalConverter.hadc3Buffer[3];
}
/*
 * AKB (OPTIMUS):
 * Kesme Akımı 5A = 0.6V
 * 5A = 186/1024 ADC
 * 0.6V = 0.5mA*1.2k
 *
 * KKU (ETNA)
 * Kesme Akımı 8A = 0.8V
 * 8A = 248/1024 ADC
 * 0.6V = 0.5mA*1.2k
 */
void funcCurrentMeasure(uint8_t *data)
{
	pandora.powerManagement.solenoidCurrent 		= pandora.analogDigitalConverter.hadc3Buffer[2];
	pandora.powerManagement.cockingHandleCurrent 	= pandora.analogDigitalConverter.hadc3Buffer[0];
	pandora.powerManagement.servoCurrent 			= pandora.analogDigitalConverter.hadc2Buffer[1];
	pandora.powerManagement.AKBCurrent 				= pandora.analogDigitalConverter.hadc2Buffer[0];
	pandora.powerManagement.EOSCurrent 				= pandora.analogDigitalConverter.hadc1Buffer[0];
	pandora.powerManagement.GDBCurrent 				= pandora.analogDigitalConverter.hadc3Buffer[0];
	pandora.powerManagement.KKUCurrent 				= pandora.analogDigitalConverter.hadc1Buffer[1];
}

