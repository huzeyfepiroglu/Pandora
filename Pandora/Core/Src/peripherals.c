/*
 * peripherals.c
 *
 *  Created on: May 13, 2025
 *      Author: Abdullah Huzeyfe Piroğlu
 */

#include "peripherals.h"

Switches_t switchesArray[SWITCHES_COUNT] =
{
	[FIRE_SAFETY_SWITCH] 	= {SWITCHES_SAFETY_FEEDBACK_GPIO_Port , SWITCHES_SAFETY_FEEDBACK_Pin , LOW , 0},
	[COCKING_HANDLE_SWITCH]	= {SWITCHES_COCKING_HANDLE_GPIO_Port  , SWITCHES_COCKING_HANDLE_Pin  , LOW , 0},
	[MOVEMENT_SWITCH] 		= {MOVEMENT_SWITCH_GPIO_Port		  , MOVEMENT_SWITCH_Pin 		 , LOW , 0},
	[FIRE_ORDER_SWITCH] 	= {FIRE_ORDER_SWITCH_GPIO_Port		  , FIRE_ORDER_SWITCH_Pin 		 , LOW , 0},
	[SYSTEM_ON_OFF_SWITCH] 	= {SYSTEM_ON_OFF_SWITCH_GPIO_Port	  , SYSTEM_ON_OFF_SWITCH_Pin 	 , LOW , 0},
	[SMGA_SWITCH]			= {SMGA_SWITCH_GPIO_Port			  , SMGA_SWITCH_Pin 			 , LOW , 0},
	[CREW_1_SWITCH] 		= {CREW_1_SWITCH_GPIO_Port			  , CREW_1_SWITCH_Pin	 		 , LOW , 0},
	[CREW_2_SWITCH]			= {CREW_2_SWITCH_GPIO_Port			  , CREW_2_SWITCH_Pin	 		 , LOW , 0},
	[CREW_3_SWITCH]			= {CREW_3_SWITCH_GPIO_Port			  , CREW_3_SWITCH_Pin	 		 , LOW , 0},
};

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    uint32_t now = HAL_GetTick();

    for (int i = 0; i < SWITCHES_COUNT; i++)
    {
        if (switchesArray[i].pin == GPIO_Pin)	// Bu pin başka portta olabilir. Okuyarak karşılaştır.
        {
            if ((now - switchesArray[i].lastChangeTime) >= DEBOUNCE_DELAY_MS)
            {
                if (HAL_GPIO_ReadPin(switchesArray[i].port, switchesArray[i].pin) == GPIO_PIN_SET)
                	switchesArray[i].state = HIGH;
                else
                	switchesArray[i].state = LOW;

                switchesArray[i].lastChangeTime = now;
            }
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
