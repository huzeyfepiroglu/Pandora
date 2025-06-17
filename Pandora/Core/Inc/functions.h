/*
 * functions.h
 *
 *  Created on: Jan 8, 2025
 *      Author: ADMIN
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "stdint.h"
#include "stdbool.h"

typedef struct {
    uint8_t solenoidID;		// 0000:CheckVal 0000: Read/Write
    uint8_t deviceID;		// 00000000: Device ID
    uint8_t msgType;		// it should be remove
    uint8_t dataLength;		//
    uint8_t uartData[8];
    uint8_t endKey;
    uint8_t uartCRC[4];
} solenoid;

typedef struct {
    uint16_t number;
    uint32_t value;
} armMechanism;

typedef struct {
    uint8_t number;
    uint32_t value;
} directionSelectionMechanism;


typedef struct {
    bool powerState;
    uint8_t ID[8];

    struct
	{
    	bool state;
	};
} fogMortar;

typedef struct {
    uint8_t type;
    uint16_t parameterNumber;
    uint8_t functionNumber;
} pantilt;

typedef struct {
    bool type[3];
    uint16_t parameterNumber;
    uint8_t functionNumber;
} fogMortaraaa;

typedef struct {
	solenoid solenoid;
	armMechanism armMechanism;
	directionSelectionMechanism directionSelectionMechanism;
	fogMortar fogMortar;
	pantilt pantilt;
} denemeS;

extern denemeS deneme;

void funcSolenoid(uint8_t *data);
void funcAddEvent(uint8_t *data, uint8_t dataLenght);
void funcFogMortar(uint8_t *data);
void funcArmMechanism(uint8_t *data);
void funcDirectionSelectionMechanism(uint8_t *data);


#endif /* FUNCTIONS_H_ */
