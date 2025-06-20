/*
 * cocking_handle_main.c
 *
 *  Created on: Jan 24, 2025
 *      Author: ADMIN
 */


#include "peripherals.h"
#include "definitions.h"
#include "cocking_handle_maingun.h"

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
	if(!pandora.switches.switches_cocking_handle_home)
	{
		maingunCockingMotorBrake(OFF);

		do
		{
			maingunCockingMotorDrive(BACKWARD);
		}
		while(pandora.switches.switches_cocking_handle_home);

		maingunCockingMotorStop();
		maingunCockingMotorBrake(ON);
	}
}

void maingunCockingHandleGoSafe (void)
{
	if(!pandora.switches.switches_cocking_handle_home)
	{
		maingunCockingMotorBrake(OFF);

		do
		{
			maingunCockingMotorDrive(BACKWARD);
		}
		while(pandora.switches.switches_cocking_handle_home);

		maingunCockingMotorStop();
		maingunCockingMotorBrake(ON);
	}

	if(pandora.switches.switches_cocking_handle_home)
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
	if(!pandora.switches.switches_cocking_handle_home)
	{
		maingunCockingMotorBrake(OFF);

		do
		{
			maingunCockingMotorDrive(BACKWARD);
		}
		while(pandora.switches.switches_cocking_handle_home);

		maingunCockingMotorStop();
		maingunCockingMotorBrake(ON);
	}

	if(pandora.switches.switches_cocking_handle_home)
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

	if(!pandora.switches.switches_cocking_handle_home)
	{
		maingunCockingMotorBrake(OFF);

		do
		{
			maingunCockingMotorDrive(BACKWARD);
		}
		while(pandora.switches.switches_cocking_handle_home);


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

	if(pandora.switches.switches_cocking_handle_home)
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
