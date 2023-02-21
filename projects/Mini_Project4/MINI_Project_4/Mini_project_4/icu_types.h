/*
 * icu_types.h
 *
 *  Created on: 11 Oct 2022
 *      Author: hp
 */

#ifndef ICU_TYPES_H_
#define ICU_TYPES_H_

/*
 * edge select enum
 */
typedef enum {
	FALLING , RISING = 0x40
}icu_edge_select;

/*
 * clock prescaler
 */

typedef enum {
 NO_CLK , F_CPU_1, F_CPU_8 ,F_CPU_64 , F_CPU_256 , F_CPU_1024
}icu_clock_prescaler;

/*
 * struct config
 */
typedef struct {

	icu_edge_select edge ;
	icu_clock_prescaler prescaler;

}icu_CONFIG ;
#endif /* ICU_TYPES_H_ */
