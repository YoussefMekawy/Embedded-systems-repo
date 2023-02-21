/*
 * pwm.c
 *
 *  Created on: 4 Oct 2022
 *      Author: Mekawy
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

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */

	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);


	/*set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.*/
	GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);

	/* set the speed of the motor
	 * if the user send 25 this means he wants it 25% so I will put the compare value to
	 * 25% of its max value which is 64 and so on
	 * */

	uint8 motor_speed;

	switch (speed)
	{
	case 0: motor_speed=0;
			break;
	case 25: motor_speed=64;
			break;
	case 50: motor_speed=128;
			break;
	case 75: motor_speed=192;
			break;
	case 100: motor_speed=255;
			break;
	}

	/*
	 * here is the compare value which will decide the motor duty cycle
	 */
	OCR0  = motor_speed;

}
