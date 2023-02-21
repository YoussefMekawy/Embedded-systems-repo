/*
 * bit_field_data_type.h
 *
 * here I can easily access a register bit by bit or I can write in the whole register
 *
 *  Created on: 25 Sep 2022
 *      Author: hp
 */

#ifndef BIT_FIELD_DATA_TYPE_H_
#define BIT_FIELD_DATA_TYPE_H_

typedef union
{
	unsigned char Data;
	struct
	{
		unsigned char BIT0:1;
		unsigned char BIT1:1;
		unsigned char BIT2:1;
		unsigned char BIT3:1;
		unsigned char BIT4:1;
		unsigned char BIT5:1;
		unsigned char BIT6:1;
		unsigned char BIT7:1;
	}BITS;
};

#endif /* BIT_FIELD_DATA_TYPE_H_ */
