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


#ifndef D_MemMappedLightDriver_H
#define D_MemMappedLightDriver_H

#include "LightDriver.h"
#include <stdint.h>

LightDriver MemMappedLightDriver_Create(int lightId, uint32_t * address);
void MemMappedLightDriver_Destroy(LightDriver);
void MemMappedLightDriver_TurnOn(LightDriver);
void MemMappedLightDriver_TurnOff(LightDriver);

#endif  /* D_MemMappedLightDriver_H */
