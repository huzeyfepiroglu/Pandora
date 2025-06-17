/*
 * peripherals.c
 *
 *  Created on: May 13, 2025
 *      Author: Abdullah Huzeyfe Piroğlu
 */

#include "peripherals.h"

Switches_t switches_array[SWITCHES_COUNT] =
{
    [S_SMGA] 				= {SWITCHES_SMGA_GPIO_Port					, SWITCHES_SMGA_Pin		 				, LOW , 0},
    [S_2] 					= {SWITCHES_2_GPIO_Port						, SWITCHES_2_Pin 						, LOW , 0},
    [S_4] 					= {SWITCHES_4_GPIO_Port						, SWITCHES_4_Pin 						, LOW , 0},
    [S_5] 					= {SWITCHES_5_GPIO_Port						, SWITCHES_5_Pin 						, LOW , 0},
    [S_6] 					= {SWITCHES_6_GPIO_Port						, SWITCHES_6_Pin 						, LOW , 0},
    [S_7] 					= {SWITCHES_7_GPIO_Port						, SWITCHES_7_Pin 						, LOW , 0},
	[S_FIRE_FEEDBACK] 		= {SWITCHES_FIRE_FEEDBACK_GPIO_Port			, SWITCHES_FIRE_FEEDBACK_Pin	 		, LOW , 0},
    [S_SAFETY_FEEDBACK]		= {SWITCHES_SAFETY_FEEDBACK_GPIO_Port		, SWITCHES_SAFETY_FEEDBACK_Pin	 		, LOW , 0},
	[S_COCKING_HANDLE_HOME]	= {SWITCHES_COCKING_HANDLE_HOME_GPIO_Port	, SWITCHES_COCKING_HANDLE_HOME_Pin	 	, LOW , 0},
};

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    uint32_t now = HAL_GetTick();

    for (int i = 0; i < SWITCHES_COUNT; i++)
    {
        if (switches_array[i].pin == GPIO_Pin)	// Bu pin başka portta olabilir. Okuyarak karşılaştır.
        {
            if ((now - switches_array[i].lastChangeTime) >= DEBOUNCE_DELAY_MS)
            {
                if (HAL_GPIO_ReadPin(switches_array[i].port, switches_array[i].pin) == GPIO_PIN_SET)
                	switches_array[i].state = HIGH;
                else
                	switches_array[i].state = LOW;

                switches_array[i].lastChangeTime = now;
            }
        }
    }
}

