/*
 * timer1.h
 *
 *  Created on: 30 Oct 2022
 *      Author: hp
 */

#ifndef TIMER1_H_
#define TIMER1_H_

/***************************************************
 *            includes
 ***************************************************/

#include "std_types.h"


/********************************************************
 *         enums
 *******************************************************/

typedef enum {
	NO_CLK , F_CPU_1 , F_CPU_8 ,  F_CPU_64 , F_CPU_256 , F_CPU_1024
}Timer1_Prescaler;


typedef enum {
	Normal = 0 , Compare = 8
}Timer1_Mode;

/*******************************************************
 *         structs
 *******************************************************/

typedef struct {
uint16 initial_value;
uint16 compare_value; // it will be used in compare mode only.
Timer1_Prescaler prescaler;
Timer1_Mode mode;

} Timer1_ConfigType;


/******************************************************
 * 		functions prototypes
 *******************************************************/

void Timer1_init(const Timer1_ConfigType * Config_Ptr);

void Timer1_deInit(void);

void Timer1_setCallBack(void(*a_ptr)(void));

#endif /* TIMER1_H_ */
