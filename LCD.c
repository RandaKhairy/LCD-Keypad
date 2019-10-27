/*
 * LCD.c
 *
 *  Created on: Oct 27, 2019
 *      Author: Mariam Taha
 */

#include "LCD.h"

static uint8 g_buffer[NUM_Characters];

static uint8 init_lock = 0;
static uint8 command_key = 0;
static uint8 characterDisplayed = 0;

LCD_status_t displayStringState = BUSY;
LCD_status_t integerdisplayState = BUSY;
LCD_status_t ClearState = BUSY;
LCD_status_t gotoState = BUSY;

void LCD_init(void)
{
	static uint8 init_states_counter = 0;

	if(init_lock == 0)
	{
		switch(init_states_counter)
		{
		case state1:
			DIO_Write(LCD_E, HIGH);
			DIO_Write(LCD_RS, HIGH);
			DIO_Write(LCD_RW, HIGH);
			init_states_counter++;
			break;
		case state2:
			LCD_sendCommand(FOUR_BITS_DATA_MODE);
			if(command_key == 1)
			{
				init_states_counter++;
				command_key = 0;
			}
			break;
		case state3:
			LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE);
			if(command_key == 1)
			{
				init_states_counter++;
				command_key = 0;
			}
			break;
		case state4:
			LCD_sendCommand(CURSOR_OFF);
			if(command_key == 1)
			{
				init_states_counter++;
				command_key = 0;
			}
			break;
		case state5:
			LCD_sendCommand(CLEAR_COMMAND);
			if(command_key == 1)
			{
				init_states_counter = 0;
				init_lock = 1;
				command_key = 0;
			}
		}
	}
}

void LCD_sendCommand(uint8 command)
{
	static uint8 command_states_counter = 0;

	if(command_key == 0)
	{
		switch(command_states_counter)
		{
		case state1:
			DIO_Write(LCD_RS, LOW);
			DIO_Write(LCD_RW, LOW);

			DIO_Write(LCD_D1, ((command >> 4) & 1u));
			DIO_Write(LCD_D2, ((command >> 5) & 1u));
			DIO_Write(LCD_D3, ((command >> 6) & 1u));
			DIO_Write(LCD_D4, ((command >> 7) & 1u));

			DIO_Write(LCD_E, HIGH);
			command_states_counter++;
			break;

		case state2:

			DIO_Write(LCD_E, LOW);

			DIO_Write(LCD_D1, ((command >> 0) & 1u));
			DIO_Write(LCD_D2, ((command >> 1) & 1u));
			DIO_Write(LCD_D3, ((command >> 2) & 1u));
			DIO_Write(LCD_D4, ((command >> 3) & 1u));

			DIO_Write(LCD_E, HIGH);
			command_states_counter++;
			break;

		case state3:

			DIO_Write(LCD_E, LOW);
			command_states_counter = 0;
			command_key = 1;
			break;
		}
	}
}

void LCD_displayCharacter(uint8 data)
{
	static uint8 Display_states_counter = 0;

	if(init_lock == 1)
	{
		switch(Display_states_counter)
		{
		case state1:
			DIO_Write(LCD_RS, HIGH);
			DIO_Write(LCD_RW, LOW);
			Display_states_counter++;
			break;
		case state2:
			DIO_Write(LCD_E, HIGH);
			Display_states_counter++;
			break;
		case state3:

			DIO_Write(LCD_D1, ((data >> 4) & 1u));
			DIO_Write(LCD_D2, ((data >> 5) & 1u));
			DIO_Write(LCD_D3, ((data >> 6) & 1u));
			DIO_Write(LCD_D4, ((data >> 7) & 1u));

			Display_states_counter++;
			break;
		case state4:

			DIO_Write(LCD_E, LOW);
			Display_states_counter++;
			break;
		case state5:

			DIO_Write(LCD_E, HIGH);
			Display_states_counter++;
			break;
		case state6:

			DIO_Write(LCD_D1, ((data >> 0) & 1u));
			DIO_Write(LCD_D2, ((data >> 1) & 1u));
			DIO_Write(LCD_D3, ((data >> 2) & 1u));
			DIO_Write(LCD_D4, ((data >> 3) & 1u));

			Display_states_counter++;
			break;
		case state7:

			DIO_Write(LCD_E, LOW);
			Display_states_counter++;
			break;
		case state8:
			Display_states_counter = 0;
			characterDisplayed = 1;
			break;
		}
	}

}

void LCD_displayString(const char* data)
{
	static uint8 loop_index = 0;

	if(init_lock == 1)
	{
		if(displayStringState ==BUSY)
		{
			LCD_displayCharacter(data[loop_index]);
			if(characterDisplayed == 1)
			{
				loop_index++;
				characterDisplayed = 0;
				if(data[loop_index] == '\0')
				{
					displayStringState = DONE;
					loop_index = 0;
				}
			}
		}
	}
}

void LCD_intgerToString(uint8 data)
{
	if(init_lock == 1)
	{
		if(integerdisplayState ==BUSY)
		{
			itoa(data,g_buffer,10);
			LCD_displayString(g_buffer);

			if(displayStringState == DONE)
			{
				integerdisplayState = DONE;
				displayStringState = BUSY;
			}
		}
	}
}

void LCD_goToRowColumn(uint8 row,uint8 col)
{
	static uint8 Address = 0;

	if(init_lock == 1)
	{
		switch(row)
		{
		case 0:
			Address=col;
			break;
		case 1:
			Address=col+0x40;
			break;
		case 2:
			Address=col+0x10;
			break;
		case 3:
			Address=col+0x50;
			break;
		}

		if(gotoState == BUSY)
		{
			LCD_sendCommand(Address | SET_CURSOR_LOCATION);
			if(command_key == 1)
			{
				command_key = 0;
				gotoState = DONE;
			}
		}
	}
}

void LCD_clearScreen(void)
{
	if(init_lock == 1)
	{
		if(ClearState == BUSY)
		{
			LCD_sendCommand(CLEAR_COMMAND);
			if(command_key == 1)
			{
				command_key = 0;
				ClearState = DONE;
			}
		}
	}
}
