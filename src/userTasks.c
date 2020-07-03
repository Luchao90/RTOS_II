/*=============================================================================
 * Copyright (c) 2020, Luciano Francisco Vittori <lucianovittori99@gmail.com>
 * All rights reserved.
 * License: bsd-3-clause (see LICENSE.txt)
 * Date: 2020/07/03
 * Version: 1.0
 *===========================================================================*/

/*=====[Inclusion of own header]=============================================*/

#include "userTasks.h"

/*=====[Inclusions of private function dependencies]=========================*/

/*=====[Definition macros of private constants]==============================*/

/*=====[Private function-like macros]========================================*/

/*=====[Definitions of private data types]===================================*/

/*=====[Definitions of external public global variables]=====================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Prototypes (declarations) of private functions]======================*/

/*=====[Implementations of public functions]=================================*/

// Task implementation
void Task_A(void* taskParmPtr) {
	const char msg[] = "LED ON\r\n";
	Queue_1 = xQueueCreate(1, LENGTH);

	gpioWrite( LED, ON);

	// Send the task to the locked state for 1 s (delay)
	vTaskDelay(1000 / portTICK_RATE_MS);
	gpioWrite( LED, OFF);

	// Periodic task every 2000 ms
	portTickType xPeriodicity = 2000 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();

	// ----- Task repeat for ever -------------------------
	while (TRUE) {
		gpioToggle( LED);
		xQueueSend(Queue_1, msg, portMAX_DELAY);
		// Send the task to the locked state during xPeriodicity
		// (periodical delay)
		vTaskDelayUntil(&xLastWakeTime, xPeriodicity);
	}
}

void Task_B(void* taskParmPtr) {
	char msg[LENGTH];
}
void Task_C(void* taskParmPtr) {
	char msg[LENGTH];
	while (true) {
		xQueueReceive(Queue_1, msg, portMAX_DELAY);
		printf("%s", msg);
	}
}


/*=====[Implementations of interrupt functions]==============================*/

/*=====[Implementations of private functions]================================*/

