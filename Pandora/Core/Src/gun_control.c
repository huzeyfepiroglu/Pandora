/*
 * gun_control.c
 *
 *  Created on: Jan 22, 2025
 *      Author: ADMIN
 */

#include "gun_control.h"
#include "peripherals.h"
#include "definitions.h"

// global structer
extern pandoraStructer pandora;


/*
 * option:
 * 0: viaSwitches
 * 1: viaCanbus
 *
 * +---------+---------+---------+---------+
 * |    3    |    2    |    1    |    0    |   GUN SWITCHES
 * +---------+---------+---------+---------+
 * |    0    |    0    |    0    |    1    |   GUN MK19
 * +---------+---------+---------+---------+
 * |    0    |    0    |    1    |    0    |   GUN MAKS OBA 40
 * +---------+---------+---------+---------+
 * |    0    |    1    |    0    |    0    |   GUN 5.56
 * +---------+---------+---------+---------+
 * |    1    |    0    |    0    |    0    |   GUN 7.62
 * +---------+---------+---------+---------+
 *
 */

void checkGunType (bool option)
{
	if (option)
	{
//		pandora.gun.mode.gunMK19 	= pandora.switches.gunType_1;
//		pandora.gun.mode.gunMAKS40 	= pandora.switches.gunType_2;
//		pandora.gun.mode.gun556 	= pandora.switches.gunType_3;
//		pandora.gun.mode.gun762 	= pandora.switches.gunType_4;
	}

	else
	{
//		pandora.gun.mode.gunMK19 	= pandora.AKB.mode
//		pandora.gun.mode.gunMAKS40 	= pandora.AKB.gunMode >> 2;
//		pandora.gun.mode.gun556 	= pandora.AKB.gunMode >> 1;
//		pandora.gun.mode.gun762 	= pandora.AKB.gunMode >> 0;
	}

}
