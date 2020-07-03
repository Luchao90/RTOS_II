/*
 * user-hal-keys.h
 *
 *  Created on: Jun 8, 2020
 *      Author: luchao90
 */

#ifndef PROGRAMS_RTOS_I_INC_USER_HAL_KEYS_H_
#define PROGRAMS_RTOS_I_INC_USER_HAL_KEYS_H_

#include "RTOS_II.h"
#include "sapi.h"

#define KEY_TIMES 		4		//!< Times read
#define KEY_TIMEOUT		5000	//!< Updates Times required for Timeout
#define KEYS_QUANTITY 	4		//!< Keys quantity

/**
 * Key application map.
 */
enum {
	KEY_MODE,//!< KEY_MODE
	KEY_DOWN,//!< KEY_DOWN
	KEY_UP,  //!< KEY_UP
	KEY_ENTER//!< KEY_ENTER
};

/**
 * Enumeration for possible state's machine.
 */
typedef enum KeyState_enum {
	REALESED,			//!< Button not pressed.
	PRESSING,			//!< Transition to pressed.
	PRESSED,			//!< Button pressed.
	REALEASING,			//!< Transition to not pressed.
} KeyState_t;

/**
 * Variable to manage all information referred to one key.
 */
typedef struct {
	KeyState_t State;			//!< Machine State of key.
	uint16_t Times;				//!< Amount of readings.
	uint16_t Times_ant;			//!< Variable for auxiliary times count.
	uint8_t Pressed;			//!< Flag for Prebssed key.
	uint8_t Released;			//!< Flag for Released key.
	uint8_t Timeout;			//!< Flag for Timeout.
	uint8_t Key;				//!< Key Character.
} KEYS_t;

/**
 * @brief Key Initiation function.
 *
 * @note Should be called once for every key at the beginning.
 *
 * @param[in]  Key		Key pointer.
 * @return     True		Key initialized
 * @return     False	Key doesn't exist, Key Init was called more than KEYS_QUANTITY
 */
bool KeyInit(KEYS_t *Key);

/**
 * @brief Update Sate Function.
 *
 * This function update machine state. You should call this function every x times
 * It's recommended every 10mS
 *
 * @note KeyInit must be called before
 * @param[in]  Key		Key pointer.
 */
void KeyUpdate(KEYS_t* Key);

/**
 * @brief Public function for one key read.
 *
 * @param[in]  Key		Key pointer.
 * @return     True		Key was pressed.
 * @return     False	Key not pressed.
 */
uint8_t KeyPressed(KEYS_t* Key);

/**
 * @brief Public function for one key read.
 *
 * @param	Key		Key pointer.
 * @return	True		Key was pressed and released.
 * @return	False	Key may be was pressed but not released.
 */
uint8_t KeyReleased(KEYS_t* Key);
/**
 * @brief Public function to detect timeout pressing one key
 *
 * When timeout is reached, key state reset.
 *
 * @note timeout depends on call period of KeyUpdate function.
 *
 * @param	Key				Key pointer.
 * @return	Key->Timeout	How many times was in last state.
 * @return	False			Key not pressed.
 */
uint8_t KeyTimeout(KEYS_t *Key);

#endif /* PROGRAMS_RTOS_I_INC_USER_HAL_KEYS_H_ */
