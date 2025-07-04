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

/*
 * GİRİŞ GERİLİMİ
 * 16 BIT ADC												Çözünürlük
 * 136k//4.7k												Gerilim Bölücü
 * 28 Volt için 0.935 Volt #28/0.935#=29.94652 				Katsayı
 * #3.3/65535# = 0.000050354 								1 Bite Gelen Volt Değeri
 * VOLTAGE = ((ADC_VALUE * 3.3)/65535)*(28/0.935)			Formül
 */
void functionVoltageMeasure(void)
{
	pandora.powerManagement.batteryVoltage = (((pandora.analogDigitalConverter.hadc3Buffer[3])*3.3)/65535)*(28/0.935);
}

/*
 * AKB CURRENT
 * 16 BIT ADC												Çözünürlük
 * Kesme Akımı 5A = 0.6V									Kesme Akımındaki Gerilim Değeri
 * 5 AMPER için 0.6 VOLT #5/0.6#=8.33333	 				Katsayı
 * #3.3/65535# = 0.000050354 								1 Bite Gelen Volt Değeri
 * CURRENT = ((ADC_VALUE * 3.3)/65535)*(5/0.6)				Formül
 */

/*
 * KKU CURRENT
 * 16 BIT ADC												Çözünürlük
 * Kesme Akımı 8A = 0.8V									Kesme Akımındaki Gerilim Değeri
 * 5 AMPER için 0.8 VOLT #5/0.8#=6.25	 					Katsayı
 * #3.3/65535# = 0.000050354 								1 Bite Gelen Volt Değeri
 * CURRENT = ((ADC_VALUE * 3.3)/65535)*(5/0.8)				Formül
 */


void functionCurrentMeasure(void)
{
	pandora.powerManagement.solenoidCurrent 		= ((pandora.analogDigitalConverter.hadc3Buffer[2] * 3.3)/65535)*(5/0.8); // #DÜZENLE KESME DEĞERLERİNİ
	pandora.powerManagement.cockingHandleCurrent 	= ((pandora.analogDigitalConverter.hadc3Buffer[0] * 3.3)/65535)*(5/0.8);
	pandora.powerManagement.servoCurrent 			= ((pandora.analogDigitalConverter.hadc2Buffer[1] * 3.3)/65535)*(5/0.8);
	pandora.powerManagement.AKBCurrent 				= ((pandora.analogDigitalConverter.hadc2Buffer[0] * 3.3)/65535)*(5/0.8);
	pandora.powerManagement.EOSCurrent 				= ((pandora.analogDigitalConverter.hadc1Buffer[0] * 3.3)/65535)*(5/0.8);
	pandora.powerManagement.GDBCurrent 				= ((pandora.analogDigitalConverter.hadc3Buffer[0] * 3.3)/65535)*(5/0.8);
	pandora.powerManagement.KKUCurrent 				= ((pandora.analogDigitalConverter.hadc1Buffer[1] * 3.3)/65535)*(5/0.8);
}

