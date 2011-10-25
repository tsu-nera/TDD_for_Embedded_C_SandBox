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


#include "Flash.h"
#include "IO.h"
#include "m28w160ect.h"
#include "MicroTime.h"

#define FLASH_WRITE_TIMEOUT_IN_MICROSECONDS 5000

void Flash_Create(void)
{
}

void Flash_Destroy(void)
{
}

/* START: programError */
static int writeError(int status)
{
    IO_Write(CommandRegister, Reset);

    if (status & VppErrorBit)
        return FLASH_VPP_ERROR;
    else if (status & ProgramErrorBit)
        return FLASH_PROGRAM_ERROR;
    else if (status & BlockProtectionErrorBit)
        return FLASH_PROTECTED_BLOCK_ERROR;
    else
        return FLASH_UNKNOWN_PROGRAM_ERROR;
}
/* END: programError */

/* START: Flash_Write_8 */
int Flash_Write(ioAddress offset, ioData data)
{
    ioData status = 0;
    uint32_t timestamp = MicroTime_Get();

    IO_Write(CommandRegister, ProgramCommand);
    IO_Write(offset, data);

    status = IO_Read(StatusRegister);
    while ((status & ReadyBit) == 0)
    {
        if (MicroTime_Get() - timestamp >= FLASH_WRITE_TIMEOUT_IN_MICROSECONDS)
            return FLASH_TIMEOUT_ERROR;
        status = IO_Read(StatusRegister);
    }

    if (status != ReadyBit)
        return writeError(status);

    if (data != IO_Read(offset))
        return FLASH_READ_BACK_ERROR;

    return FLASH_SUCCESS;
}
/* END: Flash_Write_8 */

#if 0 /* START: Flash_Write_1 */
int Flash_Write(ioAddress address, ioData data)
{
    return -1;
}
/* END: Flash_Write_1 */
#endif

#if 0 /* START: Flash_Write_2 */
int Flash_Write(ioAddress address, ioData data)
{
    IO_Write(0x40, 0);
    return -1;
}
/* END: Flash_Write_2 */
#endif

#if 0 /* START: Flash_Write_3 */
int Flash_Write(ioAddress address, ioData data)
{
    IO_Write(0, 0x40);
    IO_Write(address, data);
    IO_Read(0);
    IO_Read(address);
    return FLASH_SUCCESS;
}
/* END: Flash_Write_3 */
#endif

#if 0 /* START: Flash_Write_4 */
int Flash_Write(ioAddress address, ioData data)
{
    IO_Write(CommandRegister, ProgramCommand);
    IO_Write(address, data);
    IO_Read(StatusRegister);
    IO_Read(address);
    return FLASH_SUCCESS;
}
/* END: Flash_Write_4 */
#endif

#if 0 /* START: Flash_Write_5 */
int Flash_Write(ioAddress address, ioData data)
{
    ioData status = 0;

    IO_Write(CommandRegister, ProgramCommand);
    IO_Write(address, data);

    while ((status & ReadyBit) == 0)
        status = IO_Read(StatusRegister);

    IO_Read(address);

    return FLASH_SUCCESS;
}
/* END: Flash_Write_5 */
#endif

#if 0 /* START: Flash_Write_6 */
int Flash_Write(ioAddress offset, ioData data)
{
    ioData status = 0;

    IO_Write(CommandRegister, ProgramCommand);
    IO_Write(offset, data);

    while ((status & ReadyBit) == 0)
        status = IO_Read(StatusRegister);

    if (status != ReadyBit)
    {
        IO_Write(CommandRegister, Reset);

        if (status & VppErrorBit)
            return FLASH_VPP_ERROR;
        else if (status & ProgramErrorBit)
            return FLASH_PROGRAM_ERROR;
        else if (status & BlockProtectionErrorBit)
            return FLASH_PROTECTED_BLOCK_ERROR;
        else
            return FLASH_UNKNOWN_PROGRAM_ERROR;
    }

    return FLASH_SUCCESS;
}
#endif /* END: Flash_Write_6 */

#if 0 /* START: Flash_Write_7 */
int Flash_Write(ioAddress offset, ioData data)
{
    ioData status = 0;

    IO_Write(CommandRegister, ProgramCommand);
    IO_Write(offset, data);

    while ((status & ReadyBit) == 0)
        status = IO_Read(StatusRegister);

    if (status != ReadyBit)
        return writeError(status);

    if (data != IO_Read(offset))
        return FLASH_READ_BACK_ERROR;

    return FLASH_SUCCESS;
}
#endif /* END: Flash_Write_7 */

