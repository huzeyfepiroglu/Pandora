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
#include "cocking_handle_maingun.h"

extern pandoraStructer pandora;

void prepareSendPackages (void)
{

}
/*
 *	AKB->GDB	199		RECEIVE		OK
 *	AKB->GDB	200		RECEIVE		OK
 *
 *	GDB->AKB	400		TRANSMIT	OK
 *	GDB->AKB	401		TRANSMIT	OK
 *	GDB->AKB	501		TRANSMIT
 *	GDB->AKB	505		TRANSMIT
 *
 *	AKB->GDB	800		RECEIVE		OK
 *	GDB->AKB	800		TRANSMIT
 */
void sendCanMessages (void)
{
	pandora.canMessages.sendPackage.ID400.byte_0.byte = (uint8_t)(pandora.powerManagement.batteryVoltage >> 8); 		// HIGH byte
	pandora.canMessages.sendPackage.ID400.byte_1.byte = (uint8_t)(pandora.powerManagement.batteryVoltage & 0xFF); 	// LOW byte

	pandora.canMessages.sendPackage.ID400.byte_2.bit5 = pandora.gun.cockingHandle.home;
	pandora.canMessages.sendPackage.ID400.byte_2.bit6 = pandora.gun.cockingHandle.safe;
	pandora.canMessages.sendPackage.ID400.byte_2.bit7 = pandora.gun.cockingHandle.armed;

	pandora.canMessages.sendPackage.ID400.byte_3.bit7 = pandora.states.shuttingDown;

	pandora.canMessages.sendPackage.ID400.byte_4.bit0 = pandora.powerManagement.herculeOK;
	pandora.canMessages.sendPackage.ID400.byte_4.bit1 = pandora.powerManagement.kkuOK;
	pandora.canMessages.sendPackage.ID400.byte_4.bit2 = pandora.powerManagement.akbOK;
	pandora.canMessages.sendPackage.ID400.byte_4.bit3 = pandora.powerManagement.eosOK;
	pandora.canMessages.sendPackage.ID400.byte_4.bit4 = pandora.powerManagement.gdbOK;
	pandora.canMessages.sendPackage.ID400.byte_4.bit5 = pandora.powerManagement.solenoidOK;
	pandora.canMessages.sendPackage.ID400.byte_4.bit6 = pandora.powerManagement.cockingHandleOK;

	pandora.canMessages.sendPackage.ID400.byte_5.byte = ((pandora.configurations.gunID & 0x0F) << 4) | (pandora.configurations.gunType & 0x0F);

	pandora.canMessages.sendPackage.ID400.byte_6.byte = ((pandora.states.systemMode & 0x0F) << 4) | (0x00);


/////////////////////////

	pandora.canMessages.sendPackage.ID401.byte_0.byte |= pandora.configurations.solenoidFireMode & 0x07;

	pandora.canMessages.sendPackage.ID401.byte_0.byte |= (pandora.gun.cockingHandle.motorState & 0x03) << 3;

//////////////////////////
	pandora.canMessages.sendPackage.ID402.byte_0.bit0 =	pandora.switches.switches_cocking_handle_home;
	pandora.canMessages.sendPackage.ID402.byte_0.bit1 =	pandora.switches.switches_cocking_handle_order;
	pandora.canMessages.sendPackage.ID402.byte_0.bit2 =	pandora.switches.switches_fire_order;
	pandora.canMessages.sendPackage.ID402.byte_0.bit3 =	pandora.switches.switches_movement_allowed;
	pandora.canMessages.sendPackage.ID402.byte_0.bit4 =	pandora.switches.switches_safety;
	pandora.canMessages.sendPackage.ID402.byte_0.bit5 =	pandora.switches.switches_smga;
	pandora.canMessages.sendPackage.ID402.byte_0.bit6 =	pandora.switches.switches_system_on_off;
	pandora.canMessages.sendPackage.ID402.byte_0.bit7 = pandora.switches.
//////////////////////////

	pandora.canMessages.sendPackage.ID404.byte_0.bit0 = pandora.error.solenoidCurrentLow;
	pandora.canMessages.sendPackage.ID404.byte_0.bit1 = pandora.error.solenoidCurrentHigh;
	pandora.canMessages.sendPackage.ID404.byte_0.bit2 = pandora.error.cockingHandleCurrentLow;
	pandora.canMessages.sendPackage.ID404.byte_0.bit3 = pandora.error.cockingHandleCurrentHigh;
	pandora.canMessages.sendPackage.ID404.byte_0.bit4 = pandora.error.akbCurrentLow;
	pandora.canMessages.sendPackage.ID404.byte_0.bit5 = pandora.error.akbCurrentHigh;
	pandora.canMessages.sendPackage.ID404.byte_0.bit6 = pandora.error.kkuCurrentLow;
	pandora.canMessages.sendPackage.ID404.byte_0.bit7 = pandora.error.kkuCurrentHigh;

	pandora.canMessages.sendPackage.ID404.byte_1.bit0 = pandora.error.eosCurrentLow;
	pandora.canMessages.sendPackage.ID404.byte_1.bit1 = pandora.error.eosCurrentHigh;
	pandora.canMessages.sendPackage.ID404.byte_1.bit2 = pandora.error.gdbCurrentLow;
	pandora.canMessages.sendPackage.ID404.byte_1.bit3 = pandora.error.gdbCurrentHigh;
	pandora.canMessages.sendPackage.ID404.byte_1.bit4 = pandora.error.gdbVoltageLow;
	pandora.canMessages.sendPackage.ID404.byte_1.bit5 = pandora.error.gdbVoltageHigh;

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
    	eventAKB(RxHeader.Identifier, RxData);
    }

    return HAL_ERROR; // Mesaj alımı başarısız
}


void eventAKB(uint32_t id, uint8_t *data)
{
	if(id == 199)
	{
		pandora.canMessages.AKB.commandFireMode					= (uint8_t)(GET_BIT(data[0],2) << 2) | (uint8_t)(GET_BIT(data[0],1) << 1) | (GET_BIT(data[0],0));
		pandora.canMessages.AKB.commandCockingHandleSafe		= (GET_BIT(data[0],3));
		pandora.canMessages.AKB.commandGunFire					= (GET_BIT(data[0],4));
		//pandora.canMessages.AKB.commandGunType					= (uint8_t)(GET_BIT(data[0],6) << 1) | (GET_BIT(data[0],5));
		pandora.canMessages.AKB.commandCockingHandleArm			= (GET_BIT(data[0],7));

		//pandora.canMessages.AKB.commandCockingHandleCancel		= (GET_BIT(data[1],0));	//SUBS
		pandora.canMessages.AKB.commandSmgaAllowed				= (GET_BIT(data[1],1));
		//pandora.canMessages.AKB.commandCounterSenseCancel		= (GET_BIT(data[1],2));		//SUBS
		pandora.canMessages.AKB.commandWarMode					= (GET_BIT(data[1],3));
		pandora.canMessages.AKB.commandEmergencyStop			= (GET_BIT(data[1],4));
		//pandora.canMessages.AKB.eyleyiciPowerOnOff			= (GET_BIT(data[1],5));		//SUBS
		pandora.canMessages.AKB.commandCockingHandleHome		= (GET_BIT(data[1],6));
		pandora.canMessages.AKB.commandMode						= (GET_BIT(data[1],7));
	}

	else if(id == 200)
	{
		pandora.canMessages.AKB.commandServoOnOff				= (GET_BIT(data[0],0));
		pandora.canMessages.AKB.commandEOSOnOff					= (GET_BIT(data[0],1));		//SUBS
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

		pandora.gunType = pandora.canMessages.AKB.gunType;

	}

}

//
//void eventEOS(uint8_t *data, uint8_t dataLenght)
//{
//	/*
//	 * GDB EOS ile direkt olarak iletişim halinde değil
//	 */
//}
//
//void eventHERCULE(uint8_t *data, uint8_t dataLenght)
//{
//	/*
//	 * GDB Hercule ile direkt olarak iletişim halinde değil.
//	 */
//}
//
//void eventKKU(uint8_t *data, uint8_t dataLenght)
//{
//	/*
//	 * KKU Hercule ile direkt olarak iletişim halinde değil.
//	 */
//}










//HAL_StatusTypeDef FDCAN_ReceiveMessage(FDCAN_HandleTypeDef *hfdcan)
//{
//    FDCAN_RxHeaderTypeDef RxHeader;
//    uint8_t RxData[8];
//
//    if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK)
//    {
//        if(RxHeader.Identifier == COMMAND_ID)
//        {
//        	checkCommand(RxData);
//        }
//        else if(RxHeader.Identifier == REQUEST_ID)
//        {
//        	checkRequest(RxData);
//        }
//    }
//
//    return HAL_ERROR; // Mesaj alımı başarısız
//}

//void sendAckUart(void)
//{
//	uint8_t bufferACK[8];
//
//	bufferACK[0] = ACK_HEADER;
//	bufferACK[1] = 0X01;
//	bufferACK[2] = 0x00;
//	bufferACK[3] = 0x00;
//	bufferACK[4] = 0x00;
//	bufferACK[5] = 0x00;
//	bufferACK[6] = 0x00;
//	bufferACK[7] = 0x00;
//
//	FDCAN_SendMessage(&hfdcan2, ACK_ID    ,bufferACK, 8);
//}
//
//void checkCommand(uint8_t* data)
//{
//	switch (data[1])
//	{
//		case COMMAND_COCKING_HANDLE_ARMED_DISTANCE:
//			pandora.configurations.cockingHandleArmedDistance = (uint16_t)data[3] << 8 | data[2];
//			sendAckUart();
//		break;
//
//		case COMMAND_COCKING_HANDLE_SAFE_DISTANCE:
//			pandora.configurations.cockingHandleSafeDistance = (uint16_t)data[3] << 8 | data[2];
//			sendAckUart();
//		break;
//
//		case COMMAND_COCKING_HANDLE_SAFE:
//			functionCockingHandleGoSafe();
//			sendAckUart();
//		break;
//
//		case COMMAND_COCKING_HANDLE_ARM:
//			functionCockingHandleGoArm();
//			sendAckUart();
//		break;
//
//		case COMMAND_COCKING_HANDLE_HOME:
//			functionCockingHandleGoHome();
//			sendAckUart();
//		break;
//
//		case COMMAND_SOLENOID_FAST_RPM:
//			pandora.configurations.solenoidFastRpm = (uint16_t)data[3] << 8 | data[2];
//			sendAckUart();
//		break;
//
//		case COMMAND_SOLENOID_SLOW_RPM:
//			pandora.configurations.solenoidSlowRpm = (uint16_t)data[3] << 8 | data[2];
//			sendAckUart();
//		break;
//
//		case COMMAND_SOLENOID_TIME:
//			pandora.configurations.solenoidTime = data[2];
//			sendAckUart();
//		break;
//
//		case COMMAND_SOLENOID_ACTIVE_TIME:
//			pandora.configurations.solenoidActiveTime = data[2];
//			sendAckUart();
//		break;
//
//		case COMMAND_SOLENOID_PASSIVE_TIME:
//			pandora.configurations.solenoidPassiveTime = data[2];
//			sendAckUart();
//		break;
//
//		case COMMAND_SOLENOID_FIRE_MODE:
//			pandora.configurations.solenoidFireMode = data[2];
//			sendAckUart();
//		break;
//
//		case COMMAND_FIRE:
//			// TEHLİKELİ YAZILIMSAL OLARAK ŞUANDA YOK
//			sendAckUart();
//		break;
//
//		case COMMAND_OVERRIDE_SMGA:
//			pandora.configurations.overrideSmga = data[2];
//			sendAckUart();
//		break;
//
//		case COMMAND_OVERRIDE_FIRE_BLOCKED:
//			pandora.configurations.overrideFireBlocked = data[2];
//			sendAckUart();
//		break;
//
//		case COMMAND_OVERRIDE_WAR_MODE:
//			pandora.configurations.overrideWarMode = data[2];
//			sendAckUart();
//		break;
//
//		case COMMAND_OVERRIDE_EMERGENCY_STOP:
//			pandora.configurations.overrideEmergencyStop = data[2];
//			sendAckUart();
//		break;
//
//		case COMMAND_ON_OFF_HERCULE:
//			pandora.configurations.onOffServo = data[2];
//
//			sendAckUart();
//		break;
//
//		case COMMAND_ON_OFF_KKU:
//			pandora.configurations.onOffServo = data[2];
//			sendAckUart();
//		break;
//
//		case COMMAND_ON_OFF_EOS:
//			pandora.configurations.onOffEOS = data[2];
//			sendAckUart();
//		break;
//
//		case COMMAND_SET_SYSTEM_DEFAULT_DATA:
//			//
//			//
//			//
//			//
//			//
//			sendAckUart();
//		break;
//
//		case COMMAND_SAVE_TO_FLASH:
//
//			pandora.eeprom.cockingHandleArmedDistance = pandora.canMessages.AKB.cockingHandleArmedDistance;
//			pandora.eeprom.cockingHandleSafeDistance = pandora.canMessages.AKB.cockingHandleSafeDistance;
//			pandora.eeprom.solenoidActiveTime = pandora.canMessages.AKB.solenoidActiveTime ;
//
//			functionSaveToFlash();
//			sendAckUart();
//		break;
//
//		case COMMAND_SYSTEM_RESET:
//			sendAckUart();
//			HAL_NVIC_SystemReset();
//		break;
//
//	}
//}
//
//void checkRequest(uint8_t* data)
//{
//	uint8_t responseSend[8];
//
//	switch (data[1])
//	{
//		case REQUEST_FUNC_1:
//			responseSend[0] = REQUEST_HEADER;
//			responseSend[1] = REQUEST_FUNC_1;
//			responseSend[2] = 0X12;
//			responseSend[3] = 0x00;
//			responseSend[4] = 0x00;
//			responseSend[5] = 0x00;
//			responseSend[6] = 0x00;
//			responseSend[7] = 0x00;
//
//			FDCAN_SendMessage(&hfdcan2,REQUEST_ID,responseSend, 8);
//			//HAL_UART_Transmit(&huart3, (uint8_t*)responseSend, 9, 5000);
//		break;
//
//		case REQUEST_FUNC_2:
//			responseSend[0] = REQUEST_HEADER;
//			responseSend[1] = REQUEST_FUNC_2;
//			responseSend[2] = 0X00;
//			responseSend[3] = 0X00;
//			responseSend[4] = 0X00;
//			responseSend[5] = 0X00;
//			responseSend[6] = 0X00;
//			responseSend[7] = 0X00;
//
//			FDCAN_SendMessage(&hfdcan2,REQUEST_ID,responseSend, 8);
//			//HAL_UART_Transmit(&huart3, (uint8_t*)responseSend, 9, 5000);
//
//		break;
//	}
//}
//
