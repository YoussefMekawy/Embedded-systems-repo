/*
 * main.c
 *
 *  Created on: 11 Oct 2022
 *      Author: Mekawy
 */

#include "ultrasonic.h"
#include "common_macros.h"
#include "lcd.h"
#include <avr/interrupt.h>
#include "gpio.h"
#include <util/delay.h>


uint16 g_distance =0;

int main(void)
{

	/* initialize lcd */
	LCD_init();

	/* initialize ultrasonic */
	Ultrasonic_init();
	/* enable I-Bit */
	SREG |= (1<<7);
	LCD_string_Display("Distance=");

	while (1)
	{
		/* get the distance */
		g_distance = Ultrasonic_readDistance();
		LCD_moveCursor(0, 9);
		LCD_intgerToString(g_distance);
		LCD_string_Display("cm  ");
	}

}
