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

#include "LightDriverSpy.h"
#include "LightController.h"
#include "common.h"
#include <stdlib.h>
#include <memory.h>

typedef struct LightDriverSpyStruct
{
    LightDriverStruct base;
} LightDriverSpyStruct;

static int states[MAX_LIGHTS];
static int lastId;
static int lastState;

void LightDriverSpy_Reset(void)
{
    int i;
    for (i = 0; i < MAX_LIGHTS; i++)
    {
        states[i] = LIGHT_STATE_UNKNOWN;
    }
    lastId = LIGHT_ID_UNKNOWN;
    lastState = LIGHT_STATE_UNKNOWN;
}

/* START: AddSpies */
void LightDriverSpy_AddSpiesToController(void)
{
    int i;
    for (i = 0; i < MAX_LIGHTS; i++)
    {
        LightDriver spy = (LightDriver)LightDriverSpy_Create(i);
        LightController_Add(i, spy);
    }
}
/* END: AddSpies */


/* START: create */
LightDriver LightDriverSpy_Create(int id)
{
    LightDriverSpy self = calloc(1, sizeof(LightDriverSpyStruct));
    self->base.type = "Spy";
    self->base.id = id;
    return (LightDriver)self;
}
/* END: create */

/* START: fileScope */
static void destroy(LightDriver base)
{
    free(base);
}

static void update(int id, int state)
{
    states[id] = state;
    lastId = id;
    lastState = state;
}

static void turnOn(LightDriver base)
{
    LightDriverSpy self = (LightDriverSpy)base;
    update(self->base.id, LIGHT_ON);
}

static void turnOff(LightDriver base)
{
    LightDriverSpy self = (LightDriverSpy)base;
    update(self->base.id, LIGHT_OFF);
}
/* END: fileScope */

/* START: fp_init89 */
static LightDriverInterfaceStruct interface =
{
    turnOn,
    turnOff,
    destroy
};
/* END: fp_init89 */

#if 0 /* START: fp_init99 */
static LightDriverInterfaceStruct interface =
{
    .Destroy = LightDriverSpy_Destroy
    .TurnOn = LightDriverSpy_TurnOn,
    .TurnOff = LightDriverSpy_TurnOff,
};
#endif /* END: fp_init99 */


void LightDriverSpy_InstallInterface(void)
{
    LightDriver_SetInterface(&interface);
}

int LightDriverSpy_GetState(int id)
{
    return states[id];
}

int LightDriverSpy_GetLastId(void)
{
    return lastId;
}

int LightDriverSpy_GetLastState(void)
{
    return lastState;
}

#if 0
/* START: turnOn */
void LightDriverSpy_TurnOn(LightDriver base)
{
    LightDriverSpy self = (LightDriverSpy)base;
    states[self->base.id] = LIGHT_ON;
    lastId = self->base.id;
    lastState = LIGHT_ON;
}
/* END: turnOn */


/* START: initTurnOn */
static LightDriverInterfaceStruct interface =
{
    LightDriverSpy_TurnOn,
    0,
    0
};
#endif /* END: initTurnOn */



