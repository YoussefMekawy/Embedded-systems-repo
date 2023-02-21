/*
 * usart.h
 *
 *  Created on: 9 Oct 2022
 *      Author: Mekawy
 */

#ifndef USART_H_
#define USART_H_

#include "std_types.h"
#include "usart_types.h"

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(USART_INITIALIZATION * data_init);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 * we will send the bytes by the polling method
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 * we will receive bytes by the polling
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #


#endif /* USART_H_ */
