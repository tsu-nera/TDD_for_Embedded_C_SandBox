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

#include "CountingLightDriver.h"
#include "common.h"
#include <stdlib.h>
#include <memory.h>

/* START: struct */
typedef struct CountingLightDriverStruct * CountingLightDriver;

typedef struct CountingLightDriverStruct
{
    LightDriverStruct base;
    int counter;
} CountingLightDriverStruct;
/* END: struct */

/* START: count */
static void count(LightDriver base)
{
    CountingLightDriver self = (CountingLightDriver)base;
    self->counter++;
}
/* END: count */

/* START:destroy  */
static void destroy(LightDriver base)
{
    CountingLightDriver self = (CountingLightDriver)base;
    free(self);
}
/* END: destroy */

/* START: interface */
static LightDriverInterfaceStruct interface =
{
        count, count, destroy
};
/* END: interface */

#if 0 /* START: create1 */
LightDriver CountingLightDriver_Create(int id)
{
    CountingLightDriver self = calloc(1, sizeof(CountingLightDriverStruct));
    self->base.type = "CountingLightDriver";
    self->base.id = id;
    return (LightDriver)self;
}
#endif /* END: create1 */

/* START: create2 */
LightDriver CountingLightDriver_Create(int id)
{
    CountingLightDriver self = calloc(1, sizeof(CountingLightDriverStruct));
    self->base.vtable = &interface;
    self->base.type = "CountingLightDriver";
    self->base.id = id;
    return (LightDriver)self;
}
/* END: create2 */

/* START: getcount */
int CountingLightDriver_GetCallCount(LightDriver base)
{
    CountingLightDriver self = (CountingLightDriver)base;
    return self->counter;
}
/* END: getcount */
