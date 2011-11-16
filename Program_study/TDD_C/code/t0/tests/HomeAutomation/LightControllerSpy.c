/*
 * LightControllerSpy.c
 *
 *  Created on: 2011/10/30
 *      Author: TSUNEMICHI
 */

/**N Spy function は、メモリ（構成テーブルや加点テーブル）     */
/**N にアクセスするためのインターフェース                      */
/**N TDDを実践するためには、こういう虚構の関数を作る必要がある */

#include "LightController.h"
#include "LightControllerSpy.h"

static int lastId;
static int lastState;


void LightController_Create(void)
{
	lastId    = LIGHT_ID_UNKNOWN;
	lastState = LIGHT_STATE_UNKNOWN;
}

void LightController_On(int id)
{
	lastId = id;
	lastState = LIGHT_ON;
}

void LightController_Off(int id)
{
	lastId = id;
	lastState = LIGHT_OFF;
}

int LightControllerSpy_GetLastId(void)
{
	return lastId;
}

int LightControllerSpy_GetLastState(void)
{
	return lastState;
}

void LightController_Destroy(void)
{

}


