/*
 * keypad.h
 *
 *  Created on: Oct 24, 2019
 *      Author: Randa
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_


#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"
#include "lcd.h"


#define N_col 3
#define N_row 3

/*Key status*/
#define KEY_RELEASED 1
#define KEY_PRESSED  0

/* Keypad Port Configurations */
#define KEYPAD_PORT_OUT PORTC
#define KEYPAD_PORT_IN  PINC
#define KEYPAD_PORT_DIR DDRC


typedef uint8(*ptrKeypadFunctionCallback)(void);


void KeyPad_getPressedKey(void);

#endif /* KEYPAD_H_ */
