/*
 * timer1.c
 *
 *  Created on: 30 Oct 2022
 *      Author: hp
 */



/********************************************************************************
 * 				includes
 *******************************************************************************/

#include "timer1.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 * 				ISR
 *******************************************************************************/

ISR (TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR (TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*******************************************************************************
 * 				Function definitions
 *******************************************************************************/

void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{

	/* non-pwm */
	TCCR1A = (1<<FOC1A);

	/* choose mode
	 * mode = 0 if normal
	 * mode = 0b00001000 if compare  */

	TCCR1B  = Config_Ptr->mode ;

	/*initial value */
	TCNT1 = Config_Ptr->initial_value ;


	if (Config_Ptr->mode == Compare)
	{
		/* compare value in compare mode */
		OCR1A = Config_Ptr->compare_value ;

		/* enable timer1 compare A interrupt */
		TIMSK |= (1<<OCIE1A);
	}
	else if (Config_Ptr->mode == Normal)
	{
		/* enable timer 1 overflow interrupt */
		TIMSK |= (1<<TOIE1);
	}

	/* set the clock prescaler */
	TCCR1B |= Config_Ptr->prescaler ;
}

void Timer1_deInit(void)
{
 /*
  * set the registers to zero
  */
	TCCR1A=0;
	TCCR1B=0;
	TCNT1=0;
	OCR1A=0;
}

void Timer1_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}
