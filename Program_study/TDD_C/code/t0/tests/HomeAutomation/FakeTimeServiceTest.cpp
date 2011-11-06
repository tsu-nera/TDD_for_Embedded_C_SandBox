/*
 * FakeTimeServiceTest.cpp
 *
 *  Created on: 2011/11/05
 *      Author: TSUNEMICHI
 */

extern "C"
{
#include "LightScheduler.h"
#include "LightControllerSpy.h"
#include "FakeTimeService.h"
#include "FakeRandomMinute.h"
}
#include "CppUTest/TestHarness.h"

#if 0
TEST(FakeTimeService, Create)
{
	Time time;
	TimeService_GetTime(&time);

	LONGS_EQUAL(TIME_UNKNOWN, time.minuteOfDay);
	LONGS_EQUAL(TIME_UNKNOWN, time.dayOfWeek);
}

TEST(FakeTimeService, Set)
{
	Time time;
	/**N こんな風に、事前にメモリ上に時間をセットしてからテストする */
	FakeTimeService_SetMinute(42);
	FakeTimeService_SetDay(SATURDAY);

	LONGS_EQUAL(TIME_UNKNOWN, time.minuteOfDay);
	LONGS_EQUAL(TIME_UNKNOWN, time.dayOfWeek);
}
#endif

//
