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


#include "MemMappedLightDriver.h"
#include <stdlib.h>
#include <memory.h>
#include "common.h"

typedef struct MemMappedLightDriverStruct * MemMappedLightDriver;
typedef struct MemMappedLightDriverStruct
{
    LightDriverStruct base;
    uint32_t * address;
} MemMappedLightDriverStruct;

LightDriver MemMappedLightDriver_Create(int id, uint32_t * address)
{
     MemMappedLightDriver self = calloc(1, sizeof(MemMappedLightDriverStruct));
     self->base.type = MemoryMapped;
     self->base.id = id;
     self->address = address;
     return (LightDriver)self;
}

void MemMappedLightDriver_Destroy(LightDriver super)
{
    free(super);
}

void MemMappedLightDriver_TurnOn(LightDriver super)
{
    explodesInTestEnvironment(super);
}

void MemMappedLightDriver_TurnOff(LightDriver super)
{
    explodesInTestEnvironment(super);
}

