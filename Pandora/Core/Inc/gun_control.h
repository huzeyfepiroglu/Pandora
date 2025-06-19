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

// Global parametreler
extern uint16_t HIZLI_RPM;
extern uint16_t YAVAS_RPM;
extern uint16_t SOLENOID_ACILMA_SURESI;   // ms
extern uint16_t SOLENOID_AKTIF_SURESI;    // ms
extern uint16_t SOLENOID_PASIF_SURESI;    // ms

extern volatile uint32_t boncuk_sayaci;

void Gun_Init(void);
void Gun_SetMode(FireMode_t mode);
void Gun_TriggerPressed(void);
void Gun_TriggerReleased(void);
void Gun_Process(uint32_t now_ms);

#endif /* INC_GUN_CONTROL_H_ */
