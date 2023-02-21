/*
 * adc.h
 *
 *  Created on: 1 Oct 2022
 *     Author: Mekawy
 */

#ifndef ADC_H_
#define ADC_H_


/*******************************************************************************
 *                                Includes                                  *
 *******************************************************************************/

#include "std_types.h"
#include "adc_types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56


/*******************************************************************************
 *                                Function Prototypes                                  *
 *******************************************************************************/
void ADC_init (ADC_Initialization *data);

void ADC_DeInit();

uint16 ADC_readChannel (uint8 ch_num);


#endif /* ADC_H_ */
