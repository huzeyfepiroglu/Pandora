/*
 * cocking_handle_maingun.h
 *
 *  Created on: Jan 24, 2025
 *      Author: ADMIN
 */

#ifndef INC_COCKING_HANDLE_MAINGUN_H_
#define INC_COCKING_HANDLE_MAINGUN_H_

void functionCockingMotorDrive(bool direction);
void functionCockingMotorBrake (bool state);
void functionCockingMotorStop(void);
void functionCockingHandleGoHome (void);
void functionCockingHandleGoSafe (void);
void functionCockingHandleGoArm (void);
bool functionCountEncoderPulse(uint32_t position);
void functionEncoderRead(TIM_HandleTypeDef *htim);

#endif /* INC_COCKING_HANDLE_MAINGUN_H_ */
