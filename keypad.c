/*
 * keypad.c
 *
 *  Created on: Oct 24, 2019
 *      Author: Randa
 */
#include "keypad.h"
#include "Dio.h"

KEYPAD_status_t keypad_status = NOT_PRESSED;
static uint8 g_key_state = KEY_RELEASED;
static uint8 keyPressed_counter = 0;


uint8 pressedKey;


void KeyPad_getPressedKey(void)
{
	uint8 col,row;
	for(col = 0; col < N_col; col++)
	{
		KEYPAD_PORT_DIR = (0b00100000<<col) ;
		KEYPAD_PORT_OUT = (~(0b00100000<<col));

		for(row = 0; row < N_row; row++)
		{
			g_key_state = (BIT_IS_CLEAR(KEYPAD_PORT_IN, (row + 2)));
			if(g_key_state == KEY_PRESSED)
			{
				keyPressed_counter = 1;

			}
			else if(keyPressed_counter == 1)
			{
				pressedKey = ((row * N_col) + col + 1);
				keypad_status = PRESSED;
				keyPressed_counter = 0;
			}
		}
	}
}



