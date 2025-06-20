/*
 * gun_control.h
 *
 *  Created on: May 12, 2025
 *      Author: ADMIN
 */

#ifndef INC_GUN_CONTROL_H_
#define INC_GUN_CONTROL_H_

#include "main.h"

#include <stdint.h>
#include <stdbool.h>

void gunControl_Init(void);
void gunControl_SetMode(FireMode_t mode);
void gunControl_TriggerPressed(void);
void gunControl_TriggerReleased(void);
void gunControl_Process(uint32_t now_ms);

#endif /* INC_GUN_CONTROL_H_ */
