	/*
 * main.c
 *
 *  Created on: 1 Oct 2022
 *      Author: hp
 */
#include "lcd.h"
#include "adc.h"


int main (void)
{
	ADC_Initialization  data ={AVCC , F_cpu_128 , ENABLE};
	uint16 res_value;

	LCD_init();
	ADC_init(&data);

	while (1)
	{
		/* Read ADC channel 0 where the potentiometer is connected */
		res_value = ADC_readChannel(0);

		LCD_string_Display("ADC value = ");
		LCD_intgerToString(res_value);
		LCD_string_Display("  ");
		LCD_moveCursor(0, 0);
	}
	return 0;
}
