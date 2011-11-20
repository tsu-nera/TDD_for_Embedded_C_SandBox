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


#include "LightScheduler.h"
#include "LightController.h"
#include "LightControllerSpy.h"
#include "TimeService.h"
#include "RandomMinute.h"
#include <stdlib.h>

enum
{
	TURN_ON, TURN_OFF, DIM, RANDOM_ON, RANDOM_OFF
};

enum
{
	MAX_EVENTS = 128, UNUSED = -1
};

typedef struct
{
	int id;
	Day day;
	int event;
	int minuteOfDay;
} ScheduledLightEvent;

static ScheduledLightEvent scheduledEvent;
static ScheduledLightEvent scheduledEvents[MAX_EVENTS];

void LightScheduler_Create(void)
{
	int i;

	scheduledEvent.id = UNUSED;

	for(i = 0; i < MAX_EVENTS; i++)
		scheduledEvents[i].id = UNUSED;

	TimeService_SetPeriodicAlarmInSeconds(60,
			LightScheduler_Wakeup);
}

void LightScheduler_Destroy(void)
{
	TimeService_CancelPeriodicAlarmInSeconds(60,
			LightScheduler_Wakeup);
}

static void scheduleEvent(int id, Day day, int minuteOfDay, int event)
{
	int i;

	for(i = 0; i < MAX_EVENTS; i++)
	{
		if(scheduledEvents[i].id == UNUSED)
		{
			scheduledEvents[i].day = day;
			scheduledEvents[i].minuteOfDay = minuteOfDay;
			scheduledEvents[i].event = event;
			scheduledEvents[i].id = id;
			break;
		}
	}

	scheduledEvent.day = day;
	scheduledEvent.minuteOfDay = minuteOfDay;
	scheduledEvent.event = event;
	scheduledEvent.id = id;
}

#if 0
int LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay)
{
	int i;

	if (id < 0 || id >= MAX_LIGHTS)
		return LS_ID_OUT_OF_BOUNDS;

	for (i = 0; i < MAX_EVENTS; i++)
	{
		if (eventList[i].id == UNUSED)
		{
			eventList[i].id = id;
			eventList[i].day = day;
			eventList[i].minuteOfDay = minuteOfDay;
			eventList[i].event = TURN_ON;
			eventList[i].randomize = RANDOM_OFF;
			eventList[i].randomMinutes = 0;
			return LS_OK;
		}
	}
	return LS_TOO_MANY_EVENTS;
}

int LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay)
{
	int i;

	if (id < 0 || id >= MAX_LIGHTS)
		return LS_ID_OUT_OF_BOUNDS;

	for (i = 0; i < MAX_EVENTS; i++)
	{
		if (eventList[i].id == UNUSED)
		{
			eventList[i].id = id;
			eventList[i].day = day;
			eventList[i].minuteOfDay = minuteOfDay;
			eventList[i].event = TURN_OFF;
			eventList[i].randomize = RANDOM_OFF;
			eventList[i].randomMinutes = 0;
			return LS_OK;
		}
	}
	return LS_TOO_MANY_EVENTS;
}
#endif

/**N この２つの関数は戻り値を返さなければいけないけれど */
/**N とりあえず、後回しで */
int LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay)
{
	scheduleEvent(id, day, minuteOfDay, TURN_ON);
	return 0;
}

int LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay)
{
	scheduleEvent(id, day, minuteOfDay, TURN_OFF);
	return 0;
}

static int DoesLightRespondToday(Time *time, int reactionDay)
{
	int today = time->dayOfWeek;

	if(reactionDay == EVERYDAY)
		return TRUE;
	if(reactionDay == today)
		return TRUE;
	if(reactionDay == WEEKEND && (SATURDAY == today || SUNDAY == today))
		return TRUE;
	if(reactionDay == WEEKDAY && today >= MONDAY && today <= FRIDAY)
		return TRUE;

	return FALSE;
}

static void operateLight(ScheduledLightEvent *lightEvent)
{
	if(lightEvent->event == TURN_ON)
		LightController_On(lightEvent->id);
	else if(lightEvent->event == TURN_OFF)
		LightController_Off(lightEvent->id);
}

static void processEventDuenow(Time *time, ScheduledLightEvent *lightEvent)
{
	if(lightEvent->id == UNUSED)
		return;
	if(!DoesLightRespondToday(time, lightEvent->day))
		return;
	if(lightEvent->minuteOfDay != time->minuteOfDay)
		return;

	operateLight(lightEvent);
}

void LightScheduler_Wakeup(void)
{
	int i;
	Time time;
	TimeService_GetTime(&time);

	for(i=0; i<MAX_EVENTS; i++)
	{
		processEventDuenow(&time, &scheduledEvents[i] );
	}

	processEventDuenow(&time, &scheduledEvent);
}

#if TEST_PATH

typedef struct
{
	int id;
	Day day;
	int minuteOfDay;
	int event;
	int randomize;
	int randomMinutes;

} ScheduledLightEvent;

static ScheduledLightEvent eventList[MAX_EVENTS];

void LightScheduler_Create(void)
{
	int i;
	for (i = 0; i < MAX_EVENTS; i++)
	{
		eventList[i].id = UNUSED;
	}
}


int LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay)
{
	int i;

	if (id < 0 || id >= MAX_LIGHTS)
		return LS_ID_OUT_OF_BOUNDS;

	for (i = 0; i < MAX_EVENTS; i++)
	{
		if (eventList[i].id == UNUSED)
		{
			eventList[i].id = id;
			eventList[i].day = day;
			eventList[i].minuteOfDay = minuteOfDay;
			eventList[i].event = TURN_ON;
			eventList[i].randomize = RANDOM_OFF;
			eventList[i].randomMinutes = 0;
			return LS_OK;
		}
	}
	return LS_TOO_MANY_EVENTS;
}

int LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay)
{
	int i;

	if (id < 0 || id >= MAX_LIGHTS)
		return LS_ID_OUT_OF_BOUNDS;

	for (i = 0; i < MAX_EVENTS; i++)
	{
		if (eventList[i].id == UNUSED)
		{
			eventList[i].id = id;
			eventList[i].day = day;
			eventList[i].minuteOfDay = minuteOfDay;
			eventList[i].event = TURN_OFF;
			eventList[i].randomize = RANDOM_OFF;
			eventList[i].randomMinutes = 0;
			return LS_OK;
		}
	}
	return LS_TOO_MANY_EVENTS;
}


void LightScheduler_Randomize(int id, Day day, int minuteOfDay)
{
	int i;
	for (i = 0; i < MAX_EVENTS; i++)
	{
		ScheduledLightEvent * e = &eventList[i];
		if (e->id == id && e->day == day && e->minuteOfDay == minuteOfDay)
		{
			e->randomize = RANDOM_ON;
			e->randomMinutes = RandomMinute_Get();
		}
	}
}

void LightScheduler_ScheduleRemove(int id, Day day, int minuteOfDay)
{
	int i;

	for (i = 0; i < MAX_EVENTS; i++)
	{
		if (eventList[i].id == id && eventList[i].day == day
				&& eventList[i].minuteOfDay == minuteOfDay)
		{
			eventList[i].id = UNUSED;
		}
	}
}
#endif

/* START: NeedsRefactoring1 */
#if 0
void LightScheduler_WakeUp(void)
{
	int i;
	Time time;
	Day td;
	int min;

	TimeService_GetTime(&time);
	td = time.dayOfWeek;
	min = time.minuteOfDay;

	for (i = 0; i < MAX_EVENTS; i++)
	{
		ScheduledLightEvent * se = &eventList[i];
		if (se->id != UNUSED)
		{
			Day d = se->day;
			if ( (d == EVERYDAY) || (d == td) || (d == WEEKEND &&
					(SATURDAY == td || SUNDAY == td)) ||
					(d == WEEKDAY && (td >= MONDAY
							&& td <= FRIDAY)))
			{
				/* it's the right day */
				if (min == se->minuteOfDay + se->randomMinutes)
				{
					if (TURN_ON == se->event)
						LightController_TurnOn(se->id);
					else if (TURN_OFF == se->event)
						LightController_TurnOff(se->id);

					if (se->randomize == RANDOM_ON)
						se->randomMinutes = RandomMinute_Get();
					else
						se->randomMinutes = 0;

				}
			}
		}
	}

}
#endif
/* END: NeedsRefactoring1 */

