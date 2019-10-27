/*
 * main.c
 *
 *  Created on: Oct 26, 2019
 *      Author: Randa
 */

#include "OS.h"
#include "LCD.h"
#include "keypad.h"

extern LCD_status_t displayStringState;
extern LCD_status_t clearScreenState;
extern KEYPAD_status_t keypad_status;

#define NUM_OF_QUESTIONS 5
#define NUM_OF_ANSWERS 3
#define NO 0
#define YES 1

static uint8 Questions[NUM_OF_QUESTIONS][20] = {"France?", "UK?", "Germany?", "Italy?", "Netherlands?"};
static uint8 Answers[NUM_OF_ANSWERS][10] = {"1.YES", "2.NO", "3.Skip"};
static uint8 Questions_Answers[NUM_OF_QUESTIONS][5] = {"YES", "YES", "NO", "NO", "YES"};

/* Tasks Flags */
static uint8 DisplayNextQuestion = YES;
static uint8 DisplayQuestionAnswer = NO;
static uint8 GetUserAnswer = NO;
static uint8 CheckUserAnswer = NO;
static uint8 DisplayFinalScore = NO;


static uint8 QuestionIndex = 0;
static uint8 score = 0;
static uint8 answer;

void APP_init(void);
void DisplayQuestionTask(void);
void DisplayAnswer(void);
void GetAnswer(void);
void CheckAnswer(void);
void DisplayScore(void);


void APP_init(void)
{
	LCD_init();
}

void DisplayQuestionTask(void)
{
	static uint8 display_state_counter = 0;

	if(DisplayNextQuestion == YES)
	{
		switch(display_state_counter)
		{
		LCD_clearScreen();
		if(clearScreenState == DONE)
		{
			clearScreenState = DISPALY;
		}
		case 0:
			LCD_displayString(Questions[QuestionIndex]);
			if(displayStringState == DONE)
			{
				displayStringState = DISPALY;
				display_state_counter++;
				QuestionIndex++;
				DisplayNextQuestion = NO;
				DisplayQuestionAnswer = YES;
			}
		break;
		case 1:
			LCD_displayString(Questions[QuestionIndex]);
			if(displayStringState == DONE)
			{
				displayStringState = DISPALY;
				display_state_counter++;
				QuestionIndex++;
				DisplayNextQuestion = NO;
				DisplayQuestionAnswer = YES;
			}
		break;
		case 2:
			LCD_displayString(Questions[QuestionIndex]);
			if(displayStringState == DONE)
			{
				displayStringState = DISPALY;
				display_state_counter++;
				QuestionIndex++;
				DisplayNextQuestion = NO;
				DisplayQuestionAnswer = YES;
			}
		break;
		case 3:
			LCD_displayString(Questions[QuestionIndex]);
			if(displayStringState == DONE)
			{
				displayStringState = DISPALY;
				display_state_counter++;
				QuestionIndex++;
				DisplayNextQuestion = NO;
				DisplayQuestionAnswer = YES;
			}
		break;
		case 4:
			LCD_displayString(Questions[QuestionIndex]);
			if(displayStringState == DONE)
			{
				displayStringState = DISPALY;
				QuestionIndex++;
				DisplayNextQuestion = NO;
				DisplayQuestionAnswer = YES;
			}
		break;
		default:
			display_state_counter = 0;
			QuestionIndex = 0;
			DisplayNextQuestion = NO;
			DisplayQuestionAnswer = NO;
			DisplayFinalScore = YES;
		}
	}

}

void DisplayAnswer(void)
{
	static uint8 display_answer_counter = 0;
	if(DisplayQuestionAnswer == YES)
	{
		switch( display_answer_counter)
		{
		case 0:
			LCD_displayString(Answers[0]);
			if(displayStringState == DONE)
			{
				displayStringState = DISPALY;
				display_answer_counter++;
			}
		break;
		case 1:
			LCD_displayString(Answers[1]);
			if(displayStringState == DONE)
			{
				displayStringState = DISPALY;
				display_answer_counter++;
			}
		break;
		case 2:
			LCD_displayString(Answers[2]);
			if(displayStringState == DONE)
			{
				displayStringState = DISPALY;
				display_answer_counter++;
			}
		break;
		default:
			display_answer_counter = 0;
			DisplayQuestionAnswer = NO;
			GetUserAnswer = YES;
		}
	}
}

void GetAnswer(void)
{
	if(GetUserAnswer == YES)
	{
		KeyPad_getPressedKey();
		if(keypad_status == PRESSED)
		{
			answer = pressedKey;
			GetUserAnswer = NO;
			CheckUserAnswer = YES;
		}
	}
}

void CheckAnswer()
{
	if(CheckUserAnswer == YES)
	{
		if(answer == Questions_Answers[QuestionIndex-1])
		{
			score++;
			DisplayNextQuestion = YES;
			CheckUserAnswer = NO;
		}
	}
}

void DisplayScore(void)
{
	//inttostring;
	if(displayStringState == DONE)
	{
		displayStringState = DISPALY;
	}
}

OS_ConfigType sys_tick_cnfg = {Sys_tick};
int main(void)
{

	DIO_init();
	OS_Init (&sys_tick_cnfg);

	Task_create_t Task1 = {0,2, APP_init, NA, NA};
	Task_create_t Task2 = {0,2, DisplayQuestionTask, NA, NA};
	Task_create_t Task3 = {0,2, DisplayAnswer, NA, NA};
	Task_create_t Task4 = {0,30, GetAnswer, NA, NA};
	Task_create_t Task5 = {0,30, CheckAnswer, NA, NA};
	Task_create_t Task6 = {0,200, DisplayScore, NA, NA};

	OS_Create_Task(&Task1);
	OS_Create_Task(&Task2);
	OS_Create_Task(&Task3);
	OS_Create_Task(&Task4);
	OS_Create_Task(&Task5);
	OS_Create_Task(&Task6);

	OS_Run();
}
