/*
 * common_macros.h
 *
 *  Created on: 25 Sep 2022
 *      Author: Mekawy
 */

#ifndef COMMON_MACROS
#define COMMON_MACROS

/* set bit*/
#define SET_BIT(reg , bit) (reg|=(1<<bit))

/* clear bit */
#define CLEAR_BIT(reg,bit) (reg &= (~(1<<bit)))

/*toggle bit */
#define TOGGLE_BIT(reg,bit) (reg ^= (1<<bit))

/*rotate right */
#define ROR(reg,num) ( reg = (reg >> num) | (reg << (8-num)) )

/*rotate left */
#define ROL(reg,num) ( reg = (reg << num) | (reg >> (8-num)) )

/* bit is set ? */
#define BIT_IS_SET(reg,bit) ( reg & (1<<bit) )

/*bit is clear ? */
#define BIT_IS_CLEAR(reg,bit) ( !(reg & (1<<bit)) )

/* get bit */
#define GET_BIT(reg,bit) ( (reg & (1<<bit) ) >> bit )




#endif /* COMMON_MACROS */
