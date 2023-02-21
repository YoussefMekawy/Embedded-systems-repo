/*
 * lm35.c
 *
 *  Created on: 4 Oct 2022
 *      Author: hp
 */
#include "std_types.h"
#include "adc.h"
#include "lm35.h"
#include <util/delay.h>


uint16 LM35_GetTemperature (void)
{
	uint8 temp_value = 0;

	/* Read ADC channel where the temperature sensor is connected */
	ADC_readChannel(SENSOR_CHANNEL_ID);

	/* Make delay for some time until g_adcResult value is updated with the ADC interrupt */
	_delay_ms(5);



	/* Calculate the temperature from the ADC value*/
	temp_value = (uint8)(((uint32)g_ADC_val*SENSOR_MAX_TEMPERATURE*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLT_VALUE));

	return temp_value;
}
