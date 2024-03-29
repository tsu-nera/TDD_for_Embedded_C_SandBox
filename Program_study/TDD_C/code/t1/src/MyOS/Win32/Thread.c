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

#include <windows.h>
#include "Thread.h"
#include "common.h"

/* START: struct1 */
typedef struct ThreadStruct
{
    HANDLE threadHandle;
	ThreadEntryFunction entry;
	void * parameter;
	BOOL started;
} ThreadStruct;
/* END: struct1 */

/* START: create1 */
static DWORD WINAPI Win32ThreadEntry(LPVOID param)
{
	Thread thread = (Thread)param;
	return (UINT)thread->entry(thread->parameter);
}

Thread Thread_Create(ThreadEntryFunction entry, void * parameter)
{
	DWORD threadId;
    Thread self = calloc(1, sizeof(ThreadStruct));
	self->entry = entry;
	self->parameter = parameter;
    self->threadHandle = CreateThread(0, 0, 
		Win32ThreadEntry, self, CREATE_SUSPENDED, &threadId);
    return self;
}
/* END: create1 */

/* START: destroy1 */
void Thread_Destroy(Thread self)
{
    void * result = 0;
    if (self->started)
        Thread_Join(self, &result);

    CloseHandle(self->threadHandle);
    free(self);
}
/* END: destroy1 */

/* START: start1 */
void Thread_Start(Thread self)
{
	self->started = TRUE;
    ResumeThread(self->threadHandle);
	Sleep(0);
}
/* END: start1 */

/* START: exit1 */
void Thread_Exit(void * result)
{
	/* 
	 * We'll need a better solution 
	 * to the return result if ints and 
	 * pointer are different. Test pass 
	 * now, so they are the same.
	 */
    ExitThread((UINT)result);
}
/* END: exit1 */

/* START: join1 */
void Thread_Join(Thread self, void ** result)
{
	if (self->started)
	{
		WaitForSingleObject(self->threadHandle, INFINITE);
		self->started = FALSE;

	}
	GetExitCodeThread(self->threadHandle, (DWORD *)result);
}
/* END: join1 */
