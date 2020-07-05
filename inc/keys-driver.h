/*
 * keys-driver.h
 *
 *  Created on: Jul 4, 2020
 *      Author: luchao90
 */

#ifndef PROGRAMS_RTOS_II_INC_KEYS_DRIVER_H_
#define PROGRAMS_RTOS_II_INC_KEYS_DRIVER_H_

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "sapi.h"
#include "user-hal-keys.h"

typedef struct {
	uint8_t key_number;
	portTickType xTicks;
} keyboard_event_t;

struct {
	keyboard_event_t event[KEYS_QUANTITY];
	QueueHandle_t Queue_updated;
} keyboard;


bool Keyboard_Init (void);

void Keyboard_Update (void);

#endif /* PROGRAMS_RTOS_II_INC_KEYS_DRIVER_H_ */
