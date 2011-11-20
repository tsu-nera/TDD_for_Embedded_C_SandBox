/*
 * LightControllerSpy.h
 *
 *  Created on: 2011/10/30
 *      Author: TSUNEMICHI
 */

#ifndef LIGHTCONTROLLERSPY_H_
#define LIGHTCONTROLLERSPY_H_

#include "LightController.h"

enum
{
	LIGHT_ID_UNKNOWN = -1, LIGHT_STATE_UNKNOWN = -1,
	LIGHT_OFF = 0, LIGHT_ON = 1
};

void LightController_On(int id);
void LightController_Off(int id);
int LightControllerSpy_GetLastId(void);
int LightControllerSpy_GetLastState(void);
int LightControllerSpy_GetLightState(int id);
void LightScheduler_Wakeup(void);
void LightController_Destroy(void);

#endif /* LIGHTCONTROLLERSPY_H_ */
