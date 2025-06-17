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

typedef struct {
	registers _400;
	registers _401;
	registers _504;
} ID;

typedef struct
{
	ID ID;

	// related with gun
	bool gunType_1;
	bool gunType_2;
	bool gunType_3;
	bool gunType_4;

	struct
	{
		bool hareketAnahtari;
		bool atisEmniyetAnahtari;
		bool kurmaAnahtari;
		bool savasModuAnahtari;

		bool SMGAYoksay;
	}KKU;

	struct
	{
		union {
		    struct {
		    	uint8_t gunMK19 	: 1;
		        uint8_t gunMAKS40 	: 1;
		        uint8_t gun556 		: 1;
		        uint8_t gun762 		: 1;
		        uint8_t bit4 		: 1;
		        uint8_t bit5 		: 1;
		        uint8_t bit6 		: 1;
		        uint8_t bit7 		: 1;
		    } ;
		    uint8_t value;
		} gunMode;

		uint8_t fireMode;
		uint8_t solenoidActiveTime;
		uint8_t solenoidPassiveTime;
		uint8_t cockingHandleArmedDistance;
		uint8_t cockingHandleSafeDistance;
		bool fireBlockedArea;
	}AKB;

	struct
	{
		uint8_t byte_0;
		uint8_t byte_1;
		uint8_t byte_2;
		uint8_t byte_3;
		uint8_t byte_4;
		uint8_t byte_5;
		uint8_t byte_6;
		uint8_t byte_7;

		struct
		{
			uint32_t solenoidCurrent;
			uint32_t cockingHandleCurrent;
			uint32_t herculeCurrent;
			uint32_t KKUCurrent;
			uint32_t AKBCurrent;
			uint32_t GDBCurrent;
			uint32_t EOSCurrent;
			uint32_t batteryVoltage;
		}REG555;

	}sendPackage;

	struct
	{
		uint8_t GDB_Byte_0;
		uint8_t GDB_Byte_1;
		uint8_t GDB_Byte_2;
		uint8_t GDB_Byte_3;
		uint8_t GDB_Byte_4;
		uint8_t GDB_Byte_5;
		uint8_t GDB_Byte_6;
		uint8_t GDB_Byte_7;
	}errorPackage;

}canMessages;

typedef struct
{
	bool fireBlockedArea;
	union {
	    struct {
	    	uint8_t gunMK19 	: 1;
	        uint8_t gunMAKS40 	: 1;
	        uint8_t gun556 		: 1;
	        uint8_t gun762 		: 1;
	        uint8_t bit4 		: 1;
	        uint8_t bit5 		: 1;
	        uint8_t bit6 		: 1;
	        uint8_t bit7 		: 1;
	    } ;
	    uint8_t value;
	} mode;

	struct
	{
		uint8_t armedDistance;
		uint8_t safeDistance;
		int32_t encoderCounter;
		bool encoderRotation;								// 1: FORWARD 0:BACKWARD
		uint8_t motorState;
		bool armed;
		bool safe;
		bool xxx;
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
		uint8_t solenoidActiveTime;
		uint8_t solenoidPassiveTime;

	}configurations;

}gun;





typedef struct
{
	bool fireOrder;
	bool fireSafety;
	bool systemOnOff;
	bool reserved_1;
	bool reserved_2;
	bool reserved_3;
	bool reserved_4;
	bool reserved_5;
}PIO;

typedef struct
{
	float solenoidCurrent;
	float cockingHandleCurrent;
	float servoCurrent;
	float KKUCurrent;
	float AKBCurrent;
	float GDBCurrent;
	float EOSCurrent;

	float batteryVoltage;
}powerManagement;

typedef struct {
    uint16_t hadc1Buffer[2]; // 1: EOS CURRENT
    						 // 2: KKU CURRENT

    uint16_t hadc2Buffer[2]; // 1: AKB CURRENT
    						 // 2: SERVO CURRENT

    uint16_t hadc3Buffer[4]; // 1: COCKING HANDLE CURRENT
    						 // 2: MAIN POWER CURRENT
    						 // 3: SOLENOID CURRENT
    						 // 4: MAIN POWER VOLTAGE
} analogDigitalConverter;

typedef struct
{
	bool switches_smga;
	bool switches_2;
	bool switches_4;
	bool switches_5;
	bool switches_6;
	bool switches_7;
	bool switches_fire_feedback;
	bool switches_safety_feedback;

	bool switches_cocking_handle_home;
	bool reserved_1;
	bool reserved_2;
	bool reserved_3;
	bool reserved_4;
	bool reserved_5;
	bool reserved_6;
	bool reserved_7;

}switches;

typedef struct
{
	bool errorSolenoidCurrent;
	bool errorCockingHandleCurrent;
	bool errorHerculeCurrent;
	bool errorKKUCurrent;
	bool errorAKBCurrent;
	bool errorGDBCurrent;
	bool errorEOSCurrent;
	bool errorBatteryVoltage;

	bool reserved_1;
	bool reserved_2;
	bool reserved_3;
	bool reserved_4;
	bool reserved_5;
	bool reserved_6;
	bool reserved_7;
	bool reserved_8;
}CIT;

//typedef struct
//{
//	bool gunMK19;
//	bool gunMAKS40;
//	bool gun556;
//	bool gun762;
//
//}gunMode;

typedef struct
{
	gun	gun;
	CIT CIT;
	switches switches;
	powerManagement powerManagement;
	analogDigitalConverter analogDigitalConverter;
	canMessages canMessages;

	PIO PIO;
}pandoraStructer;

#endif /* DEFINITIONS_H_ */
