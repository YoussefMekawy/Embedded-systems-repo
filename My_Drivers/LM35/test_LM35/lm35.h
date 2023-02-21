/*
 * lm35.h
 *
 *  Created on: 4 Oct 2022
 *      Author: hp
 */

#ifndef LM35_H_
#define LM35_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define SENSOR_CHANNEL_ID         2
#define SENSOR_MAX_VOLT_VALUE     1.5
#define SENSOR_MAX_TEMPERATURE    150


uint16 LM35_GetTemperature (void);

#endif /* LM35_H_ */
