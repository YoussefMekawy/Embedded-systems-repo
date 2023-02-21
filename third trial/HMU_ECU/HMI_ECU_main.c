/*
 * HMI_ECU_main.c
 *
 *  Created on: 30 Oct 2022
 *      Author: hp
 */

/*******************************************************************************
 * 								Includes
 *******************************************************************************/

#include "lcd.h"
#include "keypad.h"
#include "usart.h"
#include "timer1.h"
#include <avr/io.h>
#include <util/delay.h>
#include "gpio.h"

/*******************************************************************************
 * 								Definitions
 *******************************************************************************/
#define Matched_Passwords 		1
#define Unmatched_Passwords 	0

#define Open_Door 			43
#define Change_Pass 		45

#define rotate_motor		5
#define active_buzzer		15

#define password_created_in_EEPROM_before 	100
#define start_setting_password  150
#define dont_change_pass 90

/*******************************************************************************
 * 								function prototypes
 *******************************************************************************/
void Create_Password(void);
void check_for_enter(void);
void get_first_password(void);
void get_second_password(void);
void open_door_fun(void);
void motor_start_stop(void);
void Display_error(void);
void Activate_buzzer(void);
void count_the_time (void);
void Change_Pass_fun(void);


/*******************************************************************************
 * 								Global variables
 *******************************************************************************/

USART_INITIALIZATION usart_data_init = { PARITY_DISABLED , ONE_STOP_BIT , BIT_8 , 9600};
Timer1_ConfigType timer1_data_init = { 0 , 976, F_CPU_1024 ,Compare };

uint8 g_password[7]={0} ;
uint8 g_password_2[7]={0};
uint8 counter_incorrect_pass = 0;
uint8 g_tick = 0;
uint8 check_new_password;

/*******************************************************************************
 * THE CODE FLOW
 *
 * I enter the main and initialize the UART & the LCD
 *
 * then wait for a byte from the second microcontroller to tell me wether it's the
 * first time to enter this system so we will set a new password or we already set a password
 * so jump to the while 1
 *
 * the while(1) has 2 main functions
 *
 * + open door - change password
 *
 * +open door function will
 * 1)send a byte to second controller tell him the state
 * 2)take the password from user , send it , wait if matches or not
 * 3-a) if match will display the motor changes and send a byte to second controller to start rotating motor
 * 3-b) if not matched it increment the counter by 1 and loop on same function again
 *
 * -change password will
 * 1)send a byte to second controller tell him the state
 * 2)take the password from user , send it , wait if matches or not
 * 3-a) if match will call the function create_password to tell the user enter 2 passwords and so on
 * 3-b) if not matched it increment the counter by 1 and loop on same function again
 *
 * in both open door function and change password function if the user entered 3 passwords
 * incorrect in a row the controller will call the function activate buzzer and display error
 * activate buzzer will send a byte to second controller tell him the state to enter activate buzzer function there
 * display error will display error message for 1 minute
 *
 *******************************************************************************/

int main(void)
{
	uint8 system_state ;
	SREG |= (1<<7);
	LCD_init();
	UART_init(&usart_data_init);

	/*initial system password is 12345 */

	check_new_password=UART_recieveByte();
	if (check_new_password == start_setting_password)
	{
	Create_Password();
	}
	else if(check_new_password == dont_change_pass)
	{
		/* go to while(1) */
	}

	while(1)
	{
		LCD_clearScreen();
		LCD_string_Display("+ : Open Door");
		LCD_displayStringRowColumn(1, 0, "- : Change Pass");

		system_state = KEYPAD_getPressedKey();
		_delay_ms(500);

		if (system_state == Open_Door)
		{
			open_door_fun();
		}
		else if (system_state == Change_Pass)
		{
			Change_Pass_fun();
		}
		_delay_ms(50);
	}
}

/*******************************************************************************
 * 								function definitions
 *******************************************************************************/

void Create_Password(void)
{
	while(1)
	{

		uint8 create_check_on_recieve;

		get_first_password();
		get_second_password();

		/* send the 2 passwords */

		UART_sendString(g_password);
		_delay_ms(100);
		UART_sendString(g_password_2);
		_delay_ms(100);

		/* receive the result either matched or not matched */
		create_check_on_recieve = UART_recieveByte();

		if (create_check_on_recieve == Matched_Passwords)
		{
			break;
		}
		else if (create_check_on_recieve == Unmatched_Passwords){}
		_delay_ms(50);
	}
}
void get_first_password(void)
{
	uint8 i;
	LCD_clearScreen();
	LCD_string_Display("Enter Pass:");
	LCD_moveCursor(1, 0);

	/* get the first password from user */
	for (i=0 ; i<5 ; i++)
	{
		g_password[i] = KEYPAD_getPressedKey()+ '0';
		//LCD_display_Character(g_password[i]);
		LCD_display_Character('*');
		_delay_ms(500);

	}
	g_password[5]='#';
	g_password[6]='\0';
	/* wait until he press enter */
	check_for_enter();
}
void get_second_password(void)
{
	uint8 i;
	LCD_clearScreen();

	LCD_string_Display("Re-enter Pass:");
	LCD_moveCursor(1, 0);

	/* get the first password from user */
	for (i=0 ; i<5 ; i++)
	{
		g_password_2[i] = KEYPAD_getPressedKey()+ '0';
		//LCD_display_Character(g_password_2[i]);
		LCD_display_Character('*');
		_delay_ms(500);
	}
	g_password_2[5]='#';
	g_password_2[6]='\0';
	/* wait until he press enter */
	check_for_enter();
}
void check_for_enter(void)
{
	uint8 check_enter;
	do{
		check_enter =KEYPAD_getPressedKey();
		_delay_ms(500);
	}while (check_enter!= 13);

	/* clear the check_enter variable */
	check_enter =0;
}

void open_door_fun(void)
{
	while (counter_incorrect_pass != 3)
	{
		/* send a signal for the COTROL_ECU to tell him I am in the open door function */
		UART_sendByte(Open_Door);
		_delay_ms(100);

		uint8 open_door_check_recieved;
		LCD_clearScreen();
		get_first_password();

		UART_sendString(g_password);
		_delay_ms(100);

		open_door_check_recieved = UART_recieveByte();

		if (open_door_check_recieved == Matched_Passwords)
		{
			counter_incorrect_pass=0;
			motor_start_stop();
			break;
		}
		else if (open_door_check_recieved == Unmatched_Passwords)
		{
			counter_incorrect_pass++;
		}
		_delay_ms(50);
	}
	if (counter_incorrect_pass ==3)
	{
		counter_incorrect_pass=0;
		Activate_buzzer();
		Display_error();
	}
}


void motor_start_stop(void)
{
	UART_sendByte(rotate_motor);
	_delay_ms(100);

	Timer1_init(&timer1_data_init);
	Timer1_setCallBack(count_the_time);

	LCD_clearScreen();
	LCD_string_Display("Door Unlocking");
	while (g_tick < 15){};
	g_tick=0;

	LCD_clearScreen();
	LCD_string_Display("HOLD ");
	while (g_tick < 3){};
	g_tick=0;

	LCD_clearScreen();
	LCD_string_Display("Door Locking");
	while (g_tick < 15){};
	g_tick=0;

	Timer1_deInit();
}

void Display_error(void)
{
	LCD_clearScreen();
	Timer1_init(&timer1_data_init);
	Timer1_setCallBack(count_the_time);
	LCD_string_Display("ERROR!!");
	LCD_displayStringRowColumn(1, 0, "System Locked");
	while (g_tick <=60){};
	g_tick=0;
	Timer1_deInit();
	LCD_clearScreen();
}
void Activate_buzzer(void)
{
	UART_sendByte(active_buzzer);
	_delay_ms(100);
}
void count_the_time (void)
{
	g_tick++;
}
void Change_Pass_fun(void)
{
	while (counter_incorrect_pass != 3)
	{
		/* send a signal for the COTROL_ECU to tell him I am in the change password function*/
		UART_sendByte(Change_Pass);
		_delay_ms(100);

		uint8 change_pass_check;
		get_first_password();
		UART_sendString(g_password);

		change_pass_check = UART_recieveByte();
		if (change_pass_check == Matched_Passwords)
		{
			counter_incorrect_pass=0;
			Create_Password();
			break;
		}
		else if (change_pass_check == Unmatched_Passwords)
		{
			counter_incorrect_pass++;
		}
		_delay_ms(50);
	}
	if (counter_incorrect_pass ==3)
	{
		counter_incorrect_pass=0;
		Activate_buzzer();
		Display_error();
	}
}
