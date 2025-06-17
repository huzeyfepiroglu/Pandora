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
		pandora.canMessages.AKB.firingRate				= (uint8_t)(GET_BIT(data[0],2) << 2) | (uint8_t)(GET_BIT(data[0],1) << 1) | (GET_BIT(data[0],0));
		pandora.canMessages.AKB.machineGunSafe			= (GET_BIT(data[0],3));
	}
	pandora.canMessages.AKB.cockingHandleArmedDistance 	= data[8];
	pandora.canMessages.AKB.cockingHandleSafeDistance 	= data[7];
	pandora.canMessages.AKB.fireBlockedArea 			= GET_BIT(data[0],0);
	pandora.canMessages.AKB.fireMode 					= 0;
	pandora.canMessages.AKB.gunMode.value 				=  (uint8_t)(GET_BIT(data[5],1) << 1)  | (GET_BIT(data[5],0));
	pandora.canMessages.AKB.solenoidActiveTime 			= data[6];
	pandora.canMessages.AKB.solenoidPassiveTime 		= data[7];
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
