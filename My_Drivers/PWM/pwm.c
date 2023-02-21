/*
 * pwm.c
 *
 *  Created on: 4 Oct 2022
 *      Author: hp
 */

#include "pwm.h"
#include "std_types.h"
#include "gpio.h"
#include "dc_motor.h"
#include <avr/io.h>


void PWM_Timer0_Init(uint8 speed)
{
	/*Set Timer Initial value*/
	TCNT0 = 0;

	/*set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.*/
	GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);

	/* set the speed of the motor */
	uint8 motor_speed= (uint8)((float)2.56*speed);
	OCR0  = motor_speed;

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */

	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);


}