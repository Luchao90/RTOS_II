/*
 * keys-driver.c
 *
 *  Created on: Jul 4, 2020
 *      Author: luchao90
 */


#include "keys-driver.h"

KEYS_t keys[KEYS_QUANTITY];

bool Keyboard_Init(void) {
	uint8_t i;
	keyboard.Queue_updated = xQueueCreate(KEYS_QUANTITY, sizeof(keyboard_event_t));

	if (!keyboard.Queue_updated) {
		return false;
	} else {
		for (i = 0; i < KEYS_QUANTITY; i++) {
			KeyInit(&keys[i]);
		}
		return true;
	}
}

void Keyboard_Update(void) {
	uint8_t i;
	for (i = 0; i < KEYS_QUANTITY; i++) {

		KeyUpdate(&keys[i]);

		if (KeyPressed(&keys[i])) {
			keyboard.event[i].xTicks = xTaskGetTickCount();
		}
		if (KeyReleased(&keys[i])) {
			keyboard.event[i].xTicks = xTaskGetTickCount() -keyboard.event[i].xTicks;
			keyboard.event[i].key_number = i;
			xQueueSend(keyboard.Queue_updated, &keyboard.event[i], portMAX_DELAY);
		}
	}
}
