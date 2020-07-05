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

KEYS_t Tecla_1;
KEYS_t Tecla_2;

/*=====[Prototypes (declarations) of private functions]======================*/

/**
 * @brief Task Create.
 * Only for short expression.
 * @param taskParmPtr
 * @return
 */
bool Task_A_Create (void* taskParmPtr);
bool Task_B_Create (void* taskParmPtr);
bool Task_C_Create (void* taskParmPtr);

void Task_A( void* taskParmPtr );  // Task declaration
void Task_B( void* taskParmPtr );  // Task declaration
void Task_C( void* taskParmPtr );  // Task declaration

/*=====[Implementations of public functions]=================================*/

// Task A implementation
void Task_A(void* taskParmPtr) {
	const char msg[] = "LED ON\r\n";

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
	uint8_t count = 0;
	portTickType xTicks_Tecla_1 = 0;
	portTickType xTicks_Tecla_2 = 0;
	portTickType xLastPressedTime_Tecla_1 = 0;
	portTickType xLastPressedTime_Tecla_2 = 0;

	for (count = 0; count < KEY_TIMES; count++) {
		KeyUpdate(&Tecla_1);
		KeyUpdate(&Tecla_2);
		vTaskDelay(10 / portTICK_RATE_MS);
	}

	while (TRUE) {

		KeyUpdate(&Tecla_1);
		KeyUpdate(&Tecla_2);
		vTaskDelay(10 / portTICK_RATE_MS);

		if (KeyPressed(&Tecla_1)) {
			xLastPressedTime_Tecla_1 = xTaskGetTickCount();
		}

		if (KeyPressed(&Tecla_2)) {
			xLastPressedTime_Tecla_2 = xTaskGetTickCount();
		}

		if (KeyReleased(&Tecla_1)) {
			xTicks_Tecla_1 = xTaskGetTickCount();
			sprintf(msg, "TEC1 T%4d\r\n",
					xTicks_Tecla_1 - xLastPressedTime_Tecla_1);
			xQueueSend(Queue_1, msg, portMAX_DELAY);

		}
		if (KeyReleased(&Tecla_2)) {
			xTicks_Tecla_2 = xTaskGetTickCount();
			sprintf(msg, "TEC2 T%4d\r\n",
					xTicks_Tecla_2 - xLastPressedTime_Tecla_2);
			xQueueSend(Queue_1, msg, portMAX_DELAY);
		}
	}
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

bool Task_A_Init(void* taskParmPtr) {
	Queue_1 = xQueueCreate(1, LENGTH);
	if (Queue_1 == pdFAIL) {
		return false;
	} else {
		return (Task_A_Create(taskParmPtr));
	}
}

bool Task_B_Init( void* taskParmPtr ) {
	if(!KeyInit(&Tecla_1)) {
		return false;
	}
	if(!KeyInit(&Tecla_2)) {
		return false;
	}
	if (Queue_1 == pdFAIL) {
		return false;
	} else {
		return (Task_B_Create(taskParmPtr));
	}
}

bool Task_C_Init( void* taskParmPtr ) {
	if (Queue_1 == pdFAIL) {
		return false;
	} else {
		return (Task_C_Create(taskParmPtr));
	}
}


bool Task_A_Create(void* taskParmPtr) {
	if (xTaskCreate(Task_A,                // Function that implements the task.
			(const char *) "Task_A",     // Text name for the task.
			configMINIMAL_STACK_SIZE * 2, // Stack size in words, not bytes.
			0,                          // Parameter passed into the task.
			tskIDLE_PRIORITY + 1,      // Priority at which the task is created.
			0                       // Pointer to the task created in the system
			) == pdFAIL) {
		return false;
	} else {
		return true;
	}
}

bool Task_B_Create(void* taskParmPtr) {
	if (xTaskCreate(Task_B,                // Function that implements the task.
			(const char *) "Task_B",     // Text name for the task.
			configMINIMAL_STACK_SIZE * 2, // Stack size in words, not bytes.
			0,                          // Parameter passed into the task.
			tskIDLE_PRIORITY + 1,      // Priority at which the task is created.
			0                       // Pointer to the task created in the system
			) == pdFAIL) {
		return false;
	} else {
		return true;
	}
}

bool Task_C_Create(void* taskParmPtr) {
	if (xTaskCreate(Task_C,                // Function that implements the task.
			(const char *) "Task_C",     // Text name for the task.
			configMINIMAL_STACK_SIZE * 2, // Stack size in words, not bytes.
			0,                          // Parameter passed into the task.
			tskIDLE_PRIORITY + 1,      // Priority at which the task is created.
			0                       // Pointer to the task created in the system
			) == pdFAIL) {
		return false;
	} else {
		return true;
	}
}
