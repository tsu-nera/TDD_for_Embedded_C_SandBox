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

/* START: turnon */
void LightDriver_TurnOn(LightDriver self)
{
    if (self)
        self->vtable->TurnOn(self);
}
/* END: turnon */

/* START: turnoffAndDestroy */
void LightDriver_TurnOff(LightDriver self)
{
    if (self)
        self->vtable->TurnOff(self);
}

void LightDriver_Destroy(LightDriver self)
{
    if (self)
        self->vtable->Destroy(self);
}
/* END: turnoffAndDestroy */

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


#if 0 /* START: protectedPointers */
void LightDriver_TurnOn(LightDriver self)
{
    if (self && self->vtable && self->vtable->TurnOn)
        self->vtable->TurnOn(self);
}
#endif /* END: protectedPointers */



