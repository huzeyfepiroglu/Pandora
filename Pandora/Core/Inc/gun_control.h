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

void functionGunControlInit(void);
void functionGunControlTriggerReleased(void);
void functionGunControlTriggerPressed(void);
void functionGunControlProcess(uint32_t now);

#endif /* INC_GUN_CONTROL_H_ */
