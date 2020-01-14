/*
 * adc.c
 *
 *  Created on: Dec 29, 2019
 *      Author: aly_s
 */

#include "adc.h"
ISR(ADC_vect)
{
	return;
}
void ADC_init(void)
{
	/*Internal Vref turned off
	 *Left Adjustment turned off
	 *Channel Bits are initialized at 0 */

	ADMUX = 0;

	/*Enable ADC and Set prescaler to F_CPU8*/

	ADCSRA= (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0);
#ifndef INTERRUPT
	CLEAR_BIT(ADCSRA, ADIE);
#else
	SET_BIT(ADCSRA, ADIE);
	sei();
#endif

}
uint16 ADC_readChannel(uint8 a_channel_Num)
{
	/* Insert Channel Num in ADMUX*/
	ADMUX= (ADMUX&0xE0)|(a_channel_Num & 0x07);
	ADCSRA = (1<<ADSC) | (1<<ADEN) | (1<<ADPS0) | (1<<ADPS1);
#ifndef INTERRUPT
	while(BIT_IS_SET(ADCSRA, ADIF)){}
	SET_BIT(ADCSRA, ADIF);
#endif
	return ADC;
}
