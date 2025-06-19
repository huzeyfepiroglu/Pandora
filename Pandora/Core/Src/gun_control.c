/*
 * gun_control.c
 *
 *  Created on: Jan 22, 2025
 *      Author: ADMIN
 */

#include "peripherals.h"
#include "definitions.h"
#include "gun_control.h"

// global structer
extern pandoraStructer pandora;


#include "gun_control.h"

uint16_t HIZLI_RPM = 600;
uint16_t YAVAS_RPM = 200;
uint16_t SOLENOID_ACILMA_SURESI = 50;
uint16_t SOLENOID_AKTIF_SURESI = 30;
uint16_t SOLENOID_PASIF_SURESI = 90;

volatile uint32_t ammoCounter = 0;

static FireMode_t currentMode = FIRE_MODE_SINGLE;
static bool triggerHeld = false;
static uint8_t burstCounter = 0;
static bool solenoidActive = false;
static uint32_t stateChangeTime = 0;

extern void Solenoid_On(void);
extern void Solenoid_Off(void);

static uint32_t get_shot_interval(uint16_t rpm)
{
    return 60000 / rpm;
}

void Gun_Init(void)
{
    Solenoid_Off();
    solenoidActive = false;
    triggerHeld = false;
    burstCounter = 0;
    stateChangeTime = 0;
}

void Gun_SetMode(FireMode_t mode)
{
    currentMode = mode;
}

void Gun_TriggerPressed(void)
{
    triggerHeld = true;
    burstCounter = 0;
    stateChangeTime = HAL_GetTick();

    if (currentMode == FIRE_MODE_SINGLE)
    {
        Solenoid_On();
        solenoidActive = true;
    }
    else if (currentMode == FIRE_MODE_FAST_BURST_3 || currentMode == FIRE_MODE_FAST_BURST_5)
    {
        solenoidActive = true;
        Solenoid_On();
    }
}

void Gun_TriggerReleased(void)
{
    triggerHeld = false;
    solenoidActive = false;
    burstCounter = 0;
    Solenoid_Off();
}

void Gun_Process(uint32_t now)
{
    if (!triggerHeld && currentMode != FIRE_MODE_SINGLE) return;

    switch (currentMode)
    {
        case FIRE_MODE_SINGLE:
            if (solenoidActive && now - stateChangeTime >= SOLENOID_ACILMA_SURESI)
            {
                Solenoid_Off();
                solenoidActive = false;
                ammoCounter++;
            }
            break;

        case FIRE_MODE_FAST_AUTO:
            if (solenoidActive && now - stateChangeTime >= SOLENOID_AKTIF_SURESI)
            {
                Solenoid_Off();
                solenoidActive = false;
                ammoCounter++;
                stateChangeTime = now;
            }
            else if (!solenoidActive && now - stateChangeTime >= SOLENOID_PASIF_SURESI)
            {
                Solenoid_On();
                solenoidActive = true;
                stateChangeTime = now;
            }
            break;

        case FIRE_MODE_FAST_BURST_3:
        case FIRE_MODE_FAST_BURST_5:
        {
            uint8_t target = (currentMode == FIRE_MODE_FAST_BURST_3) ? 3 : 5;
            uint32_t burst_duration = get_shot_interval(HIZLI_RPM) * target;

            if (solenoidActive && now - stateChangeTime >= burst_duration)
            {
                Solenoid_Off();
                solenoidActive = false;
                ammoCounter += target;
            }
            break;
        }

        case FIRE_MODE_SLOW_AUTO:
            if (!solenoidActive && now - stateChangeTime >= get_shot_interval(YAVAS_RPM))
            {
                Solenoid_On();
                solenoidActive = true;
                stateChangeTime = now;
            }
            else if (solenoidActive && now - stateChangeTime >= SOLENOID_ACILMA_SURESI)
            {
                Solenoid_Off();
                solenoidActive = false;
                ammoCounter++;
                stateChangeTime = now;
            }
            break;

        case FIRE_MODE_SLOW_BURST_3:
        case FIRE_MODE_SLOW_BURST_5:
        {
            uint8_t target = (currentMode == FIRE_MODE_SLOW_BURST_3) ? 3 : 5;
            if (burstCounter >= target) break;

            if (!solenoidActive && now - stateChangeTime >= get_shot_interval(YAVAS_RPM))
            {
                Solenoid_On();
                solenoidActive = true;
                stateChangeTime = now;
            }
            else if (solenoidActive && now - stateChangeTime >= SOLENOID_ACILMA_SURESI)
            {
                Solenoid_Off();
                solenoidActive = false;
                ammoCounter++;
                burstCounter++;
                stateChangeTime = now;
            }
            break;
        }

        default:
            break;
    }
}



//Gun_Init();
//Gun_SetMode(FIRE_MODE_FAST_AUTO);
//
//while (1) {
//    Gun_Process(HAL_GetTick());
//
//    if (TetikBasildi()) {
//        Gun_TriggerPressed();
//    } else {
//        Gun_TriggerReleased();
//    }
//}
