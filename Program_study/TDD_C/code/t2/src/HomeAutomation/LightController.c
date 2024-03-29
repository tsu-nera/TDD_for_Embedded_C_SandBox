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


#include "LightController.h"
#include <stdlib.h>
#include <memory.h>
#include "LightDriver.h"
#include "common.h"

/* START: hidden_data */
static LightDriver lightDrivers[MAX_LIGHTS] = {NULL};
/* END: hidden_data */

/* START: create */
void LightController_Create(void)
{
    memset(lightDrivers, 0, sizeof lightDrivers);
}
/* END: create */

/* START: destroy */
void LightController_Destroy(void)
{
    int i;
    for (i = 0; i < MAX_LIGHTS; i++)
    {
        LightDriver driver = lightDrivers[i];
        LightDriver_Destroy(driver);
        lightDrivers[i] = NULL;
    }
}
/* END: destroy */

static BOOL isIdInBounds(int id)
{
    return id < 0 || id >= MAX_LIGHTS;
}

/* START: add */
BOOL LightController_Add(int id, LightDriver lightDriver)
{
    if (isIdInBounds(id))
        return FALSE;

    if (lightDriver == NULL)
        return FALSE;

    LightDriver_Destroy(lightDrivers[id]);

    lightDrivers[id] = lightDriver;
    return TRUE;
}
/* END: add */

/* START: remove */
BOOL LightController_Remove(int id)
{
    if (isIdInBounds(id))
        return FALSE;

    if (lightDrivers[id] == NULL)
        return FALSE;

    LightDriver_Destroy(lightDrivers[id]);

    lightDrivers[id] = NULL;
    return TRUE;
}
/* END: remove */

/* START: on_off */
void LightController_TurnOn(int id)
{
    LightDriver_TurnOn(lightDrivers[id]);
}

void LightController_TurnOff(int id)
{
    LightDriver_TurnOff(lightDrivers[id]);
}
/* END: on_off */






