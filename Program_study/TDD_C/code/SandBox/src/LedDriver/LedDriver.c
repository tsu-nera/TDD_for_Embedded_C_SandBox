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
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

enum {
	ALL_LEDS_ON = ~0,
	ALL_LEDS_OFF = ~ALL_LEDS_ON
};

enum {FIRST_LED = 1, LAST_LED = 16};

/**N 外部変数や関数に対してstaticを使用することもできます。
		通常外部変数や関数はプログラム全体のどこからでも見えるようになっています。
		しかし、staticを使って静的な記憶クラスで定義すると、
		その外部変数や関数はそれが定義されたファイル(モジュール)以外からは
		参照することができなくなります。変数や関数をファイル内のみで使用し、
		他に対しては公開したくない場合にこの方法をとります。 */
static bool IsLedOutOfBounds(int ledNumber)
{
	return ( (ledNumber < FIRST_LED) || (ledNumber > LAST_LED) );
}

static uint16_t convertLedNumberToBit(int ledNumber)
{
	return 1 << (ledNumber -1);
}

static uint16_t* ledsAddress;
static uint16_t  ledsImage;

void LedDriver_Create(uint16_t *address)
{
	ledsAddress  = address;
	ledsImage = ALL_LEDS_OFF;
	*ledsAddress = ledsImage;
}

static void updateHardware(void)
{
	*ledsAddress = ledsImage;
}

static void setLedImageBit(int ledNumber)
{
	ledsImage |= convertLedNumberToBit(ledNumber);
}

void LedDriver_TurnOn(int ledNumber)
{
	if(IsLedOutOfBounds(ledNumber))
		return;

	setLedImageBit(ledNumber);
	updateHardware();
}

static void clearLedImageBit(int ledNumber)
{
	ledsImage &= ~( convertLedNumberToBit(ledNumber) );
}

void LedDriver_TurnOff(int ledNumber)
{
	if(IsLedOutOfBounds(ledNumber))
		return;

	clearLedImageBit(ledNumber);
	updateHardware();
}

void LedDriver_TurnAllOn(void)
{
	ledsImage = ALL_LEDS_ON;
	updateHardware();
}
void LedDriver_TurnAllOff(void)
{
	ledsImage = ALL_LEDS_OFF;
	updateHardware();
}

void LedDriver_Destroy(void)
{
}

bool LedDriver_IsOn(int ledNumber)
{
	if(IsLedOutOfBounds(ledNumber));
		return false;

	return ledsImage & ((convertLedNumberToBit(ledNumber)));
}

bool LedDriver_IsOff(int ledNumber)
{
//	return false;
	return !LedDriver_IsOn(ledNumber);
}

