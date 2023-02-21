/*
 * adc.h
 *
 *  Created on: 1 Oct 2022
 *      Author: hp
 */

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

extern volatile uint16 g_ADC_val;
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   5


void ADC_init ();

uint16 ADC_readChannel (uint8 ch_num);


#endif /* ADC_H_ */
