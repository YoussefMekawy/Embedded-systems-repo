/*
 * lcd.c
 *
 *  Created on: 1 Oct 2022
 *      Author: Mekawy
 *      lcd c file
 *      containing function implementations for 4 bit mode and 8 bit modes
 */

/*-------------------------------------------------------------------------*/
/*-------------------------------INCLUDES----------------------------------*/
/*-------------------------------------------------------------------------*/

#include "lcd.h"
#include "gpio.h"
#include <util/delay.h>
#include "common_macros.h" /* For GET_BIT Macro */
#include <stdlib.h> /* for itoa function */

/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/*-------------------------FUNCTION DEFINITIONS----------------------------*/
/*-------------------------------------------------------------------------*/
void LCD_SendCommand (uint8 command)
{

	/*RS=0 */
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW);
	//delay 1u
	_delay_ms(1);

	/*enable =1 */
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	/*delay 1u */
	_delay_ms(1);

#if(LCD_DATA_BITS_MODE == 4)
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,7));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(command,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(command,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(command,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(command,3));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */

#elif(LCD_DATA_BITS_MODE == 8)
	//send command
	GPIO_writePort(LCD_DATA_PORT_ID, command);
	/*delay 1u*/
	_delay_ms(1);

	/*enable =0*/
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	/*delay 1u*/
	_delay_ms(1);
#endif

}

void LCD_display_Character (uint8 character)
{
	/*RS=1*/
	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH);
	/*delay 1u*/
	_delay_ms(1);

	/*enable =1*/
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	/*delay 1u*/
	_delay_ms(1);

#if(LCD_DATA_BITS_MODE == 4)
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(character,4));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(character,5));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(character,6));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(character,7));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_HIGH); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */

	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,GET_BIT(character,0));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,GET_BIT(character,1));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,GET_BIT(character,2));
	GPIO_writePin(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,GET_BIT(character,3));

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	GPIO_writePin(LCD_E_PORT_ID,LCD_E_PIN_ID,LOGIC_LOW); /* Disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */

#elif(LCD_DATA_BITS_MODE == 8)
	/*send command*/
	GPIO_writePort(LCD_DATA_PORT_ID, character);
	/*delay 1u*/
	_delay_ms(1);

	/*enable =0*/
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	/*delay 1u*/
	_delay_ms(1);
#endif

}

void LCD_init (void)
{
	/*RS & Enable output pins*/
	GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_OUTPUT);
	/*delay 20u */
	_delay_ms(20);

#if(LCD_DATA_BITS_MODE == 4)
	/* Configure 4 pins in the data port as output pins */
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB4_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB5_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB6_PIN_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID,LCD_DB7_PIN_ID,PIN_OUTPUT);

	/* Send for 4 bit initialization of LCD  */
	LCD_SendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_SendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);

	/* use 2-lines LCD + 4-bits Data Mode + 5*7 dot display Mode */
	LCD_SendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);

#elif(LCD_DATA_BITS_MODE == 8)
	/* Configure the data port as output port */
	GPIO_setupPortDirection(LCD_DATA_PORT_ID,PORT_OUTPUT);

	/* use 2-lines LCD + 8-bits Data Mode + 5*7 dot display Mode */
	LCD_SendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);

#endif

	/*send command cursor off*/
	LCD_SendCommand(LCD_CURSOR_OFF);

	/*clear screen*/
	LCD_SendCommand(LCD_CLEAR_COMMAND);
}

void LCD_string_Display (uint8 * str_ptr)
{
	while (*(str_ptr) != '\0')
	{
		LCD_display_Character(*str_ptr);
		str_ptr++;
	}
}

void LCD_moveCursor(uint8 row,uint8 col)
{
	uint8 lcd_memory_address;

	/* from data sheet check the address of the LCD RAM
	 * for first row the address is 0x01 0x02 ..... so it's the col num
	 * for second row the address is 0x41 0x42 .... so it's th col num + 0x40
	 * for third row the address is 0x10 0x11 ..... so it's the col num +0x10
	 * for fourth row the address is 0x51 0x52 ..... so it's the col num + 0x50
	 */

	switch (row)
	{
	case 0:
		lcd_memory_address=col;
		break;
	case 1:
		lcd_memory_address=col+0x40;
		break;
	case 2:
		lcd_memory_address=col+0x10;
		break;
	case 3:
		lcd_memory_address=col+0x50;
		break;
	}

	/* Move the LCD cursor to this specific address
	 * here the largest address is 0x5F so the MSB is always 0
	 * in this LCD from the data sheet I must put the MSB 1
	 * so I will OR the address value from the switch with 0x80
	 * here I set the cursor to the first row first col ORed with the address I got
	 */
	LCD_SendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}

void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str)
{
	LCD_moveCursor(row, col);
	LCD_string_Display(Str);
}

void LCD_intgerToString(int data)
{
	   char buff[16]; /* String to hold the ASCII result */
	   itoa(data,buff,10); /* Use itoa C function to convert the data to its corresponding ASCII value, 10 for decimal */
	   LCD_string_Display(buff); /* Display the string */
}

void LCD_clearScreen(void)
{
	LCD_SendCommand(LCD_CLEAR_COMMAND);
}
