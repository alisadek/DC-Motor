/*
 * timer.c
 *
 *  Created on: Jan 11, 2020
 *      Author: aly_s
 */

#include "timer.h"

/*This Function:
 * 1- Enables Global Interrupt
 * 2- Clears Counter
 * 3- Sets Timer Clock
 * 4- Sets Waveform mode
 *
 */
void Timer_init(const Timer_ConfigType * Config_Ptr){

	sei();
	if (Config_Ptr->waveform!= FAST_PWM){
		SET_BIT(TIMSK, FOC0);
	}
	else {CLEAR_BIT(TIMSK, FOC0);}

	TIMSK = (TIMSK & 0xFC) | (Config_Ptr->mode & 0x03);
	TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr->clock & 0x07);
	TCCR0 = (TCCR0 & 0xBF) | ((Config_Ptr->waveform & 0x01)<<6);
	TCCR0 = (TCCR0 & 0xF7) | ((Config_Ptr->waveform & 0x02)<<2);
	TCCR0 = (TCCR0 & 0xCF) | (Config_Ptr->compare & 0x03)<<4;
	TCNT0= Config_Ptr-> startValue;
	OCR0= Config_Ptr-> compareValue;
}
