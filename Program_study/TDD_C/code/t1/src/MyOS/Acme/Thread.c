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

#include "Thread.h"
#include "common.h"
#include <stdlib.h>
#include <memory.h>
#include "MyOsPrivate.h"
#include "src/MyOS/Acme/AcmeOs.h"

/* START: struct2 */
typedef struct ThreadStruct
{
    AcmeThreadStruct acmeThread;
    void * result;
} ThreadStruct;
/* END: struct2 */

/* START: create2 */
Thread Thread_Create(ThreadEntryFunction f, void * parameter)
{
     Thread self = calloc(1, sizeof(ThreadStruct));
     AcmeThread_create(&self->acmeThread, (AcmeThreadEntryFunction)f, parameter, 5, 1000);
     self->result = NULL;
     MyOS_AddThreadToTable(self);
     return self;
}
/* END: create2 */

/* START: destroy2 */
void Thread_Destroy(Thread self)
{
    AcmeThread_waitEnd(&self->acmeThread);
    MyOs_RemoveThreadFromTable(self);
    free(self);
}
/* END: destroy2 */

/* START: start2 */
void Thread_Start(Thread self)
{
    self->result = NULL;
    AcmeThread_start(&self->acmeThread);
}
/* END: start2 */

/* START: exit2 */
BOOL FindAcmeThread(Thread thread, void * acmeThread)
{
    return &thread->acmeThread == (AcmeThread)acmeThread;
}

void Thread_Exit(void * result)
{
    AcmeThread acmeThread = AcmeThread_currentThread();

    Thread t = *MyOs_FindThreadEntry(FindAcmeThread, acmeThread);
    t->result = result;
    AcmeThread_exit(0);
}
/* END: exit2 */

/* START: join2 */
void Thread_Join(Thread self, void ** result)
{
    AcmeThread_waitEnd(&self->acmeThread);
    if (result != NULL)
        *result = self->result;
}
/* END: join2 */

/* START: result */
void * Thread_Result(Thread thread)
{
    return thread->result;
}
/* END: result */
