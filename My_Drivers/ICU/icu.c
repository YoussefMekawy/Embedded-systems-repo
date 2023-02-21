/*
 * icu.c
 *
 *  Created on: 11 Oct 2022
 *      Author: hp
 */
#include "icu.h"
#include <avr/io.h>
#include "common_macros.h"
#include "gpio.h"
#include <avr/interrupt.h>


/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;


/*
 * ISR
 */

ISR(TIMER1_CAPT_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*******************************************************************************
 *                           Function Prototypes                               *
 *******************************************************************************/

void Icu_init( icu_CONFIG * Config_Ptr)
{
	/*
	 * set pin as output
	 */
	GPIO_setupPinDirection(PORTD_ID, PIN6_ID, PIN_INPUT);

	/*
	 * non PWM
	 */
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);


	/*
	 * set the edge type
	 * Bit 6 – ICES1: Input Capture Edge Select
	 */
	TCCR1B =(Config_Ptr->edge);

	/*
	 * set the clock prescaler
	 */
	TCCR1B = (TCCR1B & 0xF8) |Config_Ptr->prescaler ;

	/*
	 * set initial count = 0
	 */
	TCNT1=0;

	/*
	 *  set the value of ICR1 = 0
	 */
	ICR1=0;

	/*
	 *Bit 5 – TICIE1: Timer/Counter1, Input Capture Interrupt Enable
	 */
	TIMSK |= (1<<TICIE1);

}


void Icu_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}


void Icu_setEdgeDetectionType(const icu_edge_select edgeType)
{
	TCCR1B = (TCCR1B & 0xBF) | edgeType ;
}

uint16 Icu_getInputCaptureValue(void)
{
	return ICR1;
}


void Icu_clearTimerValue(void)
{
	TCNT1 = 0;
}

void Icu_DeInit(void)
{
	/* Clear All Timer1 Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	/* Disable the Input Capture interrupt */
	TIMSK &= ~(1<<TICIE1);
}
