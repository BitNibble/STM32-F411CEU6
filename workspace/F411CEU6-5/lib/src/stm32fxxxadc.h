/******************************************************************************
	STM32 XXX ADC
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com>
License: GNU General Public License
Hardware: STM32-XXX
Date: 28022024
Comment:
	
*******************************************************************************/
#ifndef _STM32FXXXADC_H_
	#define _STM32FXXXADC_H_

/*** Library ***/
#include "armquery.h"

/*** ADC1 ADC2 ADC3 Auxiliary TypeDef ***/
typedef struct
{
	void (*inic)(void);
	void (*vbat)(void);
	void (*temp)(void);
	void (*start)(void);
}STM32FXXXADC1single, STM32FXXXADC2single, STM32FXXXADC3single;

/*** INTERRUPT HEADER ***/
void ADC_IRQHandler(void);

#endif

/***EOF***/

