/*
 * lcd.h
 *
 *  Created on: Dec 27, 2019
 *      Author: aly_s
 */

#ifndef LCD_H_
#define LCD_H_

/*Header Files that will be included*/

#include <stdlib.h>
#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"


/*****************************************************
 *                  Configurations                   *
 *****************************************************/
#define UPPER_PORT_PINS
#define DATA_BITS_MODE 8



/* Function Prototypes*/
void LCD_displayCharacter(uint8 data);
void LCD_sendCommand(uint8 command);
void LCD_init(void);
void LCD_displayString(const char *str);
void LCD_goToRowCol(uint8 row, uint8 col);
void LCD_integerToString(int data);
void LCD_displayStringRowCol(uint8 row, uint8 col, const char *Str);
/*PORTS Config*/
#define LCD_CTRL_PORT_DIR DDRD
#define LCD_CTRL_PORT PORTD

#define LCD_DATA_PORT PORTC
#define LCD_DATA_PORT_DIR DDRC


/* LCD Commands */
#define CLEAR_COMMAND 0x01
#define LCD_FOUR_BITS_MODE 0x02
#define TWO_LINE_LCD_FOUR_BITS_MODE 0x28
#define TWO_LINE_LCD_EIGHT_BITS_MODE 0x38
#define CURSOR_OFF 0x0C
#define CURSOR_ON 0x0E
#define SET_CURSOR_LOCATION 0x80

/*PINS Config*/
#define RS PD0
#define RW PD1
#define E PD2

#endif /* LCD_H_ */
