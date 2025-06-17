/*
 * cocking_handle_main.c
 *
 *  Created on: Jan 24, 2025
 *      Author: ADMIN
 */


#include "peripherals.h"
#include "definitions.h"
#include "cocking_handle_maingun.h"
/*


+---------+---------+---------+---------+---------+---------+---------+---------+---------+
|   BITS  |    7    |    6    |    5    |    4    |    3    |    2    |    1    |    0    |
+---------+---------+---------+---------+---------+---------+---------+---------+---------+
| MGCHR_01|    X    |    X    |    X    |MG_MOT_ST|MG_MOT_RL|MG_MOT_LH|MG_MOT_LL|MG_MOT_RH|    MAIN GUN COCKING HANDLE REGISTER 01
+---------+---------+---------+---------+---------+---------+---------+---------+---------+
|   SGCH  |    X    |    X    |    X    |    X    |    X    |    X    |    X    |    X    |    SUPPORT GUN COCKING HANDLE
+---------+---------+---------+---------+---------+---------+---------+---------+---------+
|   MGCH  |    X    |    X    |    X    |    X    |    X    |    X    |    X    |    X    |    MAIN GUN COCKING HANDLE
+---------+---------+---------+---------+---------+---------+---------+---------+---------+
|   MGCH  |    X    |    X    |    X    |    X    |    X    |    X    |    X    |    X    |    MAIN GUN COCKING HANDLE
+---------+---------+---------+---------+---------+---------+---------+---------+---------+
|   MGCH  | D  X    |    X    |    X    |    X    |    X    |    X    |    X    |    X    |    MAIN GUN COCKING HANDLE
+---------+---------+---------+---------+---------+---------+---------+---------+---------+

*/

// global structer
extern pandoraStructer pandora;

// variables needed for just cocking_handle_maingun.c not global
int32_t lastCount = 0;

void maingunCockingMotorDrive(bool direction)
{
	if(direction == FORWARD)
	{
		MOTOR_CONTROL(COCKING_HANDLE_DRV_H_BACKWARD,OFF);
		MOTOR_CONTROL(COCKING_HANDLE_DRV_H_FORWARD,ON);

		pandora.gun.cockingHandle.motorState = FORWARD;
	}
	else if(direction == BACKWARD)
	{
		MOTOR_CONTROL(COCKING_HANDLE_DRV_H_FORWARD,OFF);
		MOTOR_CONTROL(COCKING_HANDLE_DRV_H_BACKWARD,ON);

		pandora.gun.cockingHandle.motorState = BACKWARD;
	}
}

void maingunCockingMotorBrake (bool state)
{
	if(state == ON)
	{
		MOTOR_CONTROL(BRAKE_DRV_28V,ON);
	}
	else if (state == OFF)
	{
		MOTOR_CONTROL(BRAKE_DRV_28V,OFF);
	}

}

void maingunCockingMotorStop(void)
{
	MOTOR_CONTROL(COCKING_HANDLE_DRV_H_BACKWARD,OFF);
	MOTOR_CONTROL(COCKING_HANDLE_DRV_H_FORWARD,OFF);

	pandora.gun.cockingHandle.motorState = IDLE;
}

void maingunCockingHandleGoHome (void)
{
	if(!SWITCH_READ(SWITCHES_COCKING_HANDLE_HOME))
	{
		maingunCockingMotorBrake(OFF);

		do
		{
			maingunCockingMotorDrive(BACKWARD);
		}
		while(SWITCH_READ(SWITCHES_COCKING_HANDLE_HOME));

		maingunCockingMotorStop();
		maingunCockingMotorBrake(ON);
	}
}

void maingunCockingHandleGoSafe (void)
{
	if(!SWITCH_READ(SWITCHES_COCKING_HANDLE_HOME))
	{
		maingunCockingMotorBrake(OFF);

		do
		{
			maingunCockingMotorDrive(BACKWARD);
		}
		while(SWITCH_READ(SWITCHES_COCKING_HANDLE_HOME));

		maingunCockingMotorStop();
		maingunCockingMotorBrake(ON);
	}

	if(SWITCH_READ(SWITCHES_COCKING_HANDLE_HOME))
	{
		maingunCockingMotorBrake(OFF);

		do
		{
			maingunCockingMotorDrive(FORWARD);
		}
		while(!maingunCountEncoderPulse(SAFE_POSITION));

		maingunCockingMotorStop();
		maingunCockingMotorBrake(ON);
	}
}

void maingunCockingHandleGoArm (void)
{
	if(!SWITCH_READ(SWITCHES_COCKING_HANDLE_HOME))
	{
		maingunCockingMotorBrake(OFF);

		do
		{
			maingunCockingMotorDrive(BACKWARD);
		}
		while(SWITCH_READ(SWITCHES_COCKING_HANDLE_HOME));

		maingunCockingMotorStop();
		maingunCockingMotorBrake(ON);
	}

	if(SWITCH_READ(SWITCHES_COCKING_HANDLE_HOME))
	{
		maingunCockingMotorBrake(OFF);

		do
		{
			maingunCockingMotorDrive(FORWARD);
		}
		while(!maingunCountEncoderPulse(ARM_POSITION));

		maingunCockingMotorStop();
		maingunCockingMotorBrake(ON);
	}

	if(!SWITCH_READ(SWITCHES_COCKING_HANDLE_HOME))
	{
		maingunCockingMotorBrake(OFF);

		do
		{
			maingunCockingMotorDrive(BACKWARD);
		}
		while(SWITCH_READ(SWITCHES_COCKING_HANDLE_HOME));


		maingunCockingMotorStop();
		maingunCockingMotorBrake(ON);
	}
}

bool maingunCountEncoderPulse(uint32_t position)
{
	if(pandora.gun.cockingHandle.encoderCounter <= position)								// main içerisinde maingunEncoderCounter saymalı..! OK #huzeyfe
		return true;
	else
		return false;
}

void maingunEncoderRead(TIM_HandleTypeDef *htim)
{
	int32_t currentCount = __HAL_TIM_GET_COUNTER(htim);
	int32_t difference = currentCount - lastCount;

	if(SWITCH_READ(SWITCHES_COCKING_HANDLE_HOME))
	{
		currentCount = 0;
	}

	if(difference > 0)
	{
		pandora.gun.cockingHandle.encoderRotation = FORWARD;
		pandora.gun.cockingHandle.encoderCounter += difference;
	}

	else if (difference < 0)
	{
		pandora.gun.cockingHandle.encoderRotation = BACKWARD;
		pandora.gun.cockingHandle.encoderCounter += difference;

	}

	lastCount = currentCount;
}
