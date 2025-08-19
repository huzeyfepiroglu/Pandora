/*
 * power_management.h
 *
 *  Created on: May 16, 2025
 *      Author: ADMIN
 */

#ifndef INC_POWER_MANAGEMENT_H_
#define INC_POWER_MANAGEMENT_H_

#define AMPER_1 	1
#define AMPER_5		5
#define AMPER_10	10
#define AMPER_15	15
#define AMPER_20	20
#define AMPER_25	25
#define VOLT_22		22
#define VOLT_28		28

void functionMeasureVoltage(void);
void functionMeasureCurrent(void);
void functionErrorCurrentVoltageCheck (void);

#endif /* INC_POWER_MANAGEMENT_H_ */
