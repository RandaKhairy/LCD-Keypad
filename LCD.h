/*
 * LCD.h
 *
 *  Created on: Oct 27, 2019
 *      Author: Mariam Taha
 */

#ifndef LCD_H_
#define LCD_H_

#include <stdlib.h>
#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"
#include "DIO.h"

#define NUM_Characters 16

typedef enum { state1, state2, state3, state4, state5, state6, state7, state8 } INIT_State;

typedef enum {BUSY, DONE} LCD_status_t;

extern LCD_status_t displayStringState;
extern LCD_status_t integerdisplayState;
extern LCD_status_t ClearState;
extern LCD_status_t gotoState;


#define CLEAR_COMMAND 0x01
#define FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_Four_BIT_MODE 0x28
#define TWO_LINE_LCD_Eight_BIT_MODE 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80

void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 data);
void LCD_displayString(const char* data);
void LCD_init(void);
void LCD_clearScreen(void);
void LCD_goToRowColumn(uint8 row,uint8 col);
void LCD_intgerToString(uint8 data);


#endif /* LCD_H_ */
