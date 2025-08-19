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



#define IDLE	  2
#define FORWARD   1
#define BACKWARD  0

#define HIGH 1
#define LOW  0
#define ON   1
#define OFF  0

#define COMMAND_ID 				0xAA
#define COMMAND_HEADER 			0xA1
#define REQUEST_ID 				0xBB
#define REQUEST_HEADER			0xB1
#define ACK_ID					0xCC
#define ACK_HEADER				0xC1
#define COMMAND_COCKING_HANDLE_ARMED_DISTANCE  0x01
#define COMMAND_COCKING_HANDLE_SAFE_DISTANCE   0x02
#define COMMAND_COCKING_HANDLE_SAFE            0x03
#define COMMAND_COCKING_HANDLE_ARM             0x04
#define COMMAND_COCKING_HANDLE_HOME            0x05
#define COMMAND_SOLENOID_FAST_RPM              0x06
#define COMMAND_SOLENOID_SLOW_RPM              0x07
#define COMMAND_SOLENOID_TIME                  0x08
#define COMMAND_SOLENOID_ACTIVE_TIME           0x09
#define COMMAND_SOLENOID_PASSIVE_TIME          0x0A
#define COMMAND_SOLENOID_FIRE_MODE             0x0B
#define COMMAND_FIRE                           0x0C
#define COMMAND_OVERRIDE_SMGA                  0x0D
#define COMMAND_OVERRIDE_FIRE_BLOCKED          0x0E
#define COMMAND_OVERRIDE_WAR_MODE              0x0F
#define COMMAND_OVERRIDE_EMERGENCY_STOP        0x10
#define COMMAND_ON_OFF_HERCULE                 0x11
#define COMMAND_ON_OFF_KKU                     0x12
#define COMMAND_ON_OFF_EOS                     0x13
#define COMMAND_SET_SYSTEM_DEFAULT_DATA        0x14
#define COMMAND_SYSTEM_RESET                   0x15
#define COMMAND_SAVE_TO_FLASH                  0x16

#define REQUEST_FUNC_1					       0x80
#define REQUEST_FUNC_2					       0x81
#define REQUEST_FUNC_3					       0x82






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

typedef union
{
	byteUnion byte_0;
	byteUnion byte_1;
	byteUnion byte_2;
	byteUnion byte_3;
	byteUnion byte_4;
	byteUnion byte_5;
	byteUnion byte_6;
	byteUnion byte_7;
} ID;

typedef struct
{
	struct
	{
		uint8_t commandFireMode;						//OKEY 3 BIT
														//OKEY 1 BIT
														//OKEY 1 BIT
														//OKEY 1 BIT
														//OKEY 1 BIT
														//OKEY 1 BIT
		/***************************************************************/
		bool commandFireBlockedAreaOveride;				//OKEY 1 BIT
		bool commandSmgaOveride;						//OKEY 1 BIT
		bool commandGunFireOveride;						//OKEY 1 BIT
		bool commandWarMode;							//OKEY 1 BIT
		bool commandEmergencyStop;						//OKEY 1 BIT
														//OKEY 1 BIT
														//OKEY 1 BIT
														//OKEY 1 BIT
		/***************************************************************/
		bool commandHERCULEPowerOnOff;					//OKEY 1 BIT
		bool commandEOSPowerOnOff;						//OKEY 1 BIT
		bool commandKKBPowerOnOff;						//OKEY 1 BIT
		bool commandAKBPowerOnOff;						//OKEY 1 BIT
		bool commandSOLPowerOnOff;						//OKEY 1 BIT
		bool commandCHPowerOnOff;						//OKEY 1 BIT
														//OKEY 1 BIT
														//OKEY 1 BIT
		/***************************************************************/
		bool commandCockingHandleHome;					//OKEY 1 BIT
		bool commandCockingHandleSafe;					//OKEY 1 BIT
		bool commandCockingHandleArm;					//OKEY 1 BIT
														//OKEY 1 BIT
														//OKEY 1 BIT
														//OKEY 1 BIT
														//OKEY 1 BIT
														//OKEY 1 BIT
		/***************************************************************/
		bool commandFireBlockedArea;					//OKEY 1 BIT
		bool commandGunFire;							//OKEY 1 BIT
		//bool commandCockingHandleArm;					//OKEY 1 BIT
														//OKEY 1 BIT
														//OKEY 1 BIT
														//OKEY 1 BIT
														//OKEY 1 BIT
														//OKEY 1 BIT
		/***************************************************************/
		uint8_t gunType;								//OKEY 4 BIT
		uint8_t gunID;									//OKEY 4 BIT
		/***************************************************************/
		union
		{
		    struct
			{
				uint8_t solenoidFastRpmHighByte;						//OKEY 8 BIT
				uint8_t solenoidFastRpmLowByte;							//OKEY 8 BIT
		    };
		    uint16_t solenoidFastRpm;
		};
		union
		{
		    struct
			{
				uint8_t solenoidSlowRpmHighByte;						//OKEY 8 BIT
				uint8_t solenoidSlowRpmLowByte;							//OKEY 8 BIT
		    };
		    uint16_t solenoidSlowRpm;
		};

		uint8_t solenoidTime;							//OKEY 8 BIT
		/***************************************************************/
		uint8_t solenoidActiveTime;						//OKEY 8 BIT
		/***************************************************************/
		uint8_t solenoidPassiveTime;					//OKEY 8 BIT
		/***************************************************************/
		uint16_t cockingHandleArmedDistance;			//OKEY 16 BIT
		uint16_t cockingHandleSafeDistance;				//OKEY 16 BIT

		struct
		{
			bool commandWarMode;							//OKEY 1 BIT
			bool commandEmergencyStop;						//OKEY 1 BIT
			bool commandHERCULEPowerOnOff;					//OKEY 1 BIT
			bool commandEOSPowerOnOff;						//OKEY 1 BIT
			bool commandKKBPowerOnOff;						//OKEY 1 BIT
			bool commandAKBPowerOnOff;						//OKEY 1 BIT
			bool commandSOLPowerOnOff;						//OKEY 1 BIT
			bool commandCHPowerOnOff;						//OKEY 1 BIT
			bool commandCockingHandleHome;					//OKEY 1 BIT
			bool commandCockingHandleSafe;					//OKEY 1 BIT
			bool commandCockingHandleArm;					//OKEY 1 BIT
		}previous;

	}AKB;

	struct
	{
		ID ID400;
		ID ID401;
		ID ID402;
		ID ID403;
		ID ID404;
	}sendPackage;

}canMessages;

//typedef struct
//{
//	uint8_t gunID;
//	uint8_t gunType;
//
//	bool onOffHERCULE;
//	bool onOffEOS;
//	bool onOffKKU;
//	bool onOffAKB;
//
//
//	bool overrideFireBlocked;
//	bool overrideSmga;
//
//	uint8_t cockingHandleArmedDistance;
//	uint8_t cockingHandleSafeDistance;
//
//	uint16_t solenoidFastRpm;
//	uint16_t solenoidSlowRpm;
//	uint8_t  solenoidFireMode;
//	uint8_t  solenoidTime;
//	uint8_t  solenoidActiveTime;						//OKEY 8 BIT
//	uint8_t  solenoidPassiveTime;
//
//
//}configurations;

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

	bool isPluggedAKB;
	bool isPluggedEOS;
	bool isPluggedHERCULE;
	bool isPluggedKKU;
	bool isPluggedSOL;
	bool isPluggedCH;

	bool HERCULEOK;
	bool KKUOK;
	bool AKBOK;
	bool EOSOK;
	bool GDBOK;
	bool SOLOK;
	bool CHOK;

	bool system;
}error;

typedef struct
{
	uint8_t cockingHandleArmedDistance;
	uint8_t cockingHandleSafeDistance;

	uint8_t fireMode;

	uint16_t solenoidFastRpm;
	uint16_t solenoidSlowRpm;
	uint8_t  solenoidFireMode;
	uint8_t  solenoidTime;
	uint8_t  solenoidActiveTime;						//OKEY 8 BIT
	uint8_t  solenoidPassiveTime;
}eeprom;

typedef struct
{
	struct
	{
		int32_t 	encoderCounter;
		bool 		encoderRotation;								// 1: FORWARD 0:BACKWARD
		uint8_t 	motorState;										// OKEY
		bool 		brakeState;
		bool 		armed;											// OKEY
		bool 		safe;											// OKEY
		bool 		home;											// OKEY
	}cockingHandle;

	struct
	{
		uint8_t ammoCounter;
		bool tetikBilgisi;
	}solenoid;
}gun;

typedef struct
{
	bool firing;
//	bool overrideFireBlocked;
	bool overrideSmga;
	//bool overrideWarMode;
	//bool overrideEmergencyStop;

	bool fireBlocked;
	bool emergencyStop;
	bool firePermission;



	bool 		solenoidActive;
	bool 		triggerHeld;
	bool 		shuttingDown;
	uint32_t 	changeTime;
	uint16_t 	burstCounter;
	uint32_t 	ammoCounter;
	uint8_t 	systemMode;

	/***************************************************************/
	bool HERCULEPowerOnOff;
	bool EOSPowerOnOff;
	bool KKBPowerOnOff;
	bool AKBPowerOnOff;
	bool SOLPowerOnOff;
	bool CHPowerOnOff;


}states;

typedef struct
{
	bool herculeOK;
	bool kkuOK;
	bool akbOK;
	bool eosOK;
	bool gdbOK;
	bool solenoidOK;
	bool cockingHandleOK;

	uint32_t SCurrent;
	uint32_t CHCurrent;
	uint32_t HERCULECurrent;
	uint32_t KKUCurrent;
	uint32_t AKBCurrent;
	uint32_t GDBCurrent;
	uint32_t EOSCurrent;
	uint32_t BATVoltage;
}powerManagement;

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
	//configurations configurations;
	powerManagement powerManagement;
	analogDigitalConverter analogDigitalConverter;
}pandoraStructer;

extern pandoraStructer pandora;

#endif /* DEFINITIONS_H_ */
