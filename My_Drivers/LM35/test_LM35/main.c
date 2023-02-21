/*
 * main.c
 *
 *  Created on: 4 Oct 2022
 *      Author:Mekawy
 *      test LM35
 */

#include "adc.h"
#include "lcd.h"
#include "lm35.h"

int main(void)
{
	uint8 temp;
	ADC_Initialization  data ={AVCC , F_cpu_128 , ENABLE};
	LCD_init(); /* initialize LCD driver */
	ADC_init(&data); /* initialize ADC driver */

	/* Display this string "Temp =   C" only once on LCD at the first row */
	LCD_string_Display("Temp =    C");

    while(1)
    {

    	temp = LM35_GetTemperature();

		/* Display the temperature value every time at same position */
		LCD_moveCursor(0,7);
		if(temp >= 100)
		{
			LCD_intgerToString(temp);
		}
		else
		{
			LCD_intgerToString(temp);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_display_Character(' ');
		}
    }
}