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

#include "TimeService.h"

BOOL Time_MatchesDayOfWeek(Time * time, Day day)
{
    int today = time->dayOfWeek;

    if (day == EVERYDAY)
        return TRUE;
    if (day == today)
        return TRUE;
    if (day == WEEKEND && (SATURDAY == today || SUNDAY == today))
        return TRUE;
    if (day == WEEKDAY && today >= MONDAY && today <= FRIDAY)
        return TRUE;
    return FALSE;
}

BOOL Time_MatchesMinuteOfDay(Time * time, int minute)
{
    if (time->minuteOfDay != minute)
        return FALSE;

    return TRUE;
}
