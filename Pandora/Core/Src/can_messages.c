/*
 * can_messages.c
 *
 *  Created on: Jan 8, 2025
 *      Author: AHP
 */
#include "can_messages.h"
#include "functions.h"
#include "definitions.h"
#include "peripherals.h"

extern pandoraStructer pandora;

void prepareSendPackages (void)
{
//	pandora.canMessages.ID._400.REG1.byte		= VBAT_MSB;
//	pandora.canMessages.ID._400.REG2.byte		= VBAT_LSB;
//
//	pandora.canMessages.ID._400.REG3.bit1 		= NOT_USED;							// NOT_USED
//	pandora.canMessages.ID._400.REG3.bit2 		= NOT_USED;							// NOT_USED
//	pandora.canMessages.ID._400.REG3.bit3 		= NOT_USED;							// NOT_USED
//	pandora.canMessages.ID._400.REG3.bit4 		= NOT_USED;							// NOT_USED
//	pandora.canMessages.ID._400.REG3.bit5 		= MACHINE_GUN_HOME_FEEDBACK;		// 1: HOME
//	pandora.canMessages.ID._400.REG3.bit6 		= MACHINE_GUN_SAFE_FEEDBACK;		// 1: SAFE
//	pandora.canMessages.ID._400.REG3.bit7 		= MACHINE_GUN_ARMED_FEEDBACK;		// 1: ARMED
//
//	pandora.canMessages.ID._400.REG4.bit1 		= NOT_USED;							// NOT_USED
//	pandora.canMessages.ID._400.REG4.bit2 		= NOT_USED;							// NOT_USED
//	pandora.canMessages.ID._400.REG4.bit3 		= NOT_USED;							// NOT_USED
//	pandora.canMessages.ID._400.REG4.bit4 		= NOT_USED;							// NOT_USED
//	pandora.canMessages.ID._400.REG4.bit5 		= NOT_USED;							// NOT_USED
//	pandora.canMessages.ID._400.REG4.bit6 		= NOT_USED;							// NOT_USED
//	pandora.canMessages.ID._400.REG4.bit7 		= SYSTEM_SHUTTING_DOWN;				// 1: SHUTTING
//
//	pandora.canMessages.ID._400.REG5.bit1 		= SERVO_POWER_FEEDBACK;				// 1: POWERED
//	pandora.canMessages.ID._400.REG5.bit2 		= H1D_POWER_FEEDBACK;				// NOT_USED
//	pandora.canMessages.ID._400.REG5.bit3 		= NOT_USED;							// NOT_USED
//	pandora.canMessages.ID._400.REG5.bit4 		= NOT_USED;							// NOT_USED
//	pandora.canMessages.ID._400.REG5.bit5 		= NOT_USED;							// NOT_USED
//	pandora.canMessages.ID._400.REG5.bit6 		= NOT_USED;							// NOT_USED
//	pandora.canMessages.ID._400.REG5.bit7 		= SYSTEM_SHUTTING_DOWN;				// 1: SHUTTING

//	pandora.canMessages.ID._400.REG4
//	pandora.canMessages.ID._400.REG5
//	pandora.canMessages.ID._400.REG6
//	pandora.canMessages.ID._400.REG7
}

void sendCanMessages (void)
{
	SEND_CAN_MESSAGE(0x400,0x55,5);

	pandora.canMessages.sendPackage.byte_0 = 0x00;
	pandora.canMessages.sendPackage.byte_1 = 0x00;
	pandora.canMessages.sendPackage.byte_2 = 0x00;
	pandora.canMessages.sendPackage.byte_3 = 0x00;
	pandora.canMessages.sendPackage.byte_4 = 0x00;
	pandora.canMessages.sendPackage.byte_5 = 0x00;
	pandora.canMessages.sendPackage.byte_6 = 0x00;
	pandora.canMessages.sendPackage.byte_7 = 0x00;

	/*SWITCHES STATE BEGIN*/
	WRITE_BIT(pandora.canMessages.sendPackage.byte_0,BIT_0,pandora.switches.switches_smga);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_0,BIT_1,pandora.switches.switches_2);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_0,BIT_2,pandora.switches.switches_4);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_0,BIT_3,pandora.switches.switches_5);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_0,BIT_4,pandora.switches.switches_6);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_0,BIT_5,pandora.switches.switches_7);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_0,BIT_6,pandora.switches.switches_fire_feedback );
	WRITE_BIT(pandora.canMessages.sendPackage.byte_0,BIT_7,pandora.switches.switches_safety_feedback);

	WRITE_BIT(pandora.canMessages.sendPackage.byte_1,BIT_0,pandora.switches.switches_cocking_handle_home);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_1,BIT_1,pandora.switches.reserved_1);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_1,BIT_2,pandora.switches.reserved_2);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_1,BIT_3,pandora.switches.reserved_3);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_1,BIT_4,pandora.switches.reserved_4);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_1,BIT_5,pandora.switches.reserved_5);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_1,BIT_6,pandora.switches.reserved_6);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_1,BIT_7,pandora.switches.reserved_7);
	/*SWITCHES STATE END*/

	/*ERRORS STATE BEGIN*/
	WRITE_BIT(pandora.canMessages.sendPackage.byte_2,BIT_0,pandora.CIT.errorAKBCurrent);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_2,BIT_1,pandora.CIT.errorBatteryVoltage);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_2,BIT_2,pandora.CIT.errorCockingHandleCurrent);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_2,BIT_3,pandora.CIT.errorEOSCurrent);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_2,BIT_4,pandora.CIT.errorGDBCurrent);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_2,BIT_5,pandora.CIT.errorHerculeCurrent);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_2,BIT_6,pandora.CIT.errorKKUCurrent);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_2,BIT_7,pandora.CIT.errorSolenoidCurrent);

	WRITE_BIT(pandora.canMessages.sendPackage.byte_3,BIT_0,pandora.CIT.reserved_1);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_3,BIT_1,pandora.CIT.reserved_2);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_3,BIT_2,pandora.CIT.reserved_3);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_3,BIT_3,pandora.CIT.reserved_4);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_3,BIT_4,pandora.CIT.reserved_5);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_3,BIT_5,pandora.CIT.reserved_6);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_3,BIT_6,pandora.CIT.reserved_7);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_3,BIT_7,pandora.CIT.reserved_8);
	/*ERRORS STATE END*/

	/*ID400 BEGIN*/
	pandora.canMessages.sendPackage.byte_4 = (uint8_t)(pandora.powerManagement.batteryVoltage >> 8); // HIGH byte
	pandora.canMessages.sendPackage.byte_5 = (uint8_t)(pandora.powerManagement.batteryVoltage & 0xFF); // LOW byte

	pandora.canMessages.sendPackage.byte_6 = ((pandora.canMessages.AKB.gunID & 0x0F) << 4) | (pandora.canMessages.AKB.gunType & 0x0F);

	pandora.canMessages.sendPackage.byte_7 = (uint8_t)(pandora.gun.fireSolenoid.ammoCounter >> 8); // HIGH byte
	pandora.canMessages.sendPackage.byte_8 = (uint8_t)(pandora.gun.fireSolenoid.ammoCounter & 0xFF); // LOW byte

	//WRITE_BIT(pandora.canMessages.sendPackage.byte_6,BIT_0,pandora. );
	//WRITE_BIT(pandora.canMessages.sendPackage.byte_6,BIT_1,pandora. );
	//WRITE_BIT(pandora.canMessages.sendPackage.byte_6,BIT_2,pandora. );
	//WRITE_BIT(pandora.canMessages.sendPackage.byte_6,BIT_3,pandora. );
	//WRITE_BIT(pandora.canMessages.sendPackage.byte_6,BIT_4,pandora. );
	WRITE_BIT(pandora.canMessages.sendPackage.byte_6,BIT_5,pandora.gun.cockingHandle.home);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_6,BIT_6,pandora.gun.cockingHandle.safe);
	WRITE_BIT(pandora.canMessages.sendPackage.byte_6,BIT_7,pandora.gun.cockingHandle.armed);

	//pandora.canMessages.sendPackage.byte_7 = ;

	//pandora.canMessages.sendPackage.byte_8 = ;



	/*ID400 END*/

}

HAL_StatusTypeDef FDCAN_SendMessage(FDCAN_HandleTypeDef *hfdcan, uint32_t id, uint8_t *data, uint8_t length)
{
    FDCAN_TxHeaderTypeDef TxHeader;

    TxHeader.Identifier 			= id;
    TxHeader.IdType 				= FDCAN_STANDARD_ID;
    TxHeader.TxFrameType 			= FDCAN_DATA_FRAME;
    TxHeader.DataLength 			= length << 16;
    TxHeader.ErrorStateIndicator 	= FDCAN_ESI_ACTIVE;
    TxHeader.BitRateSwitch 			= FDCAN_BRS_OFF;
    TxHeader.FDFormat 				= FDCAN_CLASSIC_CAN;
    TxHeader.TxEventFifoControl 	= FDCAN_NO_TX_EVENTS;

    return HAL_FDCAN_AddMessageToTxFifoQ(hfdcan, &TxHeader, data);
}

HAL_StatusTypeDef FDCAN_ReceiveMessage(FDCAN_HandleTypeDef *hfdcan)
{
    FDCAN_RxHeaderTypeDef RxHeader;
    uint8_t RxData[8];


    if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK)
    {
        switch (RxHeader.Identifier)
        {
        case ID_KKU:           // 0x101 #define olarak fonksiyon numaralarıyla tanımla
        	eventKKU(RxData, RxHeader.DataLength);
            break;

        case AKB_199:
        	eventAKB(RxHeader.Identifier, RxData, RxHeader.DataLength);
            break;

        case AKB_200:
        	eventAKB(RxHeader.Identifier, RxData, RxHeader.DataLength);
            break;


        default:
            // none
            break;
        }
    }

    return HAL_ERROR; // Mesaj alımı başarısız
}

void eventKKU(uint8_t *data, uint8_t dataLenght)  /*örnektir. ICD oluşturulacak*/
{
	pandora.canMessages.KKU.hareketAnahtari 	= GET_BIT(data[2],3); // Kontrol için kullanılabilir Normalde PIO
	pandora.canMessages.KKU.atisEmniyetAnahtari = GET_BIT(data[1],0); // Kontrol için kullanılabilir Normalde PIO
	pandora.canMessages.KKU.kurmaAnahtari 		= GET_BIT(data[2],7); // Kontrol için kullanılabilir Normalde PIO
	pandora.canMessages.KKU.savasModuAnahtari	= GET_BIT(data[4],5); // Kontrol için kullanılabilir Normalde PIO
	pandora.canMessages.KKU.SMGAYoksay			= GET_BIT(data[3],5); // Kontrol için kullanılabilir Normalde PIO
}

void eventAKB(uint32_t id, uint8_t *data, uint8_t dataLenght)
{
	if(id == 199)
	{
		pandora.canMessages.AKB.commandFireMode					= (uint8_t)(GET_BIT(data[0],2) << 2) | (uint8_t)(GET_BIT(data[0],1) << 1) | (GET_BIT(data[0],0));
		pandora.canMessages.AKB.commandCockingHandleSafe		= (GET_BIT(data[0],3));
		pandora.canMessages.AKB.commandGunFire					= (GET_BIT(data[0],4));
		//pandora.canMessages.AKB.commandGunType					= (uint8_t)(GET_BIT(data[0],6) << 1) | (GET_BIT(data[0],5));
		pandora.canMessages.AKB.commandCockingHandleArm			= (GET_BIT(data[0],7));

		pandora.canMessages.AKB.commandCockingHandleCancel		= (GET_BIT(data[1],0));
		pandora.canMessages.AKB.commandSmgaAllowed				= (GET_BIT(data[1],1));
		pandora.canMessages.AKB.commandCounterSenseCancel		= (GET_BIT(data[1],2));
		pandora.canMessages.AKB.commandWarMode					= (GET_BIT(data[1],3));
		pandora.canMessages.AKB.commandEmergencyStop			= (GET_BIT(data[1],4));
		//pandora.canMessages.AKB.eyleyiciPowerOnOff			= (GET_BIT(data[1],5));		//SUBS
		pandora.canMessages.AKB.commandCockingHandleHome		= (GET_BIT(data[1],6));
		//pandora.canMessages.AKB.commandMode2					= (GET_BIT(data[1],7));		//SUBS
	}

	else if(id == 200)
	{
		pandora.canMessages.AKB.commandServoOnOff				= (GET_BIT(data[0],0));
		pandora.canMessages.AKB.commandEOSOnOff					= (GET_BIT(data[0],1));	//SUBS
		//pandora.canMessages.AKB.commandAKBOnOff					= (GET_BIT(data[0],2));
		pandora.canMessages.AKB.commandKKBOnOff					= (GET_BIT(data[0],3));
		//pandora.canMessages.AKB.commandEmergencyStop			= (GET_BIT(data[0],4));
		//pandora.canMessages.AKB.eyleyiciPowerOnOff			= (GET_BIT(data[0],5));		//SUBS
		//pandora.canMessages.AKB.commandCockingHandleHome		= (GET_BIT(data[0],6));
		pandora.canMessages.AKB.canBusOk						= (GET_BIT(data[0],7));		//SUBS

	}

	else if (id == 800)
	{
		pandora.canMessages.AKB.gunType						= (uint8_t)(GET_BIT(data[0],3) << 3) | (uint8_t)(GET_BIT(data[0],2) << 2) | (uint8_t)(GET_BIT(data[0],1) << 1) | (GET_BIT(data[0],0));
		pandora.canMessages.AKB.gunID						= (uint8_t)(GET_BIT(data[0],7) << 7) | (uint8_t)(GET_BIT(data[0],6) << 6) | (uint8_t)(GET_BIT(data[0],5) << 5) | (GET_BIT(data[0],4));
		pandora.canMessages.AKB.fastRpmHighByte				= data[1];
		pandora.canMessages.AKB.fastRpmLowByte				= data[2];
		pandora.canMessages.AKB.slowRpmHighByte				= data[3];
		pandora.canMessages.AKB.slowRpmLowByte				= data[4];
		pandora.canMessages.AKB.solenoidTime				= data[5];
		pandora.canMessages.AKB.solenoidActiveTime			= data[6];
		pandora.canMessages.AKB.solenoidPassiveTime			= data[7];

		pandora.gun.gunType = pandora.canMessages.AKB.gunType;
		pandora.gun.configurations.solenoid
	}

}



void eventEOS(uint8_t *data, uint8_t dataLenght)
{
	/*
	 * GDB EOS ile direkt olarak iletişim halinde değil
	 */
}

void eventHERCULE(uint8_t *data, uint8_t dataLenght)
{
	/*
	 * GDB Hercule ile direkt olarak iletişim halinde değil.
	 */
}
