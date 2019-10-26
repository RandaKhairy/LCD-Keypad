/*
 * main.c
 *
 *  Created on: Oct 25, 2019
 *      Author: Mariam Taha
 */


#include "OS.h"
#include "LCD.h"

void APP_init(void);
void Print_array(void);

Task_create_t Task1 = {0,2,APP_init,NA,NA};
Task_create_t Task2 = {0,2,Print_array,NA,NA};

void APP_init(void)
{
	LCD_init();
}

void Print_array(void)
{
	LCD_displayCharacter('a');
}



OS_ConfigType sys_tick_cnfg = {Sys_tick};
int main(void)
{
	DDRD |= (1u << PD0);
	PORTD &= ~(1u << PD0);

	DIO_init();


	OS_Init (&sys_tick_cnfg);

	OS_Create_Task(&Task1);
	OS_Create_Task(&Task2);

	OS_Run();
}
