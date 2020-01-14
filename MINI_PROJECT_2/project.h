/*
 * project.h
 *
 *  Created on: Jan 11, 2020
 *      Author: aly_s
 */

#ifndef PROJECT_H_
#define PROJECT_H_

#include "adc.h"
#include "lcd.h"
#include "timer.h"

void startTimer(uint8 a_outputCompareValue);
void reverse_Motor(void);
void INT1_init(void);
#endif /* PROJECT_H_ */
