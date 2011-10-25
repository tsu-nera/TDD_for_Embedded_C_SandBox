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
#include <stdlib.h>
#include <memory.h>
#include <pthread.h>


#if 0 /* START: struct1 */
typedef struct ThreadStruct
{
    ThreadEntryFunction entry;
    void * parameter;
    pthread_t pthread;

} ThreadStruct;
#endif /* END: struct1 */

/* START: struct2 */
typedef struct ThreadStruct
{
    ThreadEntryFunction entry;
    void * parameter;
    pthread_t pthread;
    void * result;

} ThreadStruct;
/* END: struct2 */


/* START: create2 */
Thread Thread_Create(ThreadEntryFunction f, void * parameter)
{
     Thread self = calloc(1, sizeof(ThreadStruct));
     self->entry = f;
     self->parameter = parameter;
     self->result = NULL;
     MyOS_AddThreadToTable(self);
     return self;
}
/* END: create2 */

/* START: destroy2 */
void Thread_Destroy(Thread self)
{
    pthread_join(self->pthread, 0);
    MyOs_RemoveThreadFromTable(self);
    free(self);
}
/* END: destroy2 */

/* START: start2 */
void Thread_Start(Thread self)
{
    self->result = NULL;
    pthread_create(&self->pthread, NULL, self->entry, self->parameter);
}
/* END: start2 */

/* START: exit2 */
BOOL FindPosixThread(Thread thread, void * pthread)
{
    return thread->pthread == (pthread_t)pthread;
}

void Thread_Exit(void * result)
{
    pthread_t pthread = pthread_self();
    Thread t = *MyOs_FindThreadEntry(FindPosixThread, pthread);
    t->result = result;
    pthread_exit(result);
}
/* END: exit2 */

/* START: join2 */
void Thread_Join(Thread other, void ** result)
{
    pthread_join(other->pthread, result);
}
/* END: join2 */

/* START: result2 */
void * Thread_Result(Thread thread)
{
    return thread->result;
}
/* END: result2 */



#if 0
/* START: create1 */
Thread Thread_Create(ThreadEntryFunction f, void * parameter)
{
     Thread self = calloc(1, sizeof(ThreadStruct));
     self->entry = f;
     self->parameter = parameter;
     return self;
}
/* END: create1 */

/* START: destroy1 */
void Thread_Destroy(Thread self)
{
    pthread_join(self->pthread, 0);
    free(self);
}
/* END: destroy1 */

/* START: start1 */
void Thread_Start(Thread self)
{
    pthread_create(&self->pthread, NULL, self->entry, self->parameter);
}
/* END: start1 */

/* START: exit1 */
void Thread_Exit(void * result)
{
    pthread_exit(result);
}
/* END: exit1 */

/* START: join1 */
void Thread_Join(Thread other, void ** result)
{
    pthread_join(other->pthread, result);
}
/* END: join1 */
#endif
