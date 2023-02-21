/*
 * main.c
 *
 *  Created on: 30 Oct 2022
 *      Author: hp
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timer1.h"

unsigned char seconds_digit=0;
unsigned char seconds_tenth=0;
unsigned char minutes_digit=0;
unsigned char minutes_tenth=0;
unsigned char hours_digit=0;
unsigned char hours_tenth=0;


void TIMER1_processing()
{
	// in this ISR I just update the time value
	seconds_digit++;

	if (seconds_digit >= 10)
	{
		seconds_digit=0;
		seconds_tenth++;

		/*didn't end the bracket here  because if
		no overflow in the first digit  then nothing more gonna change*/

		if (seconds_tenth >= 6)
		{
			seconds_tenth=0;
			minutes_digit++;
		}

		if (minutes_digit >=10)
		{
			minutes_digit=0;
			minutes_tenth++;
		}

		if (minutes_tenth >=6)
		{
			minutes_tenth=0;
			hours_digit++;
		}

		if(hours_digit >=10)
		{
			hours_digit=0;
			hours_tenth++;
		}
		if (hours_tenth >=10)
		{
			seconds_digit=0;
			seconds_tenth=0;
			minutes_digit=0;
			minutes_tenth=0;
			hours_digit=0;
			hours_tenth=0;
		}
	}
}



ISR (INT0_vect)
{
	seconds_digit=0;
	seconds_tenth=0;
	minutes_digit=0;
	minutes_tenth=0;
	hours_digit=0;
	hours_tenth=0;
}



ISR (INT1_vect)
{
	//we will stop the stopWatch by applying no clock to the timer
	//therefore it will stop counting
	TCCR1B &= ~(1<<CS12);
	TCCR1B &= ~(1<<CS11);
	TCCR1B &= ~(1<<CS10);
}


ISR (INT2_vect)
{
	//to resume the count from where we left it just apply the clock again
	TCCR1B |=(1<<CS10) | (1<< CS11);
}


void reset_INIT(void)
{
	//set button as input
	DDRD &= ~(1<<PD2);

	//enable internal pull up
	PORTD |= (1<<PD2);

	//make interrupt 0 with falling edge
	MCUCR |= (1<<ISC01);

	//enable interrupt mask request
	GICR |= (1<<INT0);
}


void Stop_INIT (void)
{
	//set button as input
	DDRD &= ~(1<<PD3);

	//make interrupt 1 with rising edge
	MCUCR |= (1<<ISC10)| (1<<ISC11) ;

	//enable interrupt 1 mask request
	GICR |= (1<<INT1);
}

void Resume_INIT (void)
{
	//set button as input
	DDRB &= ~(1<<PB2);

	//enable internal pull up
	PORTB |= (1<<PB2);

	//make interrupt 2 with falling edge
	MCUCSR &= ~(1<<ISC2);

	//enable interrupt 2 mask request
	GICR |= (1<<INT2);
}



int main (void)
{
	SREG |= (1<<7);

	// Connect 7447 decoder 4-pins to the first 4-pins in PORTC.
	DDRC |= 0x0F;

	//Use first 6-pins in PORTA as the enable/disable pins for the six 7-segments.
	DDRA |= 0b00111111;

	// set initial value of the seven segments to 0
	PORTC = (PORTC & 0xF0) ;

	//set them all as active in the beginning
	PORTA = 0x3F;

	//call Timer 1 initialize function
	Timer1_ConfigType data = { 0 , 15625 , F_CPU_256 , Compare};

	Timer1_init(&data);

	if (data.mode == Compare)
	{
		Timer1_setCallBack(TIMER1_processing);
	}

	// initialize reset button to reset the stopwatch when pressed
	reset_INIT();

	// initialize the stop button to stop the timer when pressed
	Stop_INIT();

	//initialize resume button to resume the time when pressed
	Resume_INIT();

	while (1)
	{
		// display content of seven segment only !
		// by enabling the seven segment transistor (put 0 on it) and disable all others
		PORTA = (PORTA & 0xC0) | (1<<0);
		PORTC = (PORTC & 0xF0) | (seconds_digit & 0x0F) ;
		_delay_ms(3);

		PORTA = (PORTA & 0xC0) | (1<<1);
		PORTC = (PORTC & 0xF0) | (seconds_tenth & 0x0F) ;
		_delay_ms(3);

		PORTA = (PORTA & 0xC0) |(1<<2);
		PORTC = (PORTC & 0xF0) | (minutes_digit & 0x0F) ;
		_delay_ms(3);

		PORTA = (PORTA & 0xC0) |(1<<3);
		PORTC = (PORTC & 0xF0) | (minutes_tenth & 0x0F) ;
		_delay_ms(3);

		PORTA = (PORTA & 0xC0) |(1<<4);
		PORTC = (PORTC & 0xF0) | (hours_digit & 0x0F) ;
		_delay_ms(3);

		PORTA = (PORTA & 0xC0) |(1<<5);
		PORTC = (PORTC & 0xF0) | (hours_tenth & 0x0F) ;
		_delay_ms(3);

	}
}
