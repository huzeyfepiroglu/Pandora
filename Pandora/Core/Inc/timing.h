/*
 * 	timing.h
 *
 *  Created on	: February 12, 2025
 *  Company		: ASELSAN KONYA
 *  Author		: ABDULLAH HUZEYFE PIROGLU
 *
 */

#ifndef INC_TIMING_H_
#define INC_TIMING_H_

#include "main.h"
#include "stdbool.h"
#include "definitions.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void startTimeScanFlags(void);
void clearTimeScanFlags(void);

extern bool _configurableFlag;
extern bool _1msFlag;
extern bool _10msFlag;
extern bool _25msFlag;
extern bool _50msFlag;
extern bool _100msFlag;
extern bool _250msFlag;
extern bool _500msFlag;
extern bool _1sFlag;
extern bool _10sFlag;

#endif /* INC_TIMING_H_ */
