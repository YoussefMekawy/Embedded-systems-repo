/*
 * main.c
 *
 *  Created on: 4 Oct 2022
 *      Author: Mekawy
 *
 */

#include "adc.h"
#include "dc_motor.h"
#include "lcd.h"
#include "lm35.h"


/*the temperature and it's global to use it in the display function  */
uint8 g_temp=0;

/*
 * display function to display the temperature and the fan state
 * also it will decrease the code size as all the if else's are the same printing */
void display_state (void);


int main (void)
{
	/* setup the ADC configurations */
	ADC_Initialization data = {INTERNAL , F_cpu_8 , ENABLE} ;
	ADC_init(&data);

	/* initialize the LCD */
	LCD_init();

	/* initialize the DC motor */
	DcMotor_Init();


	while(1)
	{

		/* get the current temperature value */
		g_temp = LM35_GetTemperature();

		/* if the temp is below 30 the fan is off */
		if (g_temp <= 30)
		{
			DCMotor_Rotate(CW, 0);
			display_state();
		}
		/* if the 30 < temp < 60 the fan is on with 25% */
		else if (g_temp >= 30 && g_temp < 60)
		{
			DCMotor_Rotate(CW, 25);
			display_state();
		}
		/* if the 60 < temp < 90 the fan is on with 50% */
		else if (g_temp >= 60 && g_temp < 90)
		{
			DCMotor_Rotate(CW, 50);
			display_state();
		}
		/* if the 90 < temp < 120 the fan is on with 75% */
		else if (g_temp >=90 && g_temp < 120)
		{
			DCMotor_Rotate(CW, 75);
			display_state();
		}
		/* if the temp is above 120 the fan is on with 100% */
		else
		{
			DCMotor_Rotate(CW, 100);
			display_state();
		}

	}

}

void display_state (void)
{
	if (g_temp <= 30)
		LCD_displayStringRowColumn(0, 4, "Fan is OFF ");
	else
	LCD_displayStringRowColumn(0, 4, "Fan is ON ");

	LCD_displayStringRowColumn(1, 4, "Temp=    C");
	LCD_moveCursor(1, 10);
	LCD_intgerToString(g_temp);
}

