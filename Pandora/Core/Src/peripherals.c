/*
 * peripherals.c
 *
 *  Created on: May 13, 2025
 *      Author: Abdullah Huzeyfe Piroğlu
 */

#include "peripherals.h"
#include "definitions.h"

extern pandoraStructer pandora;

#define COUNT_BUTTON	9

typedef struct digitalInput_Struct
{
	GPIO_PinState 	inputVal;					//INIT - GPIO_PIN_RESET 	check if error is occured, change variable type to bit
	bool 			readFlag;					//INIT -> false
	uint16_t 		inputPin;					//CUSTOM
	GPIO_TypeDef 	*inputPort;					//CUSTOM
	GPIO_PinState 	readState;
	uint32_t 		debounceTimer;				//INIT -> 0
	uint32_t 		debounceFactor;				//CUSTOM-INIT

} digitalInput;

typedef struct {
    GPIO_TypeDef* port;         // Butonun bağlı olduğu GPIO portu (örneğin GPIOA)
    uint16_t pin;               // Butonun bağlı olduğu pin (örneğin GPIO_PIN_0)
    uint8_t state;              // Son bilinen buton durumu (HIGH veya LOW)
    uint32_t lastChangeTime;    // En son buton durumu değişim zamanı (debounce için)
} Switches_t;

typedef enum {
    FIRE_SAFETY_SWITCH = 0,
	COCKING_HANDLE_SWITCH,
	MOVEMENT_SWITCH,
	FIRE_ORDER_SWITCH,
	SYSTEM_ON_OFF_SWITCH,
	SMGA_SWITCH,
	COCKING_HANDLE_HOME_SWITCH,
	CREW_1_SWITCH,
	CREW_2_SWITCH,
	SWITCHES_COUNT
} switchEnum;

Switches_t switchesArray[SWITCHES_COUNT] =
{
	[FIRE_SAFETY_SWITCH] 		= {SWITCHES_SAFETY_GPIO_Port 				, SWITCHES_SAFETY_Pin 				, false , 0},
	[COCKING_HANDLE_SWITCH]		= {SWITCHES_COCKING_HANDLE_ORDER_GPIO_Port  , SWITCHES_COCKING_HANDLE_ORDER_Pin , false , 0},
	[MOVEMENT_SWITCH] 			= {SWITCHES_MOVEMENT_ALLOWED_GPIO_Port		, SWITCHES_MOVEMENT_ALLOWED_Pin 	, false , 0},
	[FIRE_ORDER_SWITCH] 		= {SWITCHES_FIRE_ORDER_GPIO_Port	  		, SWITCHES_FIRE_ORDER_Pin 			, false , 0},
	[SYSTEM_ON_OFF_SWITCH] 		= {SWITCHES_SYSTEM_ON_OFF_GPIO_Port	  		, SWITCHES_SYSTEM_ON_OFF_Pin 		, false , 0},
	[SMGA_SWITCH]				= {SWITCHES_SMGA_GPIO_Port			  		, SWITCHES_SMGA_Pin		 			, false , 0},
	[COCKING_HANDLE_HOME_SWITCH]= {SWITCHES_COCKING_HANDLE_HOME_GPIO_Port	, SWITCHES_COCKING_HANDLE_HOME_Pin	, false , 0},
	[CREW_1_SWITCH] 			= {SWITCHES_CREW_1_GPIO_Port				, SWITCHES_CREW_1_Pin	 			, false , 0},
	[CREW_2_SWITCH]				= {SWITCHES_CREW_2_GPIO_Port				, SWITCHES_CREW_2_Pin	 			, false , 0},
};

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    uint32_t now = HAL_GetTick();

    // FIRE_SAFETY_SWITCH
    if (GPIO_Pin == SWITCHES_SAFETY_Pin)
    {
        if ((now - switchesArray[FIRE_SAFETY_SWITCH].lastChangeTime) >= DEBOUNCE_DELAY_MS)
        {
            switchesArray[FIRE_SAFETY_SWITCH].state = HAL_GPIO_ReadPin(SWITCHES_SAFETY_GPIO_Port, SWITCHES_SAFETY_Pin);
            pandora.switches.switches_safety = switchesArray[FIRE_SAFETY_SWITCH].state;
            switchesArray[FIRE_SAFETY_SWITCH].lastChangeTime = now;
        }
    }

    // COCKING_HANDLE_SWITCH
    else if (GPIO_Pin == SWITCHES_COCKING_HANDLE_ORDER_Pin)
    {
        if ((now - switchesArray[COCKING_HANDLE_SWITCH].lastChangeTime) >= DEBOUNCE_DELAY_MS)
        {
            switchesArray[COCKING_HANDLE_SWITCH].state = HAL_GPIO_ReadPin(SWITCHES_COCKING_HANDLE_ORDER_GPIO_Port, SWITCHES_COCKING_HANDLE_ORDER_Pin);
            pandora.switches.switches_cocking_handle_order = switchesArray[COCKING_HANDLE_SWITCH].state;
            switchesArray[COCKING_HANDLE_SWITCH].lastChangeTime = now;
        }
    }

    // MOVEMENT_SWITCH
    else if (GPIO_Pin == SWITCHES_MOVEMENT_ALLOWED_Pin)
    {
        if ((now - switchesArray[MOVEMENT_SWITCH].lastChangeTime) >= DEBOUNCE_DELAY_MS)
        {
            switchesArray[MOVEMENT_SWITCH].state = HAL_GPIO_ReadPin(SWITCHES_MOVEMENT_ALLOWED_GPIO_Port, SWITCHES_MOVEMENT_ALLOWED_Pin);
            pandora.switches.switches_movement_allowed = switchesArray[MOVEMENT_SWITCH].state;
            switchesArray[MOVEMENT_SWITCH].lastChangeTime = now;
        }
    }

    // FIRE_ORDER_SWITCH
    else if (GPIO_Pin == SWITCHES_FIRE_ORDER_Pin)
    {
        if ((now - switchesArray[FIRE_ORDER_SWITCH].lastChangeTime) >= DEBOUNCE_DELAY_MS)
        {
            switchesArray[FIRE_ORDER_SWITCH].state = HAL_GPIO_ReadPin(SWITCHES_FIRE_ORDER_GPIO_Port, SWITCHES_FIRE_ORDER_Pin);
            pandora.switches.switches_fire_order = switchesArray[FIRE_ORDER_SWITCH].state;
            switchesArray[FIRE_ORDER_SWITCH].lastChangeTime = now;
        }
    }

    // SYSTEM_ON_OFF_SWITCH
    else if (GPIO_Pin == SWITCHES_SYSTEM_ON_OFF_Pin)
    {
        if ((now - switchesArray[SYSTEM_ON_OFF_SWITCH].lastChangeTime) >= DEBOUNCE_DELAY_MS)
        {
            switchesArray[SYSTEM_ON_OFF_SWITCH].state = HAL_GPIO_ReadPin(SWITCHES_SYSTEM_ON_OFF_GPIO_Port, SWITCHES_SYSTEM_ON_OFF_Pin);
            pandora.switches.switches_system_on_off = switchesArray[SYSTEM_ON_OFF_SWITCH].state;
            switchesArray[SYSTEM_ON_OFF_SWITCH].lastChangeTime = now;
        }
    }

    // SMGA_SWITCH
    else if (GPIO_Pin == SWITCHES_SMGA_Pin)
    {
        if ((now - switchesArray[SMGA_SWITCH].lastChangeTime) >= DEBOUNCE_DELAY_MS)
        {
            switchesArray[SMGA_SWITCH].state = HAL_GPIO_ReadPin(SWITCHES_SMGA_GPIO_Port, SWITCHES_SMGA_Pin);
            pandora.switches.switches_smga = switchesArray[SMGA_SWITCH].state;
            switchesArray[SMGA_SWITCH].lastChangeTime = now;
        }
    }

    // COCKING_HANDLE_HOME_SWITCH
    else if (GPIO_Pin == SWITCHES_COCKING_HANDLE_HOME_Pin)
    {
        if ((now - switchesArray[COCKING_HANDLE_HOME_SWITCH].lastChangeTime) >= DEBOUNCE_DELAY_MS)
        {
            switchesArray[COCKING_HANDLE_HOME_SWITCH].state = HAL_GPIO_ReadPin(SWITCHES_COCKING_HANDLE_HOME_GPIO_Port, SWITCHES_COCKING_HANDLE_HOME_Pin);
            pandora.switches.switches_cocking_handle_home = switchesArray[COCKING_HANDLE_HOME_SWITCH].state;
            switchesArray[COCKING_HANDLE_HOME_SWITCH].lastChangeTime = now;
        }
    }

    // CREW_1_SWITCH
    else if (GPIO_Pin == SWITCHES_CREW_1_Pin)
    {
        if ((now - switchesArray[CREW_1_SWITCH].lastChangeTime) >= DEBOUNCE_DELAY_MS)
        {
            switchesArray[CREW_1_SWITCH].state = HAL_GPIO_ReadPin(SWITCHES_CREW_1_GPIO_Port, SWITCHES_CREW_1_Pin);
            pandora.switches.switches_crew_1 = switchesArray[CREW_1_SWITCH].state;
            switchesArray[CREW_1_SWITCH].lastChangeTime = now;
        }
    }

    // CREW_2_SWITCH
    else if (GPIO_Pin == SWITCHES_CREW_2_Pin)
    {
        if ((now - switchesArray[CREW_2_SWITCH].lastChangeTime) >= DEBOUNCE_DELAY_MS)
        {
            switchesArray[CREW_2_SWITCH].state = HAL_GPIO_ReadPin(SWITCHES_CREW_2_GPIO_Port, SWITCHES_CREW_2_Pin);
            pandora.switches.switches_crew_2 = switchesArray[CREW_2_SWITCH].state;
            switchesArray[CREW_2_SWITCH].lastChangeTime = now;
        }
    }
}

void functionMeasure(void)
{
	pandora.powerManagement.solenoidCurrent 		= pandora.analogDigitalConverter.hadc3Buffer[2];
	pandora.powerManagement.cockingHandleCurrent 	= pandora.analogDigitalConverter.hadc3Buffer[0];
	pandora.powerManagement.servoCurrent 			= pandora.analogDigitalConverter.hadc2Buffer[1];
	pandora.powerManagement.AKBCurrent 				= pandora.analogDigitalConverter.hadc2Buffer[0];
	pandora.powerManagement.EOSCurrent 				= pandora.analogDigitalConverter.hadc1Buffer[0];
	pandora.powerManagement.GDBCurrent 				= pandora.analogDigitalConverter.hadc3Buffer[0];
	pandora.powerManagement.KKUCurrent 				= pandora.analogDigitalConverter.hadc1Buffer[1];
}








//
//digitalInput boardDigitalInputs[BUTTON_COUNT];			//OK
//
//void initDigitalInputs(digitalInput *digitalInputPtr)
//{
//	/****************************************************
//	***	CUSTOM VALUES SHOULD BE INITIALIZED MANUALLY	***
//	****************************************************/
//	boardDigitalInputs[0].inputPin 		= SWITCHES_SAFETY_Pin;
//	boardDigitalInputs[0].inputPort		= SWITCHES_SAFETY_GPIO_Port;
//	boardDigitalInputs[1].inputPin 		= SWITCHES_COCKING_HANDLE_ORDER_Pin;
//	boardDigitalInputs[1].inputPort		= SWITCHES_COCKING_HANDLE_ORDER_GPIO_Port;
//	boardDigitalInputs[2].inputPin 		= SWITCHES_MOVEMENT_ALLOWED_Pin;
//	boardDigitalInputs[2].inputPort		= SWITCHES_MOVEMENT_ALLOWED_GPIO_Port;
//	boardDigitalInputs[3].inputPin 		= SWITCHES_FIRE_ORDER_Pin;
//	boardDigitalInputs[3].inputPort		= SWITCHES_FIRE_ORDER_GPIO_Port;
//	boardDigitalInputs[4].inputPin 		= SWITCHES_SYSTEM_ON_OFF_Pin;
//	boardDigitalInputs[4].inputPort		= SWITCHES_SYSTEM_ON_OFF_GPIO_Port;
//	boardDigitalInputs[5].inputPin 		= SWITCHES_SMGA_Pin;
//	boardDigitalInputs[5].inputPort		= SWITCHES_SMGA_GPIO_Port;
//	boardDigitalInputs[6].inputPin 		= SWITCHES_COCKING_HANDLE_HOME_Pin;
//	boardDigitalInputs[6].inputPort		= SWITCHES_COCKING_HANDLE_HOME_GPIO_Port;
//	boardDigitalInputs[7].inputPin 		= SWITCHES_CREW_1_Pin;
//	boardDigitalInputs[7].inputPort		= SWITCHES_CREW_1_GPIO_Port;
//	boardDigitalInputs[8].inputPin 		= SWITCHES_CREW_2_Pin;
//	boardDigitalInputs[8].inputPort		= SWITCHES_CREW_2_GPIO_Port;
//
//
//	/***************************************************/
//		uint32_t i;
//		digitalInput* tempDigitalInputPtr = digitalInputPtr;
//
//		for(i = 0; i < COUNT_BUTTON; i++)
//		{
//			tempDigitalInputPtr	-> inputVal = GPIO_PIN_RESET;
//			tempDigitalInputPtr	-> readFlag = false;
//			tempDigitalInputPtr -> readState= GPIO_PIN_RESET;
//			tempDigitalInputPtr -> debounceTimer = 0;
//			//for prototype debounce factor
//			tempDigitalInputPtr	-> debounceFactor = 20; /*!!!!!!!!!!!!! config structtan cekilecek !!!!!!!!!!!!!!!!!*/
//			tempDigitalInputPtr++;
//		}
//
//}
//
//digitalInput* getDigitalInputs(void)
//{
//		return &boardDigitalInputs[0];
//}
//
//void readDigitalInputs(digitalInput *digitalInputPtr)
//{
//	uint32_t i;
//	digitalInput* tempDigitalInputPtr = digitalInputPtr;
//
//	for(i=0;i<COUNT_BUTTON;i++)
//	{
//		tempDigitalInputPtr -> inputVal = HAL_GPIO_ReadPin(tempDigitalInputPtr->inputPort, tempDigitalInputPtr->inputPin);
//		tempDigitalInputPtr	-> readFlag = true;
//		tempDigitalInputPtr++;
//	}
//}
//
//void sampleDigitalInputs(digitalInput *digitalInputPtr)
//{
//	uint32_t i;
//	digitalInput* tempDigitalInputPtr = digitalInputPtr;
//
//	for(i = 0; i < COUNT_BUTTON; i++)
//	{
//		if(tempDigitalInputPtr -> readFlag == true)
//		{
//			if(tempDigitalInputPtr -> readState == GPIO_PIN_RESET)
//			{
//				if(tempDigitalInputPtr -> inputVal == GPIO_PIN_RESET)
//				{
//					if(tempDigitalInputPtr -> debounceTimer < tempDigitalInputPtr -> debounceFactor)
//					{
//						tempDigitalInputPtr -> debounceTimer++;
//					}
//					if(tempDigitalInputPtr ->debounceTimer >= tempDigitalInputPtr ->debounceFactor)
//					{
//						tempDigitalInputPtr -> debounceTimer = 0;
//						tempDigitalInputPtr -> readState = GPIO_PIN_SET;
//					}
//				}
//				else
//				{
//					tempDigitalInputPtr -> debounceTimer = 0;
//				}
//			}
//
//			else if(tempDigitalInputPtr -> readState == GPIO_PIN_SET)
//			{
//				if(tempDigitalInputPtr -> inputVal == GPIO_PIN_SET)
//				{
//					if(tempDigitalInputPtr -> debounceTimer < tempDigitalInputPtr -> debounceFactor)
//					{
//						tempDigitalInputPtr -> debounceTimer++;
//					}
//					if(tempDigitalInputPtr ->debounceTimer >= tempDigitalInputPtr ->debounceFactor)
//					{
//						tempDigitalInputPtr -> debounceTimer = 0;
//						tempDigitalInputPtr -> readState = GPIO_PIN_RESET;
//					}
//				}
//				else
//				{
//					tempDigitalInputPtr -> debounceTimer = 0;
//				}
//			}
//
//			tempDigitalInputPtr   ->  readFlag = false;
//
//			tempDigitalInputPtr++;
//		}
//	}
//}









//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
//    uint32_t now = HAL_GetTick();
//
//    for (int i = 0; i < SWITCHES_COUNT; i++)
//    {
//        if (switchesArray[i].pin == GPIO_Pin)	// Bu pin başka portta olabilir. Okuyarak karşılaştır.
//        {
//            if ((now - switchesArray[i].lastChangeTime) >= DEBOUNCE_DELAY_MS)
//            {
//                if (HAL_GPIO_ReadPin(switchesArray[i].port, switchesArray[i].pin) == GPIO_PIN_SET)
//                	switchesArray[i].state = HIGH;
//                else
//                	switchesArray[i].state = LOW;
//
//                switchesArray[i].lastChangeTime = now;
//            }
//        }
//    }
//}
