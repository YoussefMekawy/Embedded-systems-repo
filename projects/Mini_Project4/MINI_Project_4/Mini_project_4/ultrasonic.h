/*
 * ultrasonic.h
 *
 *  Created on: 11 Oct 2022
 *      Author: Mekawy
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

/*******************************************************************************
 *                            Includes
 *******************************************************************************/
#include "std_types.h"



/*******************************************************************************
 *                            Defines
 *******************************************************************************/
#define Trigger_PORT_ID  		 PORTB_ID
#define Trigger_PIN_ID 			 PIN5_ID

#define Echo_PORT_ID 			 PORTD_ID
#define Echo_PIN_ID 			 PIN6_ID

/*******************************************************************************
 *                            Prototypes
 *******************************************************************************/

/*
 * Description:
 * Initialize the ICU driver as required.
 * Setup the ICU call back function.
 * Setup the direction for the trigger pin as output pin through the GPIO driver.
 */
void Ultrasonic_init(void);

/*
 * Description:
 *Send the Trigger pulse to the ultrasonic.
 */
void Ultrasonic_Trigger(void);

/*
 * Description:
 * Send the trigger pulse by using Ultrasonic_Trigger function.
 * Start the measurements by the ICU from this moment.
 * Return: The measured distance in Centimeter.
 */
uint16 Ultrasonic_readDistance(void);

/*
 * Description
 * This is the call back function called by the ICU driver.
 * This is used to calculate the high time (pulse time) generated by the ultrasonic sensor.
 */
void Ultrasonic_edgeProcessing(void);



#endif /* ULTRASONIC_H_ */