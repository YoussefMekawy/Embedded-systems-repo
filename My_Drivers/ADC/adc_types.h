/*
 * adc_types.h
 *
 *  Created on: 4 Oct 2022
 *      Author: hp
 */

#ifndef ADC_TYPES_H_
#define ADC_TYPES_H_

/*******************************************************************************
 *                                Enums                                        *
 *******************************************************************************/

typedef enum {
	AREF , AVCC=0x40 , INTERNAL =0xC0
}Vref_Bits;


typedef enum {
	F_cpu_2 = 1 , F_cpu_4 , F_cpu_8 , F_cpu_16 , F_cpu_32 , F_cpu_64 , F_cpu_128
}F_ADC;

typedef enum {
	DISABLE , ENABLE
}Status;

/*******************************************************************************
 *                                       structs                               *
 *******************************************************************************/
typedef struct
{
	Vref_Bits volt;
	F_ADC freq;
	Status state;
}ADC_Initialization;


#endif /* ADC_TYPES_H_ */
