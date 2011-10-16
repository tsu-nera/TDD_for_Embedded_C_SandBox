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

#include "LedDriver.h"
#include "RuntimeError.h"

#include <stdlib.h>
#include <memory.h>

enum {
  ALL_LEDS_ON = ~0,
  ALL_LEDS_OFF = ~ALL_LEDS_ON
};

static uint16_t* ledsAddress;
static uint16_t  ledsImage;

void LedDriver_Create(uint16_t *address)
{
  ledsAddress  = address;
  ledsImage = ALL_LEDS_OFF;
  *ledsAddress = ledsImage;
}

static uint16_t convertLedNumberToBit(int ledNumber)
{
  return 1 << (ledNumber -1);
}

static void updateHardware(void)
{
  *ledsAddress = ledsImage;
}

void LedDriver_TurnOn(int ledNumber)
{
  if(ledNumber <= 0 || ledNumber > 16)
    return;

  ledsImage |= convertLedNumberToBit(ledNumber);
  updateHardware();
}

void LedDriver_TurnOff(int ledNumber)
{
  if(ledNumber <= 0 || ledNumber > 16)
    return;

  ledsImage &= ~( convertLedNumberToBit(ledNumber) );
  updateHardware();
}

void LedDriver_TurnAllOn(void)
{
  ledsImage = ALL_LEDS_ON;
  updateHardware();
}

void LedDriver_Destroy(void)
{
}
