/*
 * lcd.h
 *
 *  Created on: 1 Oct 2022
 *      Author: Mekawy
 *      header file of LCD driver
 */

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"


/*---------------------------------------------------------------------------*/
/*-------------------------------DEFINITIONS---------------------------------*/
/*---------------------------------------------------------------------------*/
/* these defines are the configurations that should be made to connect to different pins*/

/*choose either 4 bit mode or 8 bit mode*/
#define LCD_DATA_BITS_MODE 8

#if((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))

#error "Number of Data bits should be equal to 4 or 8"

#endif


#define LCD_RS_PORT_ID                 PORTD_ID
#define LCD_RS_PIN_ID                  PIN2_ID

#define LCD_E_PORT_ID                  PORTD_ID
#define LCD_E_PIN_ID                   PIN3_ID

#define LCD_DATA_PORT_ID               PORTC_ID

/*if we use 4 bit mode then there are 4 pins only*/
#if (LCD_DATA_BITS_MODE == 4)

#define LCD_DB4_PIN_ID                 PIN3_ID
#define LCD_DB5_PIN_ID                 PIN4_ID
#define LCD_DB6_PIN_ID                 PIN5_ID
#define LCD_DB7_PIN_ID                 PIN6_ID

#endif

/* LCD commands : these are related to the LCD we are using */

#define LCD_CLEAR_COMMAND                    0x01
#define LCD_GO_TO_HOME                       0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                       0x0C
#define LCD_CURSOR_ON                        0x0E
#define LCD_SET_CURSOR_LOCATION              0x80


/*---------------------------------------------------------------------------*/
/*---------------------------FUNCTION-PTOTPTYPES-----------------------------*/
/*---------------------------------------------------------------------------*/

/* prototype of command function */
void LCD_SendCommand (uint8 command) ;

/* prototype of displaying a single character */
void LCD_display_Character (uint8 character);

/* init function */
void LCD_init (void) ;

/*string display */
void LCD_string_Display (uint8 * str_ptr);

/* Move the cursor to a specified row and column index on the screen */
void LCD_moveCursor(uint8 row,uint8 col);

/* Display the required string in a specified row and column index on the screen */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);


/* Display the required decimal value on the screen */
void LCD_intgerToString(int data);

/*send clear command to screen */
void LCD_clearScreen(void);

#endif /* LCD_H_ */
