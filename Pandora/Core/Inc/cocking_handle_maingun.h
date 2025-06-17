/*
 * cocking_handle_maingun.h
 *
 *  Created on: Jan 24, 2025
 *      Author: ADMIN
 */

#ifndef INC_COCKING_HANDLE_MAINGUN_H_
#define INC_COCKING_HANDLE_MAINGUN_H_

void maingunCockingMotorDrive(bool direction);
void maingunCockingMotorBrake (bool state);
void maingunCockingMotorStop(void);
void maingunCockingHandleGoHome (void);
void maingunCockingHandleGoSafe (void);
void maingunCockingHandleGoArm (void);
bool maingunCountEncoderPulse(uint32_t position);
void maingunEncoderRead(TIM_HandleTypeDef *htim);

#endif /* INC_COCKING_HANDLE_MAINGUN_H_ */
