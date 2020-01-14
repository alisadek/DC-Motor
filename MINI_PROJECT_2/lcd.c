/*
 * lcd.c
 *
 *  Created on: Dec 27, 2019
 *      Author: aly_s
 */

#include "lcd.h"

void LCD_init(void)
{

	LCD_CTRL_PORT_DIR = (1<<RS)|(1<<E)|(1<<RW);
#if (DATA_BITS_MODE==4)
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT_DIR|= 0xF0;
#else
	LCD_DATA_PORT_DIR|=0x0F;
#endif
	LCD_sendCommand(LCD_FOUR_BITS_DATA_MODE);
	LCD_sendCommand(TWO_LINE_LCD_FOUR_BIT_MODE);
#elif (DATA_BITS_MODE==8)
	LCD_DATA_PORT_DIR=0xFF;
	LCD_sendCommand(TWO_LINE_LCD_EIGHT_BITS_MODE);
#endif

	LCD_sendCommand(CURSOR_OFF);
	LCD_sendCommand(CLEAR_COMMAND);
}


void LCD_sendCommand(uint8 command)
{
	CLEAR_BIT(LCD_CTRL_PORT,RS);
	CLEAR_BIT(LCD_CTRL_PORT,RW);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT, E);
	_delay_ms(1);
#if (DATA_BITS_MODE==4)

#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT= (LCD_DATA_PORT & 0x0F) | (command & 0xF0);
#else
	LCD_DATA_PORT= (LCD_DATA_PORT & 0xF0) | ((command & 0xF0) >> 4));
#endif
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT= (LCD_DATA_PORT&0x0F)|((command&0x0F)<<4);
#else
	LCD_DATA_PORT= (LCD_DATA_PORT&0xF0)|(command&0x0F);
#endif
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
#elif (DATA_BITS_MODE==8)
	LCD_DATA_PORT= command;
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT, E);
	_delay_ms(1);

#endif

}

void LCD_displayCharacter(uint8 data)
{
	SET_BIT(LCD_CTRL_PORT, RS);
	CLEAR_BIT(LCD_CTRL_PORT,RW);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT, E);
	_delay_ms(1);
#if (DATA_BITS_MODE==4)
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (data & 0xF0);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((data & 0xF0) >> 4);
#endif
	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
	SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
	_delay_ms(1); /* delay for processing Tpw - Tdws = 190ns */
	/* out the lowest 4 bits of the required data to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((data & 0x0F) << 4);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (data & 0x0F);
#endif

	_delay_ms(1); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	_delay_ms(1); /* delay for processing Th = 13ns */
#elif (DATA_BITS_MODE==8)
	LCD_DATA_PORT= data;
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT, E);
	_delay_ms(1);
#endif
}

void LCD_displayString(const char *str)
{
	uint8 i=0;
	while(str[i]!= '\0')
	{
		LCD_displayCharacter(str[i]);
		i++;
	}
}
void LCD_goToRowCol(uint8 row, uint8 col)
{
	uint8 address;
	switch(row){

	case 0: address= col;
	break;

	case 1: address= 0x40+col;
	break;

	case 2: address= 0x10+col;
	break;

	case 3: address= 0x50+col;
	break;
	}
	LCD_sendCommand(SET_CURSOR_LOCATION|address);
}

void LCD_integerToString(int data)
{
	char buff[16];
	itoa(data,buff,10);
	LCD_displayString(buff);
}

void LCD_displayStringRowCol(uint8 row, uint8 col, const char *Str)
{
	LCD_goToRowCol(row, col);
	LCD_displayString(Str);
}


