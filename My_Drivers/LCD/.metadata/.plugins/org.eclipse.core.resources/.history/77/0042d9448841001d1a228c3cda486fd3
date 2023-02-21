/*
 * main.c
 *
 *  Created on: 1 Oct 2022
 *      Author: hp
 *      test lcd driver
 */

#include "lcd.h"
#include <util/delay.h>

int main(void)
{
	LCD_init();
	LCD_display_Character('r');
	LCD_string_Display("ramlaa");
	_delay_ms(1000);
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 5, "Mekawy");
	while(1) {};

	return 0;
}
