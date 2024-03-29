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

#ifndef D_LightControllerSpy_H
#define D_LightControllerSpy_H

#include "LightController.h"

/* START: RememberAllLightStates */
typedef enum
{
	LIGHT_ID_UNKNOWN = -1, LIGHT_STATE_UNKNOWN = -1,
	LIGHT_OFF = 0, LIGHT_ON = 1
} LightState;


void LightController_On(int id);
void LightController_Off(int id);
int LightControllerSpy_GetLastId(void);
int LightControllerSpy_GetLastState(void);
void LightScheduler_Wakeup(void);
void LightController_Destroy(void);

LightState LightControllerSpy_GetLightState(int id);
/**N なるほど、enumの使い方はこういう戻り値の方法にあったのか！ */

/* END: RememberAllLightStates */

int LightControllerSpy_GetLastId(void);
int LightControllerSpy_GetLastState(void);
int LightControllerSpy_GetEventCounts(void);

#endif  /* D_LightControllerSpy_H */

#if 0 /* START: initial */
#ifndef D_LightControllerSpy_H
#define D_LightControllerSpy_H

#include "LightController.h"

int LightControllerSpy_GetLastId(void);
int LightControllerSpy_GetLastState(void);

#endif  /* D_LightControllerSpy_H */
/* END: initial */
#endif
