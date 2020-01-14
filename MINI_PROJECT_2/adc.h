/*
 * adc.h
 *
 *  Created on: Dec 29, 2019
 *      Author: aly_s
 */

#ifndef ADC_H_
#define ADC_H_

#include "micro_config.h"
#include "common_macros.h"
#include "std_types.h"

#define INTERRUPT    /*ADC Operates using interrupt*/


uint16 ADC_readChannel(uint8 a_channel_Num);
void ADC_init(void);

#endif /* ADC_H_ */
