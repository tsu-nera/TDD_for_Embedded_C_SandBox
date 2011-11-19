/*- ------------------------------------------------------------------ -*/
/*-    Copyright (c) James W. Grenning -- All Rights Reserved          -*/
/*-    For use by owners of Test-Driven Development for Embedded C,    -*/
/*-    and attendees of Renaissance Software Consulting, Co. training  -*/
/*-    classes.                                                        -*/
/*-                                                                    -*/
/*-    Available at http://pragprog.com/titles/jgade/                  -*/
/*-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3                -*/
/*-                                                                    -*/
/*-    Authorized users may use this source code in your own           -*/
/*-    projects, however the source code may not be used to            -*/
/*-    create training material, courses, books, articles, and         -*/
/*-    the like. We make no guarantees that this source code is        -*/
/*-    fit for any purpose.                                            -*/
/*-                                                                    -*/
/*-    www.renaissancesoftware.net james@renaissancesoftware.net       -*/
/*- ------------------------------------------------------------------ -*/


#if TEST_PATH

#include "LightControllerSpy.h"
#include "memory.h"



static int lastId;
static int lastLevel;
static int count;
static int lights[MAX_LIGHTS];

void LightController_Create(void)
{
		lastId = LIGHT_ID_UNKNOWN;
		lastLevel = LIGHT_STATE_UNKNOWN;
		count = 0;
		memset(lights, LIGHT_STATE_UNKNOWN, sizeof lights);
}

void LightController_Destroy(void)
{
}

int LightControllerSpy_GetLastId(void)
{
		return lastId;
}

int LightControllerSpy_GetLastState(void)
{
		return lastLevel;
}

static int isIdInRange(int id)
{
		return id > 0 && id <=32;
}
void LightController_TurnOn(int id)
{
		lastId = id;
		lastLevel = 1;
		count++;
		if (isIdInRange(id))
				lights[id-1] = LIGHT_ON;
}

void LightController_TurnOff(int id)
{
		lastId = id;
		lastLevel = 0;
		count++;
		if (isIdInRange(id))
				lights[id-1] = LIGHT_OFF;
}

int LightControllerSpy_GetEventCounts(void)
{
		return count;
}

LightState LightControllerSpy_GetLightState(int id)
{
		if (!isIdInRange(id))
				return LIGHT_STATE_UNKNOWN;
		return lights[id-1];
}
#endif

#if 0

/* START: initial */
#include "LightControllerSpy.h"

static int lastId; 
static int lastState;

void LightController_Create(void) 
{
		lastId = -1;
		lastState = -1;
}

void LightController_Destroy(void)
{
}

void LightController_TurnOn(int id) 
{
		lastId = id;
		lastState = 1;
}

void LightController_TurnOff(int id) 
{
		lastId = id;
		lastState = 0;
}

int LightControllerSpy_GetLastId(void) 
{
		return lastId;
}

int LightControllerSpy_GetLastState(void)
{
		return lastState;
}
#endif

/* END: initial */

