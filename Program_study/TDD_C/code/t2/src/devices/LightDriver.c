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

#include "LightDriver.h"
#include "common.h"

/* START: SetInterface */
static LightDriverInterface interface = NULL;

void LightDriver_SetInterface(LightDriverInterface i)
{
    interface = i;
}
/* END: SetInterface */

/* START: isValid */
static BOOL isValid(LightDriver self)
{
    return interface && self;
}
/* END: isValid */

/* START: turnon */
void LightDriver_TurnOn(LightDriver self)
{
    if (isValid(self))
        interface->TurnOn(self);
}
/* END: turnon */

/* START: turnoff */
void LightDriver_TurnOff(LightDriver self)
{
    if (isValid(self))
        interface->TurnOff(self);
}
/* END: turnoff */

/* START: destroy */
void LightDriver_Destroy(LightDriver self)
{
    if (isValid(self))
        interface->Destroy(self);
}
/* END: destroy */

/* START: helpers */
const char * LightDriver_GetType(LightDriver driver)
{
    return driver->type;
}

int LightDriver_GetId(LightDriver driver)
{
    return driver->id;
}
/* END: helpers */

#if 0 /* START: turnon1 */
void LightDriver_TurnOn(LightDriver self)
{
    interface->TurnOn(self);
}
#endif /* END: turnon1 */

#if 0 /* START: brightness */
void LightDriver_SetBrightness(LightDriver self, int level)
{
    if(isValid(self) && self->brightness)
        self->brightness(self, level);
}
#endif /* END: brightness */


