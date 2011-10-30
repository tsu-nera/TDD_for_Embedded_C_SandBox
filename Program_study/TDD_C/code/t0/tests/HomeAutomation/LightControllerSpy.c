/*
 * LightControllerSpy.c
 *
 *  Created on: 2011/10/30
 *      Author: TSUNEMICHI
 */

#include "LightController.h"

static int lastId;
static int lastState;


void LightController_Create(void)
{
	lastId    = LIGHT_ID_UNKNOWN;
	lastState = LIGHT_STATE_UNKNOWN;
}
