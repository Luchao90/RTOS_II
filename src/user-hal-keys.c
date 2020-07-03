/*
 * user-hal-keys.c
 *
 *  Created on: Jun 8, 2020
 *      Author: luchao90
 */


#include "user-hal-keys.h"


/**
 * @brief Key port mapping
 *
 * For SAPI.
 *
 * @note Change Keys initialization definition for different key mapping
 */
static uint32_t Key_Pin[KEYS_QUANTITY] = {TEC1, TEC2, TEC3, TEC4};

//! Variable to detect how many keys was initialized.
static uint8_t Key_Init_Times = 0;

/**
 * @brief Read function.
 *
 * @param[in]  Key		Key pointer.
 * @return     True		Key pressed.
 * @return     False	Key not pressed.
 */
static bool KeyRead(KEYS_t *Key);

/**
 * @brief Error Handler.
 *
 * This function restart machine state.
 *
 * @param[in]  Key		Key pointer.
 */
static void KeyError(KEYS_t *Key);


static bool KeyRead(KEYS_t *Key) {
	return (!gpioRead(Key_Pin[Key->Key]));
}

uint8_t KeyPressed(KEYS_t *Key) {
	uint8_t i = Key->Pressed;
	Key->Pressed = 0;
	return i;
}

uint8_t KeyReleased(KEYS_t *Key) {
	uint8_t i = Key->Released;
	Key->Released = 0;
	return i;
}

uint8_t KeyTimeout(KEYS_t *Key) {
	uint8_t i = Key->Timeout;
	Key->Timeout = 0;
	return i;
}

bool KeyInit(KEYS_t *Key) {

	if (Key == NULL){
		return false;
	}

	Key->Key = Key_Init_Times;

	if ((Key->Key) >= KEYS_QUANTITY)
		return false;

	else {
		Key->State = REALESED;
		Key->Times = 0;
		Key->Times_ant = 0;
		Key->Pressed = 0;
		Key->Released = 0;
		Key_Init_Times++;
		return true;
	}
}

void KeyUpdate(KEYS_t *Key) {

	switch (Key->State) {

	case REALESED:
		if (KeyRead(Key) == true) {
			Key->Times_ant = Key->Times;
			Key->State = PRESSING;
		} else {
			Key->Times = 0;
			Key->Times_ant = 0;
		}
		break;

	case PRESSING:
		if (KeyRead(Key) == true) {
			Key->Times++;
		} else {
			Key->State = REALESED;
		}
		if ((Key->Times - Key->Times_ant) >= KEY_TIMES) {
			Key->Pressed++;
			Key->Times = 0;
			Key->Times_ant = 0;
			Key->State = PRESSED;
		}
		break;

	case PRESSED:
		if (KeyRead(Key) == true) {
			Key->Times++;
		} else {
			Key->Times = 0;
			Key->Times_ant = 0;
			Key->State = REALEASING;
		}
		if (Key->Times >= KEY_TIMEOUT) {
			Key->Timeout++;
			Key->Times = 0;
		}
		break;

	case REALEASING:
		if (KeyRead(Key) == false) {
			Key->Times++;
		} else {
			Key->State = PRESSED;
			Key->Times_ant = Key->Times;
			Key->Times = 0;
		}
		if ((Key->Times - Key->Times_ant) >= KEY_TIMES) {
			Key->Released++;
			Key->Times = 0;
			Key->Times_ant = 0;
			Key->State = REALESED;
		}
		break;

	default:
		KeyError(Key);
		break;
	}
}

static void KeyError(KEYS_t *Key) {
	Key->Times = 0;
	Key->Times_ant = 0;
	Key->Pressed = 0;
	Key->Released = 0;
	Key->State = REALESED;
}
