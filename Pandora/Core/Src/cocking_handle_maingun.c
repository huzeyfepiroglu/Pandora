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

void functionCockingMotorDrive(bool direction)
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

void functionCockingMotorBrake (bool state)
{
	if(state == ON)
	{
		MOTOR_CONTROL(BRAKE_DRV_28V,ON);
		pandora.gun.cockingHandle.brakeState = ON;
	}
	else if (state == OFF)
	{
		MOTOR_CONTROL(BRAKE_DRV_28V,OFF);
		pandora.gun.cockingHandle.brakeState = OFF;
	}

}

void functionCockingMotorStop(void)
{
	MOTOR_CONTROL(COCKING_HANDLE_DRV_H_BACKWARD,OFF);
	MOTOR_CONTROL(COCKING_HANDLE_DRV_H_FORWARD,OFF);

	pandora.gun.cockingHandle.motorState = IDLE;
}

void functionCockingHandleGoHome (void)
{
	if(!pandora.switches.switches_cocking_handle_home)
	{
		functionCockingMotorBrake(OFF);

		do
		{
			functionCockingMotorDrive(BACKWARD);
		}
		while(pandora.switches.switches_cocking_handle_home);

		functionCockingMotorStop();
		functionCockingMotorBrake(ON);
	}

	pandora.gun.cockingHandle.safe  = false;
	pandora.gun.cockingHandle.home  = true;
}

void functionCockingHandleGoSafe (void)
{
	if(!pandora.switches.switches_cocking_handle_home)
	{
		functionCockingMotorBrake(OFF);

		do
		{
			functionCockingMotorDrive(BACKWARD);
		}
		while(pandora.switches.switches_cocking_handle_home);

		functionCockingMotorStop();
		functionCockingMotorBrake(ON);
	}

	if(pandora.switches.switches_cocking_handle_home)
	{
		functionCockingMotorBrake(OFF);

		do
		{
			functionCockingMotorDrive(FORWARD);
		}
		while(!functionCountEncoderPulse(SAFE_POSITION));

		functionCockingMotorStop();
		functionCockingMotorBrake(ON);
	}

	pandora.gun.cockingHandle.armed = false;
	pandora.gun.cockingHandle.safe  = true;
	pandora.gun.cockingHandle.home  = true;
}

void functionCockingHandleGoArm (void)
{
	if(!pandora.switches.switches_cocking_handle_home)
	{
		functionCockingMotorBrake(OFF);

		do
		{
			functionCockingMotorDrive(BACKWARD);
		}
		while(pandora.switches.switches_cocking_handle_home);

		functionCockingMotorStop();
		functionCockingMotorBrake(ON);
	}

	if(pandora.switches.switches_cocking_handle_home)
	{
		functionCockingMotorBrake(OFF);

		do
		{
			functionCockingMotorDrive(FORWARD);
		}
		while(!functionCountEncoderPulse(ARM_POSITION));

		functionCockingMotorStop();
		functionCockingMotorBrake(ON);
	}

	if(!pandora.switches.switches_cocking_handle_home)
	{
		functionCockingMotorBrake(OFF);

		do
		{
			functionCockingMotorDrive(BACKWARD);
		}
		while(pandora.switches.switches_cocking_handle_home);


		functionCockingMotorStop();
		functionCockingMotorBrake(ON);
	}

	pandora.gun.cockingHandle.armed = true;
	pandora.gun.cockingHandle.safe  = false;
	pandora.gun.cockingHandle.home  = true;
}

bool functionCountEncoderPulse(uint32_t position)
{
	if(pandora.gun.cockingHandle.encoderCounter <= position)								// main içerisinde functionEncoderCounter saymalı..! OK #huzeyfe
		return true;
	else
		return false;
}

void functionEncoderRead(TIM_HandleTypeDef *htim)
{
	int32_t currentCount = __HAL_TIM_GET_COUNTER(htim);
	int32_t difference = currentCount - lastCount;

	if(pandora.switches.switches_cocking_handle_home)
	{
		currentCount = 0;
		lastCount = 0;

		return;
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
