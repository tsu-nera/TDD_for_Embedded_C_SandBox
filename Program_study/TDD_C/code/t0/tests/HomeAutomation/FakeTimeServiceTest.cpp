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

TEST(FakeTimeService, Create)
{
	Time time;
	TimeService_GetTime(&time);

	LONGS_EQUAL(TIME_UNKNOWN, time.minuteOfDay);
	LONGS_EQUAL(TIME_UNKNOWN, time.dayOfWeekd);
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

TEST(LightScheduler, NoSheduleNothingHappens)
{
	FakeTimeService_SetDay(MONDAY);
	FakeTimeService_SetMinute(100);

	LightScheduler_Wakeup();

	LONGS_EQUAL(TIME_UNKNOWN, LightControllerSpy_GetLastId());
	LONGS_EQUAL(TIME_UNKNOWN, LightControllerSpy_GetLastState());
}

