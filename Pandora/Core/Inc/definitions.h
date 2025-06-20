/*
 * definitions.h
 *
 *  Created on: Jan 23, 2025
 *      Author: ADMIN
 */

#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#include "main.h"
#include "stdbool.h"

#define ID_KKU		 	 0x700
#define ID_AKB			 0x500
#define ID_EOS			 0x300
#define ID_HERCULE		 0x100

#define KIOSK_JOYSTICKS		 0x1
#define KIOSK_BUTTONS		 0x2
#define KIOSK_SWITCHES		 0x3

#define HOME_POSITION		0
#define SAFE_POSITION		500
#define ARM_POSITION		1000

#define AMPER_5		5
#define AMPER_10	10
#define AMPER_15	15
#define AMPER_20	20
#define AMPER_25	25

#define VOLTAGE_22	22

//	FOR DEBOUNCE BEGIN
#define DEBOUNCE_DELAY_MS 1





//	FOR DEBOUNCE END

// Atış Modları
typedef enum {
    FIRE_MODE_SINGLE,
    FIRE_MODE_FAST_AUTO,
    FIRE_MODE_FAST_BURST_3,
    FIRE_MODE_FAST_BURST_5,
    FIRE_MODE_SLOW_AUTO,
    FIRE_MODE_SLOW_BURST_3,
    FIRE_MODE_SLOW_BURST_5
} FireMode_t;

typedef union {
    struct {
    	uint8_t bit0 : 1;
        uint8_t bit1 : 1;
        uint8_t bit2 : 1;
        uint8_t bit3 : 1;
        uint8_t bit4 : 1;
        uint8_t bit5 : 1;
        uint8_t bit6 : 1;
        uint8_t bit7 : 1;
    } ;
    uint8_t byte;
} byteUnion;

// 3 byte içeren yapı
typedef struct
{
	byteUnion REG1;
	byteUnion REG2;
	byteUnion REG3;
	byteUnion REG4;
	byteUnion REG5;
	byteUnion REG6;
	byteUnion REG7;

} registers;


typedef struct
{
	struct
	{
		/* ID300 BEGIN	COCKING HANDLE*/
		uint8_t cockingHandleArmedDistance;
		uint8_t cockingHandleSafeDistance;
		bool commandCockingHandleSafe;
		bool commandCockingHandleArm;
		bool commandCockingHandleHome;
		bool commandCockingHandleCancel;
		/* ID300 END COCKING HANDLE*/

		/* ID301 BEGIN	SOLENOID*/
		uint8_t fastRpmHighByte;						//OKEY 8 BIT
		uint8_t fastRpmLowByte;							//OKEY 8 BIT
		uint8_t slowRpmHighByte;						//OKEY 8 BIT
		uint8_t slowRpmLowByte;							//OKEY 8 BIT
		uint8_t solenoidTime;							//OKEY 8 BIT
		uint8_t solenoidActiveTime;						//OKEY 8 BIT
		uint8_t solenoidPassiveTime;					//OKEY 8 BIT
		uint8_t commandFireMode;						//OKEY 3 BIT
		bool 	commandGunFire;							//OKEY 1 BIT
		bool 	commandSmgaAllowed;						//OKEY 1 BIT
		bool 	commandCounterSenseCancel;				//OKEY 1 BIT
		/* ID301 END	SOLENOID*/

		/* ID302 BEGIN POWER*/
		bool commandServoOnOff;
		bool commandKKBOnOff;
		bool commandEOSOnOff;
		bool canBusOk;
		/* ID302 END POWER*/

		/* ID303 BEGIN INTERRUPT*/
		bool commandWarMode;
		bool commandEmergencyStop;
		bool fireBlockedArea;
		/* ID303 END INTERRUPT*/

		/*	ID304 BEGIN	GENERAL PURPOSE*/
		uint8_t gunType;								//OKEY
		uint8_t gunID;									//OKEY
		/*	ID304 END GENERAL PURPOSE*/
	}AKB;

	struct
	{
		struct
		{
			// #DÜZENLE GÖNDERİLECEK PAKETLERİ STRUCTLA
			byteUnion byte_0;
			byteUnion byte_1;
			byteUnion byte_2;
			byteUnion byte_3;
			byteUnion byte_4;
			byteUnion byte_5;
			byteUnion byte_6;
			byteUnion byte_7;
		}ID400;

		struct
		{
			// #DÜZENLE GÖNDERİLECEK PAKETLERİ STRUCTLA
			byteUnion byte_0;
			byteUnion byte_1;
			byteUnion byte_2;
			byteUnion byte_3;
			byteUnion byte_4;
			byteUnion byte_5;
			byteUnion byte_6;
			byteUnion byte_7;
		}ID401;

		struct
		{
			// #DÜZENLE GÖNDERİLECEK PAKETLERİ STRUCTLA
			byteUnion byte_0;
			byteUnion byte_1;
			byteUnion byte_2;
			byteUnion byte_3;
			byteUnion byte_4;
			byteUnion byte_5;
			byteUnion byte_6;
			byteUnion byte_7;
		}ID404;

	}sendPackage;


}canMessages;

typedef struct
{
	bool solenoidCurrentLow;
	bool solenoidCurrentHigh;
	bool cockingHandleCurrentLow;
	bool cockingHandleCurrentHigh;
	bool herculeCurrentLow;
	bool herculeCurrentHigh;
	bool akbCurrentLow;
	bool akbCurrentHigh;
	bool kkuCurrentLow;
	bool kkuCurrentHigh;
	bool eosCurrentLow;
	bool eosCurrentHigh;
	bool gdbCurrentLow;
	bool gdbCurrentHigh;
	bool gdbVoltageLow;
	bool gdbVoltageHigh;
}error;

typedef struct
{
	uint8_t fastRpm;
	uint8_t slowRpm;
	uint8_t solenoidTime;
	uint8_t solenoidActiveTime;
	uint8_t solenoidPassiveTime;
	uint8_t fireMode;
}eeprom;

typedef struct
{
	bool fireBlockedArea;
	uint8_t gunID;
	uint8_t gunType;
	uint8_t fireMode;

//	struct {
//	    uint16_t rpm;               // 600 RPM = 100ms
//	    uint16_t pulseTime_ms;      // Solenoid açık süresi
//	    FireMode mode;
//	    uint8_t remainingShots;
//	    uint8_t firing;
//	    GPIO_TypeDef *port;
//	    uint16_t pin;
//	    GunState state;
//	    uint32_t stateStartTime;    // Zaman takip
//	} GunControl;

	struct
	{
		uint8_t armedDistance;
		uint8_t safeDistance;
		int32_t encoderCounter;
		bool encoderRotation;								// 1: FORWARD 0:BACKWARD
		uint8_t motorState;									// OKEY
		bool armed;											// OKEY
		bool safe;											// OKEY
		bool home;											// OKEY
		registers registers;
	}cockingHandle;

	struct
	{
		uint8_t ammoCounter;
		bool tetikBilgisi;

		registers registers;
	}fireSolenoid;

	struct
	{
		uint8_t fastRpm;								//OKEY
		uint8_t slowRpm;								//OKEY
		uint8_t solenoidTime;							//OKEY
		uint8_t solenoidActiveTime;						//OKEY
		uint8_t solenoidPassiveTime;					//OKEY
		uint8_t fireMode;								//OKEY


	}configurations;

}gun;

typedef struct
{
	bool solenoidActive;
	bool triggerHeld;
	bool shuttingDown;
	uint32_t changeTime;
	uint16_t burstCounter;
	uint32_t ammoCounter;
	uint8_t systemMode;
}states;

typedef struct
{
	bool fireSafetySwitch;
	bool cockingHandleSwitch;
	bool movementSwitch;
	bool fireOrderSwitch;
	bool systemOnOffSwitch;				// AÇILIRKEN DONANIMSAL KAPANIRKEN MÜHÜRLEME KAPATILACAK
}PIO;

typedef struct
{
	uint32_t solenoidCurrent;
	uint32_t cockingHandleCurrent;
	uint32_t servoCurrent;
	uint32_t KKUCurrent;
	uint32_t AKBCurrent;
	uint32_t GDBCurrent;
	uint32_t EOSCurrent;
	uint32_t batteryVoltage;

	bool herculeOK;
	bool kkuOK;
	bool akbOK;
	bool eosOK;
	bool gdbOK;
	bool solenoidOK;
	bool cockingHandleOK;
}powerManagement;

typedef struct {
	uint32_t hadc1Buffer[2]; // 1: EOS CURRENT
    						 // 2: KKU CURRENT

	uint32_t hadc2Buffer[2]; // 1: AKB CURRENT
    						 // 2: SERVO CURRENT

	uint32_t hadc3Buffer[4]; // 1: COCKING HANDLE CURRENT
    						 // 2: MAIN POWER CURRENT
    						 // 3: SOLENOID CURRENT
    						 // 4: MAIN POWER VOLTAGE
} analogDigitalConverter;

typedef struct
{
	bool switches_safety;
	bool switches_cocking_handle_order;
	bool switches_movement_allowed;
	bool switches_fire_order;
	bool switches_system_on_off;
	bool switches_smga;
	bool switches_cocking_handle_home;
	bool switches_crew_1;
	bool switches_crew_2;

}switches;

typedef struct
{
	gun	gun;
	error error;
	eeprom eeprom;
	states states;
	switches switches;
	canMessages canMessages;
	powerManagement powerManagement;
	analogDigitalConverter analogDigitalConverter;
	PIO PIO;
}pandoraStructer;

extern pandoraStructer pandora;
#endif /* DEFINITIONS_H_ */
