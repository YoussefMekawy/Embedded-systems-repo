/*
 * main.c
 *
 *  Created on: 9 Oct 2022
 *      Author: hp
 */



#include "usart.h"
#include "gpio.h"

int main(void)
{
	uint8 Str[20];
	uint8 data;

	/* Initialize the UART driver with Baud-rate = 9600 bits/sec */
	USART_INITIALIZATION data_init = {PARITY_DISABLED ,ONE_STOP_BIT , BIT_8 , 9600};
	UART_init(&data_init);

    while(1)
    {
		data = UART_recieveByte(); /* Receive Byte from Terminal */
		UART_sendByte(data);       /* Re-send the received byte to Terminal */
//		UART_receiveString(Str);     /* Receive String from Terminal */
//	    UART_sendString(Str);        /* Re-send the string to Terminal2 */
    }
}
