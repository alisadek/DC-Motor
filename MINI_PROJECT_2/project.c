/*
 * project.c
 *
 *  Created on: Jan 11, 2020
 *      Author: aly_s
 */


#include "project.h"

ISR(INT1_vect)
{
	reverse_Motor();
}

void reverse_Motor(void){
	TOGGLE_BIT(PORTB,PB0);
	TOGGLE_BIT(PORTB, PB1);
}
void INT1_init(void){
	sei();
	GICR= (1<<INT1);
	MCUCR = (1 << ISC11);
}
int main(void)
{
	uint16 potentiometerValue;
	INT1_init();
	ADC_init();
	LCD_init();
	DDRB = (1 << PB3) | (1 << PB0) | (1 << PB1);
	SET_BIT(PORTB,PB0);
	CLEAR_BIT(PORTB,PB1);
	CLEAR_BIT(DDRD, PD3);
	Timer_ConfigType config={F_CPU8, FAST_PWM, NO_INTERRUPT ,CLEAR, 0, potentiometerValue};
	while(1)
	{
		LCD_displayStringRowCol(0,0,"ADC= ");
		LCD_goToRowCol(0,6);
		LCD_integerToString(ADC_readChannel(0));
		potentiometerValue = ((ADC_readChannel(0))/4);
		config.compareValue= potentiometerValue;
		Timer_init(&config);
	};
}
