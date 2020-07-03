/*=============================================================================
 * Copyright (c) 2020, Luciano Francisco Vittori <lucianovittori99@gmail.com>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/07/03
 * Version: 1.0
 *===========================================================================*/

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef __USER_TASKS_H__
#define __USER_TASKS_H__

/*=====[Inclusions of public function dependencies]==========================*/

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "sapi.h"
#include "user-hal-keys.h"

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/
#define LENGTH 20
/*=====[Public function-like macros]=========================================*/

/*=====[Definitions of public data types]====================================*/
QueueHandle_t Queue_1;
/*=====[Prototypes (declarations) of public functions]=======================*/

void Task_A( void* taskParmPtr );  // Task declaration
void Task_B( void* taskParmPtr );  // Task declaration
void Task_C( void* taskParmPtr );  // Task declaration

/*=====[Prototypes (declarations) of public interrupt functions]=============*/

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* __USER_TASKS_H__ */
