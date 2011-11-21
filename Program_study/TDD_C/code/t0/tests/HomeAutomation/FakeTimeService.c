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

#include "FakeTimeService.h"

static long int theMinute;
static int theDay;
static WakeupCallback callback;
static int period;

void TimeService_Create(void)
{
		theMinute = MINUTE_UNKNOWN;
		theDay = DAY_UNKNOWN;
}

void TimeService_Destroy(void)
{
}

void TimeService_GetTime(Time *time)
{
		time->minuteOfDay = theMinute;
		time->dayOfWeek = theDay;
}


int TimeService_GetMinute(void)
{
		return theMinute;
}

void FakeTimeService_SetMinute(int minute)
{
		theMinute = minute;
}

void FakeTimeService_SetDay(int day)
{
		theDay = day;
}

int TimeService_GetDay(void)
{
		return theDay;
}

void TimeService_SetPeriodicAlarmInSeconds(
		int seconds, WakeupCallback cb)
{
	callback = cb;
	period   = seconds;
}

void TimeService_CancelPeriodicAlarmInSeconds(
		int seconds, WakeupCallback cb)
{
	if(cb == callback && period == seconds)
	{
		callback = NULL;
		period   = 0;
	}
}
