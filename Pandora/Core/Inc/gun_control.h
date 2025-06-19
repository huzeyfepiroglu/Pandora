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

// Atış Modları
typedef enum {
    FIRE_MODE_SINGLE,
    FIRE_MODE_FAST_AUTO,
    FIRE_MODE_FAST_BURST_3,
    FIRE_MODE_FAST_BURST_5,
    FIRE_MODE_SLOW_AUTO,
    FIRE_MODE_SLOW_BURST_3,
    FIRE_MODE_SLOW_BURST_5
} FireMode_t;

void gunControl_Init(void);
void gunControl_SetMode(FireMode_t mode);
void gunControl_TriggerPressed(void);
void gunControl_TriggerReleased(void);
void gunControl_Process(uint32_t now_ms);

#endif /* INC_GUN_CONTROL_H_ */
