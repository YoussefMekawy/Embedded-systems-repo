/*
 * adc.c
 *
 *  Created on: 4 Oct 2022
 *      Author: Mekawy
 *      ADC using polling method and not quite configurable
 */

#include "common_macros.h"
#include <avr/io.h>
#include "std_types.h"

volatile uint16 g_ADC_val =0;

ISR(ADC_vect)
{
	g_ADC_val = ADC;
}

void ADC_init ()
{
	/*
	 * 5 V reference (AVCC)
	 * REFS1 REFS0 (01)
	 * ADLAR   = 0 right adjusted
	 * Bits 4:0 – MUX4:0: Analog Channel and Gain Selection Bits
	 * choose 0000 as initialization
	 * • Bit 3 – ADIE: ADC Interrupt Enable
	 */
	ADMUX = 0 ;

	/*
	 * Enable ADC -> Bit 7 – ADEN: ADC Enable in ADCSRA
	 * set the  Bits 2:0 – ADPS2:0: ADC Prescaler Select Bits
	 * these what control the clock of the ADC
	 * to get range 50 k t0 200 k Hz with F_cpu = 16 MHz
	 * set the presacer to 128 == 111
	 */

	ADCSRA = (1<<ADEN) | (1<<ADIE) | (1<<ADPS0) | (1<<ADPS1) ;

}

void ADC_readChannel(uint8 ch_num)
{
	/*
	 * if I want say channel 1
	 * make the last 5 bits =0 , leave first 3 unchanged (anded with 1)
	 * And the channel num with 0x07 to clear all its bits except the last 3 bits
	 * then OR the channel num i got with the register ADMUX
	 * */

	ADMUX = (ADMUX & 0xE0) | (ch_num & 0x07);

	/* Bit 6 – ADSC: ADC Start Conversion */
	SET_BIT(ADCSRA,ADSC);

}
