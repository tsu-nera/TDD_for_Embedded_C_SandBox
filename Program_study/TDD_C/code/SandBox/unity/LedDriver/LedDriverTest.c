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
#include "../include/util/RuntimeError.h"
#include "../mocks/RuntimeErrorStub.h"

TEST_GROUP(LedDriver);

static uint16_t virtualLeds;

TEST_SETUP(LedDriver)
{
  LedDriver_Create(&virtualLeds);
}

TEST_TEAR_DOWN(LedDriver)
{

}

TEST(LedDriver, LedsOffAfterCreate)
{
  virtualLeds = 0xffff;
  LedDriver_Create(&virtualLeds);
  TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

TEST(LedDriver, TurnOnLedOne)
{
  LedDriver_TurnOn(1);
  TEST_ASSERT_EQUAL_HEX16(1, virtualLeds);
}

TEST(LedDriver, TurnOffLedOne)
{
  LedDriver_TurnOn(1);
  LedDriver_TurnOff(1);
  TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

TEST(LedDriver, TurnOnMultipleLeds)
{
  LedDriver_TurnOn(8);
  LedDriver_TurnOn(9);
  TEST_ASSERT_EQUAL_HEX16(0x180, virtualLeds);
}

TEST(LedDriver, AllOn)
{
  LedDriver_TurnAllOn();
  TEST_ASSERT_EQUAL_HEX16(0xffff, virtualLeds);
}

TEST(LedDriver, TurnOffAnyLed)
{
  LedDriver_TurnAllOn();
  LedDriver_TurnOff(8);
  TEST_ASSERT_EQUAL_HEX16(0xff7f, virtualLeds);
}

TEST(LedDriver, LedMemoryIsNotReadable)
{
  virtualLeds = 0xffff;
  LedDriver_TurnOn(8);
  TEST_ASSERT_EQUAL_HEX16(0x80, virtualLeds);
}

TEST(LedDriver, UpperAndLowerBounds)
{
  LedDriver_TurnOn(1);
  LedDriver_TurnOn(16);
  TEST_ASSERT_EQUAL_HEX16(0x8001, virtualLeds);
}

TEST(LedDriver, OutOfBoundsTurnOnDoesNoHarm)
{
  LedDriver_TurnOn(-1);
  LedDriver_TurnOn(0);
  LedDriver_TurnOn(17);
  LedDriver_TurnOn(3141);

  TEST_ASSERT_EQUAL_HEX16( 0, virtualLeds);
}

TEST(LedDriver, OutOfBoundsTurnOffDoesNoHarm)
{
  LedDriver_TurnAllOn();

  LedDriver_TurnOff(-1);
  LedDriver_TurnOff(0);
  LedDriver_TurnOff(17);
  LedDriver_TurnOff(3141);

  TEST_ASSERT_EQUAL_HEX16( 0xffff, virtualLeds);
}

TEST(LedDriver, OutOfBoundsProducesRuntimeError)
{
  LedDriver_TurnOn(-1);
  TEST_ASSERT_EQUAL_STRING("LED_Driver: out-of-bounds LED",
      RuntimeErrorStub_GetLastError());
  TEST_ASSERT_EQUAL( -1, RuntimeErrorStub_GetLastParameter());
}
