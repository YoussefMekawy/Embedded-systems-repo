/*
 * dc_motor.c
 *
 *  Created on: 4 Oct 2022
 *      Author: Mekawy
 */

#include "dc_motor.h"
#include "std_types.h"
#include "gpio.h"

void DcMotor_Init(void)
{
	/*
	 * setting the pins directions
	 */
	GPIO_setupPinDirection(MOTOR_PORT_ID, MOTOR_PIN1_ID , PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_PORT_ID, MOTOR_PIN2_ID, PIN_OUTPUT);

	/*
	 * setting the initial value = 0 ;
	 */
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN1_ID, LOGIC_LOW);
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN2_ID, LOGIC_LOW);

}

void DCMotor_Rotate (DcMotor_State state,uint8 speed)
{

	/*
	 * here I send the speed I got from the controller to the PWM generator to
	 * set the duty cycle of the motor
	 */
	 PWM_Timer0_Init(speed);

	 /*
	  * if the state is clock-wise I rotate that way
	  * and if anti-clock-wise I rotate the other way
	  */
	if (state == CW)
	{
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN1_ID, LOGIC_HIGH);
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN2_ID, LOGIC_LOW);
	}
	else if (state == A_CW)
	{
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN1_ID, LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN2_ID, LOGIC_HIGH);
	}
}
