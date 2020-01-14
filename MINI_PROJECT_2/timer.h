/*
 * timer.h
 *
 *  Created on: Jan 11, 2020
 *      Author: aly_s
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"

typedef enum{
	NO_CLOCK,F_CPU_CLOCK,F_CPU8,F_CPU64,F_CPU256,F_CPU1024
}Timer_Clock;

typedef enum{
	NORMAL, PWM, CTC, FAST_PWM
}Timer_Waveform;


typedef enum{
	NO_INTERRUPT,Timer_OVF,Timer_OC
}Timer_Mode;


typedef enum{
	NORMAL_CTC, TOGGLE,CLEAR,SET
}Timer_Compare;

typedef struct{
	Timer_Clock clock;
	Timer_Waveform waveform;
	Timer_Mode mode;
	Timer_Compare compare;
	uint8 startValue;
	uint8 compareValue;
}Timer_ConfigType;

void Timer_init(const Timer_ConfigType * Config_Ptr);


#endif /* TIMER_H_ */
